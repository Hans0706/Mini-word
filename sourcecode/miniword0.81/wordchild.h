#ifndef WORDCHILD_H
#define WORDCHILD_H

#include <QKeyEvent>
#include <QWidget>
#include"QMdiArea"
#include"form.h"
#include <cstdlib>
#include <QLabel>
#include <QString>
#include <iostream>

class row{
private:
          QString temp;
              QString filename;
public:
  char * text;
  int size,maxsize;
  int order;
  void changefilename(QString a);
   QString getfilename();
   void readFile();
  row * next;


  row(int ord){
      maxsize=100;
      size =0;
      order=ord;
      text=(char *)calloc(maxsize,sizeof(char));
//      for(int i=0;i<maxsize;i++)
//          text[i]='\0';
      next=nullptr;
  }
  ~row(){free(text);}    //警告：调用析构函数时请确保已将该链节从链表中分离，否则可能导致链表断开

  void newNext(){
      row * cache=next;
      next=new row(order + 1);
      next->next=cache;
      while(cache!=nullptr){
          cache->order+=1;
          cache=cache->next;
      }

  }

  void enlarge(){
      maxsize+=100;
      char * cache = (char *)calloc(maxsize,sizeof(char));
//      for(int i=0;i<maxsize;i++)
//          cache[i]='\0';
      for(int i=0;i<size;i++)
          cache[i]=text[i];
      free(text);
      text = cache;
  }
  void input(const char ch,const int pos){
      if(size==maxsize)
          this->enlarge();
      if(pos!=size)
          for(int i=size;i>pos;i--)
              text[i]=text[i-1];
      text[pos]=ch;
      size++;
  }
  void insert(QString qstr,int place){  //插在第place个字符后面，从1开始数，0代表行首
      QString cache = QString("%1").arg(text);
      QString front,behind;
      if(place==0)
          front="",behind=cache;
      else
          front = cache.mid(0,place),behind = cache.mid(place);

      cache = "";
      cache += front;
      cache += qstr;
      cache += behind;

      QByteArray ba = cache.toLatin1();
      char *ch=ba.data();

      maxsize = cache.length()/100*100+100;
      size = cache.length();
      free(text);
      text = (char *)calloc(maxsize,sizeof(char));
      for(int i=0;i<size;i++)
          text[i] = ch[i];
  }

  QString to_QStr(){
      QString qs;
      qs = QString("%1").arg(text);
      return qs;
  }
  void from_QStr(QString cache){
        QByteArray ba = cache.toLatin1();
        char *ch=ba.data();

        maxsize = cache.length()/100*100+100;
        size = cache.length();
        free(text);
        text = (char *)calloc(maxsize,sizeof(char));
        for(int i=0;i<size;i++)
            text[i] = ch[i];
    }

};

class My_cursor{
public:
    int x,y;    //第x行，第y个字符后面
    row * currentRow;

    void moveup(){x--;}
    void movedown(){
        if(currentRow->next==nullptr){
                    y=currentRow->size;
                    return;
                }
                x++;
                currentRow=currentRow->next;
                if(y>currentRow->size)
                    y=currentRow->size;
    }
    void moveleft(){y--;}
    void moveright(){
        if(y==currentRow->size){
            if(currentRow->next==nullptr)
                return;
            x++;
            y=0;
            currentRow=currentRow->next;
        }
        else
            y++;
    }

    void input(const char c){
        currentRow->input(c,y);
        y++;
    }
    void enter(){
        currentRow->newNext();

        QString cache = currentRow->to_QStr();
        cache = cache.mid(y);
        for(int i=y;i<currentRow->size;i++)
            currentRow->text[i]='\0';

        currentRow->size=y;
        currentRow=currentRow->next;
        currentRow->insert(cache,0);

        y=0;
        x++;
    }
    void backspace(){
        for(int i=y;i<currentRow->size;i++)
            currentRow->text[i-1]=currentRow->text[i];
        currentRow->text[--(currentRow->size)]='\0';
        y--;
    }
    void del(){
        for(int i=y+1;i<currentRow->size;i++)
            currentRow->text[i-1]=currentRow->text[i];
        currentRow->text[--(currentRow->size)]='\0';
    }

    My_cursor(row * current){
        x=1,y=0;
        currentRow=current;
    }
};


class BS{
public:
    int state;  //0代表未选中内容，1代表选中内容
    int start_x,start_y;    //坐标所带字符不包含在选区内
    int end_x,end_y;    //坐标所带字符包含在选区内
    row * startRow,* endRow;
    QString clipboard;

    void copying(){
          QString cache = QString("%1").arg(startRow->text);
          clipboard = cache.mid(start_y,end_y-start_y);
  //        clipboard+="\n";
  //        row * c=startRow->next;
  //        for(int i=start_x+1;i<end_x;i++){
  //            clipboard += QString("%1").arg(c->text);
  //            clipboard += "\n";
  //            c=c->next;
  //        }
  //        cache = QString("%1").arg(c->text);
  //        clipboard+=cache.mid(0,end_y);
    }
    void delThis(){
           QString cache = QString("%1").arg(startRow->text),fin;
           fin = cache.mid(0,start_y);
           fin += cache.mid(end_y);
           startRow ->from_QStr(fin);
           state=0;
           inactive();
       }

    void active(int sx,int sy,int ex,int ey,row * start){    //make sure ex>=sx; when ex==sx, make sure ey>=sy, start from 1
        start_x=sx;
        start_y=sy;
        end_x=ex;
        end_y=ey;
        if(start_x==end_x&&start_y>end_y){
                   int ccc=start_y;
                   start_y=end_y;
                   end_y=ccc;
               }
        state=1;
        clipboard = "";
        startRow=start;
        row * cache = start;
        for(int i=0;i<end_x-start_x;i++)
            cache=cache->next;
        endRow=cache;
    }
    void inactive(){
        start_x=0;
        start_y=0;
        end_x=0;
        end_y=0;

        state=0;
        startRow = endRow = nullptr;
    }

    BS(){
        start_x=0;
        start_y=0;
        end_x=0;
        end_y=0;

        state=0;
        clipboard = "";
        startRow = endRow = nullptr;
    }
};
class wordchild:public QWidget
{
    Q_OBJECT
public:
    wordchild();
    void keyPressEvent(QKeyEvent *e);
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *m);
    void mouseReleaseEvent(QMouseEvent *m);
    void newFile();
    void insert(char s);

    int downlen=0;
    int henlen=0;
    QString cancel1;
    QScrollBar *vbar;
    QScrollBar *hbar;
    My_cursor * cur;
    row * rowHead;
       BS * bs;


       int nowLHx,nowLHy;  //现在左上角是第几行第几个字
    Form *A;
    QLabel *a;

    int count=0;//计数
    QPixmap* pixmap;
    QPixmap* pixmap2;
    QFont the_font;
    QColor the_color;
    QString userFriendlyCurrentFile();
    QString currentFile()
    {
        return curFile;
    }
    //编辑功能
        bool loadFile(const QString &fileName);
        bool save();
        bool saveAs();
        bool saveFile(QString fileName);
        void setCursorPos(int x,int y);

        int countChar(){
            row * cache = rowHead;
            int i=0;
            while(cache!=nullptr){
                i+=cache->size;
                cache=cache->next;
            }
            return i;
        }


    void openFile();
    void pressBackspace();
    void pressDel();
    void pressLeft();
    void pressRight(){cur->moveright();}
    void pressUp();
    void pressDown(){cur->movedown();}
    void copy(){
       if(bs->state==0)
           return;
       bs->copying();
   }
   void cut(){
       if(bs->state==0)
           return;
       bs->copying();
       setCursorPos(bs->start_x,bs->start_y);
       bs->delThis();
   }
   void paste(){
       if(bs->state==1){
           bs->delThis();
           setCursorPos(bs->start_x,bs->start_y);
       }
       QString qs = cur->currentRow->to_QStr();
       qs.insert(cur->y,bs->clipboard);
       cur->currentRow->from_QStr(qs);
       setCursorPos(cur->x,cur->y+bs->clipboard.length());
    }
        row * findRow(int ord){
            row * cache = rowHead;
            while(cache->order!=ord&&cache->next!=nullptr)
                cache=cache->next;
            return cache;
        }
        bool isUntitled;                    //作为当前文件是否被保存到硬盘上的标志
        void setCurrentFile(const QString &fileName);

protected:
    void closeEvent(QCloseEvent *event);    //关闭事件

private:
    QString strippedName(const QString &fullFileName);
                                        //获取较短的绝对路径
    QString curFile;                    //用于保存当前文件路径

private slots:
    void to_find_cha(QString);
    void to_replace_cha(QString,QString);
    void v_bar_changed(int x);
    void h_bar_changed(int y);
};


#endif // WORDCHILD_H














