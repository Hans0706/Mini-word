#include"wordchild.h"
#include<QtWidgets>
#include <QPainter>
#include <QKeyEvent>
#include <QString>
#include<form.h>
#include<QFile>
#include<QDialog>
#include<fstream>
#include<qtextstream.h>
#include<QInputDialog>
 wordchild::wordchild()
{


    QKeyEvent *e;
    QPaintEvent *event;
    QMouseEvent *m;

    nowLHx=nowLHy=1;
    cancel1 = "233333.can";
    rowHead = new row(1);
    cur = new My_cursor(rowHead);
    bs = new BS;

    a=new QLabel(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setFocusPolicy(Qt::StrongFocus);

    this->vbar=new QScrollBar(this);
    this->vbar->setMinimum(5);this->vbar->setMaximum(300);
    this->vbar->setMaximumSize(QSize(20,800));

    this->vbar->setMinimumSize(QSize(25,800));

    this->vbar->setSingleStep(5);
    vbar->move(1880,0);
    connect(this->vbar,SIGNAL(valueChanged(int)),this,SLOT(v_bar_changed(int)));    //滚动条改变时可以发出当前的值传到槽函数里
    this->hbar=new QScrollBar(this);
        this->hbar->setMinimum(0);
    this->hbar->setMaximumSize(QSize(1900,20));

    this->hbar->setMinimumSize(QSize(1900,25));
    this->hbar->setMaximum(3000);
    this->hbar->setSingleStep(10);
    hbar->move(0,800);
    hbar->setOrientation(Qt::Horizontal);
    connect(this->hbar,SIGNAL(valueChanged(int)),this,SLOT(h_bar_changed(int)));    //滚动条改变时可以发出当前的值传到槽函数里

    paintEvent(event);
    isUntitled=true;
    setMinimumHeight(300);
    setMinimumWidth(500);

}
void wordchild::v_bar_changed(int x)
{
    this->downlen=x;
    this->update();

}
void wordchild::h_bar_changed(int y)
{
    this->henlen=y;
    this->update();
}
void row::readFile()
{

    int len; //变量存储长度
    int space; //确定需要申请多少个堆
    int i,count = 0; //count用于计算是否到达100
    QString str;
    QFile file(this->filename);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
        QTextStream in(&file);
        QTextCodec *codec=QTextCodec::codecForName("utf8");
        in.setCodec(codec);
        while(!in.atEnd())
            {
            str=file.readLine();
                    //insert(str);

}
}
void row::changefilename(QString a)
{
     this->filename=a;
}
QString row::getfilename()
{
    return this->filename;
}
void wordchild::newFile()
{
    //设置窗口编号 因为编号会一直被保存 所以需要使用静态变量
    static int sequenceNumber=1;
    //新建的文档默认未命名
    isUntitled=false;
    //将当前文件命名为“文档+编号”的形式 编号先使用再加一
    curFile=tr("文档%1").arg(sequenceNumber++);
}

void wordchild::insert(const char s)
{
    if(bs->state==1){
           setCursorPos(bs->start_x,bs->start_y);
           bs->delThis();
       }
    if(s=='\n')
        cur->enter();
    else
        cur->input(s);
}

void wordchild::closeEvent(QCloseEvent *event)
{
    event->accept();
}


void wordchild::setCurrentFile(const QString &fileName)
{
    curFile = QFileInfo(fileName).canonicalFilePath();
    //文件已经被保存
    isUntitled = false;

    //窗口不显示被更改标志
    setWindowModified(false);
    //设置窗口标题,返回文件名
   // setWindowTitle(userFriendlyCurrentFile() + "[*]");
}

bool wordchild::save()
{

    if(isUntitled)
    {
        return saveFile(curFile);
    }
    else return saveAs();
}
bool wordchild::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("另存为"), curFile, tr("txt 文档 (*txt)"));
    //获取文件路径，若为空返回false，否则保存文件
    if(fileName.isEmpty())
        return false;
    isUntitled=1;
    return saveFile(fileName);
}

bool wordchild::saveFile(QString fileName)
{
    if(!(fileName.endsWith(".txt")))
    {
        fileName += ".txt";//保存为HTML文档
    }

    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QTextStream out(&file);
        row * cache = rowHead;
        while(cache!=nullptr){
            out<<cache->to_QStr();
            if(cache->next!=nullptr)
                out<<"\n";
            cache=cache->next;
        }
        return 1;
    }
    return 0;

}


void wordchild::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
        {
        case Qt::Key_A:if(LOBYTE(GetKeyState(VK_CAPITAL))==0)
                this->insert('a');
            else
                this->insert('A'); break;
        case Qt::Key_B:if(LOBYTE(GetKeyState(VK_CAPITAL))==0)
                this->insert('b');
            else
                this->insert('B'); break;
        case Qt::Key_C:if(LOBYTE(GetKeyState(VK_CAPITAL))==0)
                this->insert('c');
            else
                this->insert('C'); break;
        case Qt::Key_D:if(LOBYTE(GetKeyState(VK_CAPITAL))==0)
                this->insert('d');
            else
                this->insert('D');  break;
        case Qt::Key_E:if(LOBYTE(GetKeyState(VK_CAPITAL))==0)
                this->insert('e');
            else
                this->insert('E'); break;
        case Qt::Key_F:if(LOBYTE(GetKeyState(VK_CAPITAL))==0)
                this->insert('f');
            else
                this->insert('F'); break;
        case Qt::Key_G:if(LOBYTE(GetKeyState(VK_CAPITAL))==0)
                this->insert('g');
            else
                this->insert('G'); break;
        case Qt::Key_H:if(LOBYTE(GetKeyState(VK_CAPITAL))==0)
                this->insert('h');
            else
                this->insert('H'); break;
        case Qt::Key_I:if(LOBYTE(GetKeyState(VK_CAPITAL))==0)
                this->insert('i');
            else
                this->insert('I'); break;
        case Qt::Key_J:if(LOBYTE(GetKeyState(VK_CAPITAL))==0)
                this->insert('j');
            else
                this->insert('J'); break;
        case Qt::Key_K:if(LOBYTE(GetKeyState(VK_CAPITAL))==0)
                this->insert('k');
            else
                this->insert('K'); break;
        case Qt::Key_L:if(LOBYTE(GetKeyState(VK_CAPITAL))==0)
                this->insert('l');
            else
                this->insert('L'); break;
        case Qt::Key_M:if(LOBYTE(GetKeyState(VK_CAPITAL))==0)
                this->insert('m');
            else
                this->insert('M'); break;
        case Qt::Key_N:if(LOBYTE(GetKeyState(VK_CAPITAL))==0)
                this->insert('n');
            else
                this->insert('N'); break;
        case Qt::Key_O:if(LOBYTE(GetKeyState(VK_CAPITAL))==0)
                this->insert('o');
            else
                this->insert('O'); break;
        case Qt::Key_P:if(LOBYTE(GetKeyState(VK_CAPITAL))==0)
                this->insert('p');
            else
                this->insert('P'); break;
        case Qt::Key_Q:if(LOBYTE(GetKeyState(VK_CAPITAL))==0)
                this->insert('q');
            else
                this->insert('Q'); break;
        case Qt::Key_R:if(LOBYTE(GetKeyState(VK_CAPITAL))==0)
                this->insert('r');
            else
                this->insert('R'); break;
        case Qt::Key_S:if(LOBYTE(GetKeyState(VK_CAPITAL))==0)
                this->insert('s');
            else
                this->insert('S'); break;
        case Qt::Key_T:if(LOBYTE(GetKeyState(VK_CAPITAL))==0)
                this->insert('t');
            else
                this->insert('T'); break;
        case Qt::Key_U:if(LOBYTE(GetKeyState(VK_CAPITAL))==0)
                this->insert('u');
            else
                this->insert('U'); break;
        case Qt::Key_V:if(LOBYTE(GetKeyState(VK_CAPITAL))==0)
                this->insert('v');
            else
                this->insert('V'); break;
        case Qt::Key_W:if(LOBYTE(GetKeyState(VK_CAPITAL))==0)
                this->insert('w');
            else
                this->insert('W'); break;
        case Qt::Key_X:if(LOBYTE(GetKeyState(VK_CAPITAL))==0)
                this->insert('x');
            else
                this->insert('X'); break;
        case Qt::Key_Y:if(LOBYTE(GetKeyState(VK_CAPITAL))==0)
                this->insert('y');
            else
                this->insert('Y'); break;
        case Qt::Key_Z:if(LOBYTE(GetKeyState(VK_CAPITAL))==0)
                this->insert('z');
            else
                this->insert('Z'); break;

        case Qt::Key_0:if(LOBYTE(GetKeyState(VK_SHIFT))>0)
                this->insert('0');
            else
                this->insert(')'); break;
        case Qt::Key_1:if(LOBYTE(GetKeyState(VK_SHIFT))>0)
                this->insert('1');
            else
                this->insert('!'); break;
        case Qt::Key_2:if(LOBYTE(GetKeyState(VK_SHIFT))>0)
                this->insert('2');
            else
                this->insert('@'); break;
        case Qt::Key_3:if(LOBYTE(GetKeyState(VK_SHIFT))>0)
                this->insert('3');
            else
                this->insert('#'); break;
        case Qt::Key_4:if(LOBYTE(GetKeyState(VK_SHIFT))>0)
                this->insert('4');
            else
                this->insert('$'); break;
        case Qt::Key_5:if(LOBYTE(GetKeyState(VK_SHIFT))>0)
                this->insert('5');
            else
                this->insert('%'); break;
        case Qt::Key_6:if(LOBYTE(GetKeyState(VK_SHIFT))>0)
                this->insert('6');
            else
                this->insert('^'); break;
        case Qt::Key_7:if(LOBYTE(GetKeyState(VK_SHIFT))>0)
                this->insert('7');
            else
                this->insert('&'); break;
        case Qt::Key_8:if(LOBYTE(GetKeyState(VK_SHIFT))>0)
                this->insert('8');
            else
                this->insert('*'); break;
        case Qt::Key_9:if(LOBYTE(GetKeyState(VK_SHIFT))>0)
                this->insert('9');
            else
                this->insert('('); break;

        case Qt::Key_Space:
            this->insert(' '); break;

        case Qt::Key_Minus:if(LOBYTE(GetKeyState(VK_SHIFT))>0)
                this->insert('-');
            else
                this->insert('_'); break;
        case Qt::Key_Equal:if(LOBYTE(GetKeyState(VK_SHIFT))>0)
                this->insert('=');
            else
                this->insert('+'); break;
        case Qt::Key_BracketLeft:if(LOBYTE(GetKeyState(VK_SHIFT))>0)
                this->insert('[');
            else
                this->insert('{'); break;
        case Qt::Key_BracketRight:if(LOBYTE(GetKeyState(VK_SHIFT))>0)
                this->insert(']');
            else
                this->insert('}'); break;
        case Qt::Key_QuoteDbl:if(LOBYTE(GetKeyState(VK_SHIFT))>0)
                       this->insert('\\');
                   else
                       this->insert('|');  break;
        case Qt::Key_Semicolon:if(LOBYTE(GetKeyState(VK_SHIFT))>0)
                this->insert(';');
            else
                this->insert(':'); break;
        case Qt::Key_QuoteLeft:if(LOBYTE(GetKeyState(VK_SHIFT))>0)
                this->insert('`');
            else
                this->insert('~'); break;
        case Qt::Key_Apostrophe:if(LOBYTE(GetKeyState(VK_SHIFT))>0)
                this->insert(' ');
            else
                this->insert('"'); break;
        case Qt::Key_Comma:if(LOBYTE(GetKeyState(VK_SHIFT))>0)
                this->insert(',');
            else
                this->insert('<'); break;
        case Qt::Key_Period:if(LOBYTE(GetKeyState(VK_SHIFT))>0)
                this->insert('.');
            else
                this->insert('>'); break;
        case Qt::Key_Slash:if(LOBYTE(GetKeyState(VK_SHIFT))>0)
                this->insert('/');
            else
                this->insert('?'); break;

        //special keys
    case Qt::Key_Enter:
 //            this->insert('\n');break;
             this->copy();break;
        case Qt::Key_Return:
            this->insert('\n');break;

        case Qt::Key_Backspace:
            this->pressBackspace();break;
        case Qt::Key_Delete:
            this->pressDel();break;

        case Qt::Key_Right:
            this->cur->moveright();break;
        case Qt::Key_Left:
            this->pressLeft();break;
    case Qt::Key_Up:
                this->pressUp();break;
            case Qt::Key_Down:
                this->pressDown();break;
    case Qt::Key_Insert:
              this->paste();break;

 case Qt::Key_Home:
        downlen=henlen=0;break;
    case Qt::Key_End:
        downlen=800;break;

    }
    std::cout<<"Total words:"<<countChar()<<std::endl;
update();
}

void wordchild::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QString final,beforeC,afterC,select,drawCursor,ca;
    beforeC = afterC = final = select = drawCursor = "";
    //for bs
    row * cache = rowHead,* br,* ar;
    int bx,by,ax,ay;

    if(bs->state==1){
        bx=bs->start_x;
        by=bs->start_y;
        ax=bs->end_x;
        ay=bs->end_y;
        br=bs->startRow;
        ar=bs->endRow;
    }
    else{
        ax=bx=cur->x;
        ay=by=cur->y;
        ar=br=cur->currentRow;
    }

    //before
    beforeC += "<span class=\"def\">";
    while(cache->order < bx){
        beforeC += cache->to_QStr();
        beforeC += "<br>";
        cache = cache->next;
    }
    ca=br->to_QStr();
    if(bx==0)
        beforeC += "";
    else
        beforeC += ca.mid(0,by);
    beforeC += "</span>";

    //after
    afterC += "<span class=\"def\">";
    if(ay==ar->size)
        afterC += "";
    else
        afterC += ca.mid(ay);
    cache = ar->next;
    while(cache!=nullptr){
        afterC += "<br>";
        afterC += cache->to_QStr();
        cache = cache->next;
    }
    afterC += "</span>";

    //BS
       if(bs->state==1){
           select = "<span class=\"bs\">";
   //        QString q = bs->startRow->to_QStr();
   //        if(bs->start_x==bs->end_x)
   //            select += q.mid(bs->start_y,bs->end_y - bs->start_y);
   //        else{
   //            if(bs->start_y==bs->startRow->size)
   //                select += "";
   //            else
   //                select += q.mid(bs->start_y);
   //            row *rs = bs->startRow->next;
   //            for(int i=1;i < bs->end_x - bs->start_x;i++){
   //                select += rs->to_QStr();
   //                select += "<br>";
   //                rs=rs->next;
   //            }
   //            q = bs->endRow->to_QStr();
   //            if(bs->end_y==0)
   //                select += "";
   //            else
   //                select += q.mid(0,bs->end_y);
   //        }
           QString cache = QString("%1").arg(bs->startRow->text);
           select += cache.mid(bs->start_y,bs->end_y - bs->start_y);

           select += "</span>";
       }

    //cursor
    drawCursor = "<span class=\"cur\">|</span>";

    //color
    QString col = the_color.name();
    //html header
    final = "<style>.def{color:";
    final += col;
    final += ";} .cur{color:purple;background-color:yellow;} .bs{background-color:cyan;color=red;}</style>";

    final += beforeC;
    if(bs->state==1){
        if(cur->x==bs->start_x && cur->y==bs->start_y){
            final += drawCursor;
            final += select;
        }
        else{
            final += select;
            final += drawCursor;
        }
    }
    else
        final += drawCursor;
    final += afterC;

    if(this->a!=NULL)
    this->a->close();

    this->a=new QLabel(this);
    a->setMinimumWidth(100);
    a->setAlignment(Qt::AlignBottom);

//    QFont ft;
    the_font.setPointSize(18);
    a->setFont(the_font);

//    QPalette pa;
//    pa.setColor(QPalette::WindowText,Qt::red);
//    pa.setColor(QPalette::Window,Qt::yellow);
//    a->setPalette(pa);


    a->move(-henlen,-downlen);

    this->a->setText(final);
    a->show();


update();
}

void wordchild::pressBackspace(){
    if(bs->state==1){
           setCursorPos(bs->start_x,bs->start_y);
           bs->delThis();
           return;
       }
    if(cur->y!=0)
        cur->backspace();
    else if(cur->x==1)
        return;
    else{
        row * cache = this->rowHead;
        while(cache->next!=cur->currentRow)
            cache = cache->next;
        (cur->x)--;
        cur->y = cache->size;
        cache->insert(cur->currentRow->to_QStr(),cache->size);
        cache->next = cache->next->next;
        delete cur->currentRow;
        cur->currentRow=cache;
        while(cache->next!=nullptr){
            (cache->next->order)--;
            cache=cache->next;
        }
    }
}

void wordchild::pressDel(){
    if(bs->state==1){
           setCursorPos(bs->start_x,bs->start_y);
           bs->delThis();
           return;
       }
    if(cur->currentRow->next==nullptr&&cur->y==cur->currentRow->size)
        return;
    else if(cur->y==cur->currentRow->size){
        cur->currentRow->insert(cur->currentRow->next->to_QStr(),cur->currentRow->size);
        row * cache = cur->currentRow->next;
        cur->currentRow->next = cur->currentRow->next->next;
        delete cache;
        cache = cur->currentRow;
        while(cache->next!=nullptr){
            (cache->next->order)--;
            cache=cache->next;
        }
    }
    else
        cur->del();
}

void wordchild::pressLeft(){
    if(cur->y!=0)
        cur->moveleft();
    else if(cur->x==1)
        return;
    else{
        (cur->x)--;
        row * cache = this->rowHead;
        while(cache->next!=cur->currentRow)
            cache = cache->next;
        cur->y=cache->size;
        cur->currentRow=cache;
    }
}
void wordchild::pressUp(){
    if(cur->x==1){
        cur->y=0;
        return;
    }

    cur->moveup();
    row *cache = rowHead;
    while(cache->order!=cur->x && cache!=nullptr)
        cache=cache->next;
    cur->currentRow=cache;
    if(cur->y > cur->currentRow->size)
        cur->y = cur->currentRow->size;
}

void wordchild::setCursorPos(int x,int y){
    row * cache = rowHead;
    while(cache->order!=x&&cache->next!=nullptr)
        cache=cache->next;
    cur->currentRow=cache;

    if(cache->next==nullptr)
    cur->x=cur->currentRow->order;
    else
        cur->x=x;
    if(y>cur->currentRow->size)
        cur->y=cur->currentRow->size;
    else
        cur->y=y;
}


void wordchild::mousePressEvent(QMouseEvent *m){
    bs->inactive();
    int rx,ry,px=m->x(),py=m->y();
    rx=py/27+nowLHx;
    if(px<6)
        ry=nowLHy-1;
    else if(rx==cur->x && (px-6)/12+nowLHy > cur->y)
        ry=(px-6)/12+nowLHy-1;
    else
        ry=(px-6)/12+nowLHy;
    if(LOBYTE(GetKeyState(VK_TAB))==0){
        setCursorPos(rx,ry);
        return;
    }
    int release_x=cur->x,release_y=cur->y;
    setCursorPos(rx,ry);
    int press_x=cur->x,press_y=cur->y;
    if(release_x!=press_x || release_y!=press_y){
        if(release_x<press_x)
            bs->active(release_x,release_y,press_x,press_y,findRow(release_x));
        else if(release_x==press_x){
            if(release_y<press_y)
                bs->active(release_x,release_y,press_x,press_y,findRow(release_x));
            else
                bs->active(press_x,press_y,release_x,release_y,findRow(press_x));
        }
        else
            bs->active(press_x,press_y,release_x,release_y,findRow(press_x));
    }

    update();
}
void wordchild::mouseReleaseEvent(QMouseEvent *m){
    int rx,ry,px=m->x(),py=m->y();
    rx=py/27+nowLHx;
    if(px<6)
        ry=nowLHy-1;
    else if(rx==cur->x && (px-6)/12+nowLHy > cur->y)
        ry=(px-6)/12+nowLHy-1;
    else
        ry=(px-6)/12+nowLHy;

    int press_x,press_y;
    press_x=cur->x,press_y=cur->y;

    setCursorPos(rx,ry);

    //BS
    int release_x=cur->x,release_y=cur->y;
    if(release_x!=press_x || release_y!=press_y){
        if(release_x<press_x)
            bs->active(release_x,release_y,press_x,press_y,findRow(release_x));
        else if(release_x==press_x){
            if(release_y<press_y)
                bs->active(release_x,release_y,press_x,press_y,findRow(release_x));
            else
                bs->active(press_x,press_y,release_x,release_y,findRow(press_x));
        }
        else
            bs->active(press_x,press_y,release_x,release_y,findRow(press_x));
    }

    update();
}

void wordchild::to_find_cha(QString find){

    int i=0,j=0,cout=0,place=-1;
    row * cache = rowHead;
    while(cache!=nullptr){
        QString qst = cache->to_QStr();
//        if(place!=-1)
//            place=qst.indexOf(find,place);
//        else
            place=qst.indexOf(find);
        if(place>=0)
              {

                  QString number =QString::number(i,10);

                this->A->find_result->setItem(cout,0,new QTableWidgetItem(number));  //FIXME:这玩意我还是不会用
                  number =QString::number(place+1,10);
                  this->A->find_result->setItem(cout,1,new QTableWidgetItem(number));  //FIXME:这玩意我还是不会用
                  cout++;
                  }
//        else{
           cache=cache->next;
           place=-1;

        i=i+1;
        j=0;

}
}

void wordchild::to_replace_cha(QString find, QString replace){
    row * cache = rowHead;

    std::cout<<"replacing"<<std::endl;

    while(cache!=nullptr){
        QString qst = cache->to_QStr();
//        std::cout<<cache->text;
        qst.replace(find,replace);
        cache->from_QStr(qst);
//        std::cout<<cache->text;

        cache=cache->next;
    }
    update();
}
/******************************************字体*************************/
void wordchild::openFile()
{
    QString path = QFileDialog::getOpenFileName(this,
                                                tr("Open File"),
                                                ".",
                                                tr("Text Files(*.txt)"));
    if(!path.isEmpty()) {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Read File"),
                                 tr("Cannot open file:\n%1").arg(path));
            return;
        }

        //put func here
        this->rowHead = new row(1);
        row * caccc = rowHead;
        while(!file.atEnd())
        {
            QByteArray line = file.readLine();
            QString str(line);
            str.remove("\n");
            caccc->from_QStr(str);
            if(!file.atEnd())
                caccc->newNext();
            caccc=caccc->next;
        }
        //end func

        file.close();
    } else {
        QMessageBox::warning(this, tr("Path"),
                             tr("You did not select any file."));
    }

    update();
}
