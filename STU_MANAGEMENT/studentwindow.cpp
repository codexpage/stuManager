#include "studentwindow.h"
#include "ui_studentwindow.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QSqlError>
#include<iostream>
#include"mainwindow.h"
using namespace std;
void studentWindow::refresh(int sid)
{
    QSqlQuery qq;
    qq.exec(QObject::tr("select * from student where id='%1'").arg(sid));
    qq.next();
    ui->lbname->setText(qq.value("name").toString());
    ui->lbid->setText(qq.value("id").toString());
    ui->lbschool->setText(qq.value("school").toString());
    ui->lbspecialty->setText(qq.value("specialty").toString());
    ui->lbdom->setText(qq.value("dom").toString());
    ui->lbclass->setText(qq.value("class").toString());
    ui->lbmail->setText(qq.value("email").toString());
    ui->lbgrade->setText(qq.value("inyear").toString());
    ui->lbprovince->setText(qq.value("province").toString());
    if(qq.value("sex")==0){
        ui->lbsex->setText("女");
    }
    else{
        ui->lbsex->setText("男");
    }
    qDebug()<<sid<<endl;

    ui->lename->setText(qq.value("name").toString());
    ui->leid->setText(qq.value("id").toString());
    ui->leschool->setText(qq.value("school").toString());
    ui->lespecialty->setText(qq.value("specialty").toString());
    ui->ledom->setText(qq.value("dom").toString());
    ui->lemail->setText(qq.value("email").toString());
    ui->leprovince->setText(qq.value("province").toString());
    if(qq.value("sex").toString()=="0")
    {
        ui->rbwoman->setChecked(true);
    }
    else{
        ui->rbman->setChecked(true);
    }
    ui->sbclass->setValue(qq.value("class").toInt());
    ui->sbgrade->setValue(qq.value("inyear").toInt());

    //
    ui->lbidgrade->setText(QObject::tr("%1").arg(stuid));
    ui->lbnamegrade->setText(QObject::tr("%1").arg(qq.value("name").toString()));
}

studentWindow::studentWindow(int sid,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::studentWindow)
{
    ui->setupUi(this);
//    ui->splitter->setStretchFactor(1,3);
//    ui->splitter->setStretchFactor(1,3);
//    ui->splitter->setAutoFillBackground(true);

//    ui->splitter->setMinimumSize(ui->splitter->minimumSize());
//    ui->splitter->setMaximumSize(ui->splitter->maximumSize());
    connect(ui->list,SIGNAL(currentRowChanged(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
    stuid=sid;

    refresh(sid);


    model=new QSqlRelationalTableModel(this);
    QSqlQuery qq;
    qq.exec(QObject::tr("create view view%1 as SELECT course.coursename as 课程名称 ,course.weight as 学分,grade.regulargrade as 平时成绩,grade.expgrade as 实验成绩,grade.examgrade as 考试成绩,grade.totalgrade as 总成绩,grade.gpa as 所得学分 from course,grade,student where (student.id=grade.id and grade.courseid=course.courseid and student.id=%2)").arg(stuid).arg(stuid));
    model->setTable(QObject::tr("view%1").arg(stuid));
    qDebug()<<model->lastError()<<endl;

    model->setEditStrategy(QSqlTableModel::OnManualSubmit);//保存策略：手动调用submit保存
    model->select();
//    model->removeColumn(1);
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//不可编辑
    cout<<QObject::tr("create view view%1 as SELECT course.coursename as 课程名称 ,course.weight as 学分,grade.regulargrade as 平时成绩,grade.expgrade as 实验成绩,grade.examgrade as 考试成绩,grade.totalgrade as 总成绩,grade.gpa as 所得学分 from course,grade,student where (student.id=grade.id and grade.courseid=course.courseid and student.id=%2)").arg(stuid).arg(stuid).toStdString()<<endl;

    //menu
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(exit()));
}

studentWindow::~studentWindow()
{
    delete ui;
}

void studentWindow::on_pushButton_clicked()//提交修改
{
    QSqlQuery qe;
    qe.exec(QObject::tr("update student set name='%1' where student.id=%2").arg(ui->lename->text()).arg(stuid));
    qe.exec(QObject::tr("update student set id=%1 where student.id=%2").arg(ui->leid->text()).arg(stuid));
    qe.exec(QObject::tr("update student set school='%1' where student.id=%2").arg(ui->leschool->text()).arg(stuid));
    qe.exec(QObject::tr("update student set specialty='%1' where student.id=%2").arg(ui->lespecialty->text()).arg(stuid));
    qe.exec(QObject::tr("update student set dom=%1 where student.id=%2").arg(ui->ledom->text()).arg(stuid));
    qe.exec(QObject::tr("update student set email='%1' where student.id=%2").arg(ui->lemail->text()).arg(stuid));
    qe.exec(QObject::tr("update student set province='%1' where id=%2").arg(ui->leprovince->text()).arg(stuid));
    qe.exec(QObject::tr("update student set inyear=%1 where student.id=%2").arg(ui->sbgrade->text()).arg(stuid));
    qe.exec(QObject::tr("update student set class=%1 where student.id=%2").arg(ui->sbclass->text()).arg(stuid));

    //qDebug()<<QObject::tr("update student set province='%1' where id=%2").arg(ui->leprovince->text()).arg(stuid)<<endl;
    if(ui->rbman->isChecked()){
        qe.exec(QObject::tr("update student set sex=%1 where student.id=%2").arg(1).arg(stuid));
    }
    else{
        qe.exec(QObject::tr("update student set sex=%1 where student.id=%2").arg(0).arg(stuid));
    }
    qDebug()<<"saved:"<<qe.lastError()<<endl;
    refresh(stuid);
}

void studentWindow::on_btnsort_clicked()
{
    model->setSort(5,Qt::AscendingOrder); //totalscore属性，即第0列，升序排列
    model->select();
}

void studentWindow::exit(){
   MainWindow *mw=new MainWindow();
   mw->show();
   this->close();
}

void studentWindow::on_pushButton_2_clicked()
{
    MainWindow *mw=new MainWindow();
    mw->show();
    this->close();
}
