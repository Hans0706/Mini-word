#include "word.h"
#include"wordchild.h"
#include "ui_word.h"
#include"form.h"
#include"wordchild.h"
#include <QtWidgets>
#include <QIcon>
#include <QFont>
#include <QPixmap>
#include<QTableWidgetItem>
#include<QComboBox>
#include<QMdiSubWindow>
#include<QMdiArea>
const QString rsrcPath=":/images";


word::word(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::word)
{

    ui->setupUi(this);
    mdiArea=ui->mdiArea;

    this->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(this->mdiArea);
    connect(mdiArea,SIGNAL(subWindowActivated(QMdiSubWindow*)),this,SLOT(updateMenus()));
connect(ui->verticalScrollBar,SIGNAL(valueChanged(int)),this,SLOT(slot_ScroolWidget(int)));
    move(200,150);
    resize(800,500);
    setWindowTitle(tr("mini-word"));
    creatActions();
    creatMenus();
    creatToolBars();

}

word::~word()
{
    delete ui;
}
//void word::updateWindowMenu(){}
void word::creatActions()
{
    //"FILE“主菜单动作集
    NewAct=new QAction(QIcon( ":/filenew.png"),tr("New"),this);
    NewAct->setShortcuts(QKeySequence::New);
    NewAct->setToolTip("New");
    NewAct->setStatusTip(tr("Create a new document "));
   connect(NewAct,SIGNAL(triggered()),this,SLOT(fileNew()));
   //Open
    OpenAct=new QAction(    QIcon("://open-file.png"),tr("Open"),this);
    OpenAct->setShortcuts(QKeySequence::Save);
    OpenAct->setToolTip("Open");
    OpenAct->setStatusTip(tr("Open a document"));
   connect(OpenAct,SIGNAL(triggered()),this,SLOT(fileOpen()));
    SaveAct=new QAction(QIcon(":/filesave.png"),tr("Save"),this);
    SaveAct->setShortcuts(QKeySequence::Save);
    SaveAct->setToolTip("Save");
    SaveAct->setStatusTip(tr("Save the document"));
   connect(SaveAct,SIGNAL(triggered()),this,SLOT(fileSave()));
   SaveasAct=new QAction(QIcon(":/filesaveAs.png"),tr("Save As"),this);
   SaveasAct->setShortcuts(QKeySequence::SaveAs);
   SaveasAct->setToolTip("Save As");
   SaveasAct->setStatusTip(tr("Save this as a new document"));
   connect(SaveasAct,SIGNAL(triggered()),this,SLOT(fileSaveAs()));
     ExitAct=new QAction(tr("Exit"),this);
     ExitAct->setShortcuts(QKeySequence::Quit);
     ExitAct->setStatusTip(tr("Quit the exe"));
    connect(ExitAct,SIGNAL(triggered()),qApp,SLOT(closeAllWindows()));

     //"Home"菜单动作集

     CutAct=new QAction(QIcon(":/editcut.png"),tr("Cut"),this);
     CutAct->setShortcut(QKeySequence::Cut);
     CutAct->setToolTip("Cut");
     CutAct->setStatusTip(tr("Cut the selected content and put it into the shear plate."));
     connect(CutAct,SIGNAL(triggered()),this,SLOT(Cut()));
     CopyAct=new QAction(QIcon(":/edit-copy.png"),tr("Copy"),this);
     CopyAct->setShortcut(QKeySequence::Copy);
     CopyAct->setToolTip("Copy");
     CopyAct->setStatusTip(tr("Copy the selected content and put it into the shear plate."));
     connect(CopyAct,SIGNAL(triggered()),this,SLOT(Copy()));
     PasteAct=new QAction(QIcon(":/editpaste.png"),tr("Paste"),this);
     PasteAct->setShortcut(QKeySequence::Paste);
     PasteAct->setToolTip("Paste");
     PasteAct->setStatusTip(tr("Paste content from the shear plate."));
     connect(PasteAct,SIGNAL(triggered()),this,SLOT(Paste()));
    Find_replace=new QAction(QIcon(":/find.png"),tr("Find or Replace"),this);
    Find_replace->setStatusTip(tr("Find or Replace"));
    Find_replace->setShortcut(tr("Ctrl+F"));
    connect(Find_replace,SIGNAL(triggered()),this,SLOT(Find_replace_fun()));        //查找替换函数
     //"Format"菜单动作集
     BoldAct=new QAction(QIcon(":/textbold.png"),tr("Bold"),this);
     BoldAct->setCheckable(true);
     BoldAct->setShortcut(Qt::CTRL+Qt::Key_B);
     BoldAct->setToolTip("Bold");
     BoldAct->setStatusTip(tr("Bold the selected content."));
     QFont bold;
     bold.setBold(true);
     BoldAct->setFont(bold);
     connect(BoldAct,SIGNAL(triggered()),this,SLOT(set_blod_function()));

     UnderlineAct=new QAction(QIcon(":/textunder.png"),tr("Underline"),this);
     UnderlineAct->setCheckable(true);
     UnderlineAct->setShortcut(Qt::CTRL+Qt::Key_U);
     UnderlineAct->setToolTip("Underline");
     UnderlineAct->setStatusTip(tr("Underline the selected content."));
     QFont underline;
     underline.setUnderline(true);
     UnderlineAct->setFont(underline);
     connect(UnderlineAct,SIGNAL(triggered()),this,SLOT(set_underline_function()));

     //Format->Group 子菜单下的各项为同一个菜单项组。只能选其中一项
     QActionGroup *grp=new QActionGroup(this);
     connect(grp,SIGNAL(triggered(QAction*)),this, SLOT(textAlign(QAction*)));

     if(QApplication::isLeftToRight())
     {
         LeftalignAct=new QAction(QIcon(":/textleft.png"),tr("Left"),grp);
         CenterAct=new QAction(QIcon(":/textcenter.png"),tr("Center"),grp);
         RightalignAct=new QAction(QIcon(":/textright.png"),tr("Right"),grp);

     }
     else
     {
         RightalignAct=new QAction(QIcon(":/textright.png"),tr("Right"),grp);
          CenterAct=new QAction(QIcon(":/textcenter.png"),tr("Center"),grp);
            LeftalignAct=new QAction(QIcon(":/textleft.png"),tr("Left"),grp);
     }
    JustifyAct=new QAction(QIcon(":/textjustify.png"),tr("Justify"),grp);    //两端对齐
    LeftalignAct->setShortcut(Qt::CTRL+Qt::Key_E);
    LeftalignAct->setCheckable(true);
    LeftalignAct->setToolTip("Left");
    LeftalignAct->setStatusTip(tr("Left the content"));

    CenterAct->setShortcut(Qt::CTRL+Qt::Key_L);
    CenterAct->setCheckable(true);
    CenterAct->setToolTip("Center");
    CenterAct->setStatusTip(tr("Center the content"));

    RightalignAct->setShortcut(Qt::CTRL+Qt::Key_R);
    RightalignAct->setCheckable(true);
    RightalignAct->setToolTip("Right");
    RightalignAct->setStatusTip(tr("Right the content"));

    JustifyAct->setShortcut(Qt::CTRL+Qt::Key_J);
    JustifyAct->setCheckable(true);
    JustifyAct->setToolTip("Justify");
    JustifyAct->setStatusTip(tr("Justify the content"));
    QPixmap pix(16,16);
    pix.fill(Qt::red);
    ColorAct=new QAction(pix,tr("color"),this);
    ColorAct->setToolTip("Color");
    ColorAct->setStatusTip(tr("Set the color of content"));
    connect(ColorAct,SIGNAL(triggered()),this,SLOT(set_color_function()));

    //Window主菜单动作集
    CloseAct=new QAction(tr("Close"),this);
    CloseAct->setStatusTip(tr("Close the window."));
    connect(CloseAct,SIGNAL(triggered()),mdiArea,SLOT(closeActiveSubWindow()));
    CloseallAct=new QAction(tr("Close All"),this);
    CloseallAct->setStatusTip(tr("Close all the windows."));
    connect(CloseallAct,SIGNAL(triggered()),mdiArea,SLOT(closeAllSubWindows()));
    TileAct=new QAction(tr("Tile"),this);           //平铺
    TileAct->setStatusTip(tr("Tile the windows."));
    connect(TileAct,SIGNAL(triggered()),mdiArea,SLOT(tileSubWindows()));
    CascadeAct=new QAction(tr("Cascade"),this);           //层叠
    CascadeAct->setStatusTip(tr("Cascade the windows."));
    connect(CascadeAct,SIGNAL(triggered()),mdiArea,SLOT(cascadeSubWindows()));
    NextAct=new QAction(tr("Next"),this);      //下一个
    NextAct->setShortcuts(QKeySequence::NextChild);
    NextAct->setStatusTip(tr("Move to the next subwindow."));
    connect(NextAct,SIGNAL(triggered()),mdiArea,SLOT(activateNextSubWindow()));
    PreviousAct=new QAction(tr("Previous"),this);      //下一个
    PreviousAct->setShortcuts(QKeySequence::PreviousChild);
    PreviousAct->setStatusTip(tr("Move to the last subwindow."));
    connect(PreviousAct,SIGNAL(triggered()),mdiArea,SLOT(activatePreviousSubWindow()));
    SeparatorAct=new QAction(this);
    SeparatorAct->setSeparator(true);

    //Setting菜单动作集
    SetthemeAct=new QAction(tr("Set theme"),this);
    SetthemeAct->setToolTip("Theme");
    SetthemeAct->setStatusTip(tr("Set the main theme."));

    SetAct=new QAction(tr("Save automatically."),this);
    SetAct->setToolTip("Save");
    SetAct->setStatusTip(tr("Save the document automatically."));


    //Help菜单动作集
    AboutAct=new QAction(tr("About"),this);
    AboutAct->setStatusTip(tr("About mini-word"));
    connect(AboutAct,SIGNAL(triggered(bool)),this,SLOT(about()));
find_replaceAct= new QAction(QIcon(":/pic/search.ico"),tr("Find and Replace"),this);
find_replaceAct->setStatusTip(tr("Find And Replace"));
find_replaceAct->setShortcut(tr("Ctrl+F"));
connect(find_replaceAct,SIGNAL(triggered()),this,SLOT(Find_replace_fun()));
}
void word::creatMenus()
{
    //File Menu


    fileMenu=menuBar()->addMenu(tr("File"));
    fileMenu->addAction(NewAct);
    fileMenu->addAction(OpenAct);
    fileMenu->addSeparator();       //分割线
    fileMenu->addAction(SaveAct);
    fileMenu->addAction(SaveasAct);
    fileMenu->addSeparator();       //分割线

    fileMenu->addAction(ExitAct);

    //Home Menu
    homeMenu=menuBar()->addMenu((tr("Home")));


    homeMenu->addAction(CutAct);
    homeMenu->addSeparator();    //分割线
    homeMenu->addAction(CopyAct);
    homeMenu->addSeparator();    //分割线
    homeMenu->addAction(PasteAct);
    homeMenu->addSeparator();    //分割线

    //Format Menu
    formatMenu=menuBar()->addMenu((tr("Format")));
    QMenu *fmenu=formatMenu->addMenu(tr("Font"));
    fmenu->addAction(BoldAct);
    fmenu->addSeparator();    //分割线

    fmenu->addSeparator();    //分割线
    fmenu->addAction(UnderlineAct);
    QMenu* alignMenu=formatMenu->addMenu(tr("Section"));

    formatMenu->addAction(ColorAct);

    //Window Menu
    windowMenu=menuBar()->addMenu(tr("Window"));
   windowMenu->addAction(CloseAct);
   windowMenu->addAction(CloseallAct);
    windowMenu->addAction(TileAct);
     windowMenu->addAction(CascadeAct);
      windowMenu->addAction(NextAct);
       windowMenu->addAction(PreviousAct);
        windowMenu->addAction(SeparatorAct);
    connect(windowMenu,SIGNAL(aboutToShow()),this,SLOT(updateMenus()));
    menuBar()->addSeparator();

    //Setting Menu
    setMenu=menuBar()->addMenu(tr("Setting"));
    setMenu->addAction(SetAct);
    setMenu->addSeparator();    //分割线
    setMenu->addAction(SetthemeAct);
    //Help Menu
    helpMenu=menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(AboutAct);
helpMenu->addAction(find_replaceAct);
}
void word::creatToolBars()
{
    //file
    fileToolBar=addToolBar(tr("File"));
    fileToolBar->addAction(NewAct);
    fileToolBar->addAction(OpenAct);
    fileToolBar->addAction(SaveAct);


    //edit
    editToolBar=addToolBar(tr("Edit"));

    editToolBar->addAction(CutAct);

    editToolBar->addAction(CopyAct);
    editToolBar->addAction(PasteAct);
    //format
    formatToolBar=addToolBar(tr("Format"));
    formatToolBar->addAction(BoldAct);

    formatToolBar->addAction(UnderlineAct);
    formatToolBar->addSeparator();
    formatToolBar->addAction(LeftalignAct);
   formatToolBar->addAction(CenterAct);
    formatToolBar->addAction(RightalignAct);
    formatToolBar->addAction(JustifyAct);
    formatToolBar->addSeparator();
    formatToolBar->addAction(ColorAct);
    //combine
    addToolBarBreak(Qt::TopToolBarArea);
    comboToolBar=addToolBar(tr("Combination"));



   comboFont=new QFontComboBox();
   comboToolBar->addWidget(comboFont);
   comboFont->setStatusTip("Change the font");
   connect(comboFont,SIGNAL(activated(QString)),this,SLOT(set_font_function(QString)));
   comboSize=new QComboBox();
   comboToolBar->addWidget(comboSize);
   comboSize->setEditable(true);
   comboFont->setStatusTip("Change the size");
    QFontDatabase db;
    foreach(int size,db.standardSizes());
 //  comboSize->addItem(QString::number(size));

   connect(comboSize,SIGNAL(activated(int)),this,SLOT(set_size_function(QString)));
   comboSize->setCurrentIndex(comboSize->findText(QString::number(QApplication::font().pointSize())));
formatToolBar=addToolBar("Font");




}

void word::textAlign(QAction *a){}
void word::about()
{
    QMessageBox::about(this,tr("About"),tr("This is a software based on QT which aquired the functions such as office word,"));
}



void word::fileNew()
{
    wordchild *child=new wordchild;

     this->mdiArea->addSubWindow(child);

    child->newFile();

    child->show();
    enabledText();

}

void word::enabledText()
{
    BoldAct->setEnabled(true);

    UnderlineAct ->setEnabled(true);
    LeftalignAct->setEnabled(true);
    CenterAct->setEnabled(true);
    RightalignAct->setEnabled(true);
    JustifyAct->setEnabled(true);
    ColorAct->setEnabled(true);
}
void word::Find_replace_fun()
{
    Form * a=new Form;
    this->activechild()->A= a;
    a->show();
    connect(this->activechild()->A,SIGNAL(send_find_data(QString)),this->activechild(),SLOT(to_find_cha(QString)));
      connect(this->activechild()->A,SIGNAL(send_replace_data(QString,QString)),this->activechild(),SLOT(to_replace_cha(QString,QString)));    //将窗体和信号连接
}
void word::closeEvent(QCloseEvent *event)
{
    this->mdiArea->closeAllSubWindows();
    if(this->mdiArea->currentSubWindow())
    {
        event->ignore();

    }
    else{
        event->accept();
    }

}
wordchild *word::activechild()
{
    //if there iss
    if(QMdiSubWindow *activeSubWindow=mdiArea->activeSubWindow())
        return qobject_cast<wordchild *>(activeSubWindow->widget());
    return 0;
}
wordchild *word::creatwordchild()
{
    wordchild *child=new wordchild;

}
void word::updateMenus()
{
    bool hasMychild=(activechild()!=0);

}

void word::creatStatusBar()
{
    statusBar()->showMessage(tr("Ready."));
}

void word::fileOpen()
{
    //建立子窗口
    wordchild *child=new wordchild;

          this->mdiArea->addSubWindow(child);
        child->openFile();
        child->isUntitled=true;
        child->show();
        child->update();
child->setCurrentFile(child->rowHead->getfilename());
}

void word::fileSave()
{
    if(activechild() && activechild()->save()){

        statusBar()->showMessage(tr("保存成功"), 2000);
           QMessageBox::warning (this,tr("提示信息"),tr("保存成功"));
           }
    else
        {
            QMessageBox::warning(this,tr("提示信息"),tr("保存失败，请重新保存"));
        }
}

void word::fileSaveAs()
{
    if(activechild() && activechild()->saveAs())
        statusBar()->showMessage(tr("保存成功"), 2000);
    else
      {
          QMessageBox::warning(this,tr("提示信息"),tr("保存失败，请重新保存"));
      }
}
/******************************************字体*************************/
void word::set_blod_function()
{
 wordchild *a=this->activechild();
 if(bold_couting==0 )//之前不是粗体
        {
           a-> the_font.setBold(true);
            bold_couting=1;
    }

        else //之前是粗体
        {
            bold_couting=0;
           a-> the_font.setBold(false);
        }
  this->activechild()->update();
}




void word::set_font_function(QString qname)
{
    wordchild *a=this->activechild();
    a->the_font.setFamily(qname);
     this->activechild()->update();
}

void word::set_size_function(QString qsize)
{
      int size =qsize.toInt();
    wordchild *a=this->activechild();
    a->the_font.setPixelSize(size);
      this->activechild()->update();
}

void word::set_color_function()
{
    if(activechild())
      {
          QColor col=QColorDialog::getColor(Qt::blue);
          if(col.isValid())
          {//颜色合法
 wordchild *a=this->activechild();
 a-> the_color=col;
        this->activechild()->update();
          }
    }
}

void word::set_underline_function()
{
    wordchild *a=this->activechild();
    if(under_couting==0 )//之前不是下划线
            {
               a-> the_font.setUnderline(true);
                under_couting=1;
            }
            else //之前是粗体
            {
                under_couting=0;
               a-> the_font.setUnderline(false);
            }

    this->activechild()->update();
   }

void word::Cut()
{
     wordchild *a=this->activechild();
   a->cut();
}

void word::Copy()
{
    wordchild *a=this->activechild();
  a->copy();
}
void word::Paste()
{
    wordchild *a=this->activechild();
  a->paste();
}
