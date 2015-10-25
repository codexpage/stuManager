#include "mainwindow.h"
#include "database.h"
#include <QApplication>
#include<QSplashScreen>
#include<QTimer>
#include<QTextCodec>
#include<iostream>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pixmap(":/new/logo/tianda.png");
    QSplashScreen splash(pixmap);
    splash.show();


    MainWindow w;
    w.setWindowOpacity(0);
//    w.showMaximized();//最大化
    QTimer::singleShot(500, &splash, SLOT(close()));
    QTimer::singleShot(500, &w, SLOT(sh()));


    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8")) ;//防乱码

    if(!createConnection())//创建数据库 并且连接 初始化数据库
    {
        std::cout<<"can't connect to the database"<<std::endl;
        return 1;//不成功则退出
    }

    w.show();






    return a.exec();
}

