#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "studentwindow.h"
#include "teacherwindow.h"

#include<QMessageBox>
#include<QSqlQuery>
#include<QtDebug>
#include<QBitmap>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->passwordEdit->setEchoMode( QLineEdit::Password );

    ui->buttonGroup->setId(ui->BtnTeacher,0);
    ui->buttonGroup->setId(ui->BtnStudent,1);



    //setWindowFlags(Qt::FramelessWindowHint);//这句会去掉标题栏 } 注意:mask的图多余部分设为白色

    //setAttribute(Qt::WA_TranslucentBackground, true);//设置背景全透明
//    ui->radioButton->setChecked(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sh()
{
    setWindowOpacity(1);
}

bool MainWindow::login(){//判断用户名密码
    QString usrname=ui->IDEdit->text();
    QString password=ui->passwordEdit->text();


    //superuser
    if(usrname=="admin"&&password=="admin"){//此处可从数据库中读数据
        return true;
    }

    int type=ui->buttonGroup->checkedId();

    if(type==1){//student
    QSqlQuery qs;
    qs.exec(QObject::tr("select id from student"));//find id
    while(qs.next()){
        if(qs.value("id")==usrname){
            QSqlQuery qq;
            qq.exec(QObject::tr("select password from user where userid=%1").arg(usrname));
            qq.next();
//            qDebug()<<qq.lastError()<endl;
            if(qq.value("password")==ui->passwordEdit->text()){
                qDebug()<<"id: "<<usrname<<endl;
                return true;
            }
        }
    }

    }else{//teacher

    if(usrname=="teacher"&&password=="teacher"){//此处可从数据库中读数据
        return true;
    }
    else{
        return false;
    }

    }

    //superuser
    if(usrname=="admin"&&password=="admin"){//此处可从数据库中读数据
        return true;
    }

}

void MainWindow::on_pushButton_clicked()
{

    int type=ui->buttonGroup->checkedId();
    if(login()){
        if(type==0){//teacher
            teacherWindow *tw =new teacherWindow;
            tw->show();
            this->hide();
        }
        else if(type==1){//student

            int idtmp=ui->IDEdit->text().toInt();
            qDebug()<<"idtmp"<<idtmp<<endl;
             studentWindow *st=new studentWindow(idtmp);
            st->show();
//            this->hide();
            this->close();

        }
    }
    else{
        //弹出密码错误
        QMessageBox::warning(this,tr("用户名或密码错误"),
                 tr("请检查您输入的用户名和密码是否有误"),
                 QMessageBox::Accepted,
                 QMessageBox::Accepted);
    }
}
