#ifndef WORD_H
#define WORD_H

#include <QMainWindow>
#include"QMdiArea"
#include"QMenu"
#include<QMenuBar>
#include<QAction>
#include<QToolBar>
#include<QDialog>
#include<QPushButton>
#include<QIcon>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QGridLayout>
#include<QLineEdit>
#include<QLabel>
class QComboBox;
class QFontComboBox;
class QMdiSubWindow;
class QMdiArea;
class wordchild;

namespace Ui {
class word;
}

class word : public QMainWindow
{

    Q_OBJECT

public:
    explicit word(QWidget *parent = 0);

    ~word();

private:
    int bold_couting=0;//粗体计数
        int ita_couting=0;//斜体计数
        int up_couting=0;//
        int under_couting=0;
    Ui::word *ui;
    wordchild *activechild();
    void creatActions();
    void creatMenus();
    void creatToolBars();
    void creatStatusBar();
    void enabledText();
    void closeEvent(QCloseEvent *event);
void creatchild();
    QMdiArea *mdiArea;
    QScrollBar *verticalScrollBar;
    QScrollBar *horizenScrollBar;
    QMenu *fileMenu;
    QMenu *homeMenu;
    QMenu *formatMenu;
    QMenu *windowMenu;
    QMenu *helpMenu;
    QMenu *setMenu;
    //文件菜单动作集
    QAction *NewAct;
    QAction *OpenAct;
    QAction *SaveAct;
    QAction *SaveasAct;
    QAction *PrintAct;
    QAction *PrintPreviewAct;
    QAction *ExitAct;
    //主页菜单动作集
    QAction *UndoAct;
    QAction *RedoAct;
    QAction *CutAct;
    QAction *CopyAct;
    QAction *PasteAct;
    QAction *Find_replace;
    //格式菜单动作集
    QAction *BoldAct;
    QAction *ItalicAct;
    QAction *UnderlineAct;
    QAction *LeftalignAct;
    QAction *CenterAct;
    QAction *RightalignAct;
    QAction *JustifyAct;
    QAction *ColorAct;
    //窗口菜单动作集
    QAction *CloseAct;
    QAction *CloseallAct;
    QAction *TileAct;
    QAction *CascadeAct;
    QAction *NextAct;
    QAction *PreviousAct;
    QAction *SeparatorAct;
    //设置菜单动作集
    QAction *SetthemeAct;
    QAction *SetAct;
    //帮助菜单动作集
    QAction *AboutAct;
    QAction *find_replaceAct;
    //工具栏
    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QToolBar *formatToolBar;
    QToolBar *comboToolBar;
    QComboBox *comboStyle;
    QFontComboBox *comboFont;
    QComboBox *comboSize;
    //查找子窗口
        QMdiSubWindow *findwordchild(const QString &fileName);
private slots:
    void textAlign(QAction *a);
    void about();
    void fileNew();                 //新建文件
    //void fileOpen();
    void fileSave();
    void fileSaveAs();
    void fileOpen();
    wordchild *creatwordchild();    //创建子窗口

    void set_font_function(QString);
         void set_blod_function();
         void set_color_function();
         void set_size_function(QString );
         void set_underline_function();
    void updateMenus();
void Find_replace_fun();
void Cut();
void Paste();
void Copy();

};

#endif // WORD_H
