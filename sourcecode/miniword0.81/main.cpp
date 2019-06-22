#include "word.h"
#include <QApplication>
#include <QFile>
#include <QApplication>
#include<QSplashScreen>
class CommonHelper
{
public:
    static void setStyle(const QString &style) {
        QFile qss(style);
        qss.open(QFile::ReadOnly);
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 加载QSS样式
       // CommonHelper::setStyle(":/style.qss");  //古朴纯黑
        // CommonHelper::setStyle(":/black.qss"); //奢靡雅黑
          CommonHelper::setStyle(":/white.qss"); //纯净湖蓝
    word w;
    QSplashScreen *splash=new QSplashScreen;
        QPixmap pix(":/start.png");
        splash->setPixmap(pix);

        splash->showMessage("Loading........");
        splash->show();
        a.processEvents();
                splash->finish(&w);
    w.show();

    return a.exec();
}

