#include "teacherwindow.h"
#include "ui_teacherwindow.h"
#include<QMessageBox>
#include<QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include<QtDebug>
#include<QTextCodec>
#include<iostream>
#include<QSqlRelationalTableModel>
#include<QSqlRecord>
#include"mainwindow.h"
using namespace std;

teacherWindow::teacherWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::teacherWindow)
{
    ui->setupUi(this);
    connect(ui->list,SIGNAL(currentRowChanged(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));



    //====student info======
    model=new QSqlRelationalTableModel(this);
    model->setTable("student");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);//保存策略：手动调用submit保存
    model->select();
//    model->removeColumn(1);
    ui->tableView->setModel(model);
//    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//不可编辑
    //====student info end=====

    //=====courseinfo====
    coursemodel=new QSqlRelationalTableModel(this);
    coursemodel->setTable("course");
    coursemodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    coursemodel->select();
    ui->tableView_2->setModel(coursemodel);
    //====courseinfo end===

    //====grade by course====
    QSqlQuery query;
    query.exec(QObject::tr("select coursename from course"));
    while(query.next()){
//        qDebug()<<"query is at "<<query.at()<<endl;
        QString tmp=query.value("coursename").toString();
        ui->ComboCourse->addItem(tmp);
    }


//    ui->ComboCourse->addItem("数据结构");
    grademodel=new QSqlRelationalTableModel(this);
    grademodel->setTable("grade");
    grademodel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //ralation here
    grademodel->setRelation(1,QSqlRelation("student","id","name"));
    grademodel->setRelation(2,QSqlRelation("course","courseid","coursename"));
    grademodel->setRelation(3,QSqlRelation("course","courseid","weight"));

    grademodel->select();
    ui->tableView_3->setModel(grademodel);
    ui->tableView_3->setItemDelegate(new QSqlRelationalDelegate(ui->tableView_3));

    grademodel->setJoinMode(QSqlRelationalTableModel::LeftJoin);//显示带null值的记录
    //====grade by course end===
}

teacherWindow::~teacherWindow()
{
    delete ui;
}


void teacherWindow::on_BtnSubmit_clicked()
{
    model->database().transaction(); //开始事务操作

        if (model->submitAll()) {
            model->database().commit(); //提交
        } else {
            model->database().rollback(); //回滚
            QMessageBox::warning(this, tr("tableModel"),tr("数据库错误: %1").arg(model->lastError().text()));
        }
}

void teacherWindow::on_BtnRevert_clicked()
{
    model->revertAll();
}


void teacherWindow::on_BtnAdd_clicked()
{
    int rowNum = model->rowCount(); //获得表的行数
         int id = rowNum;
          model->insertRow(rowNum); //添加一行
          model->setData(model->index(rowNum,0),id);//核心：把某一行某一列的值设为id
          //model->submitAll(); //可以直接提交
}

void teacherWindow::on_BtnDelete_clicked()//delete student
{
    int curRow = ui->tableView->currentIndex().row();
    int id=model->record(curRow).value("id").toInt();
        //获取选中的行
        model->removeRow(curRow);
        //删除该行
        int ok = QMessageBox::warning(this,tr("删除当前行!"),tr("你确定"
                                                               "删除当前行吗？"),
                             QMessageBox::Yes,QMessageBox::No);
        if(ok == QMessageBox::No)
        {
           model->revertAll(); //如果不删除，则撤销
        }
        else {
            model->submitAll(); //否则提交，在数据库中删除该行
            QSqlQuery qq;
            qq.exec(QObject::tr("delete from user where userid=%1").arg(id));//级联删除
            qq.exec(QObject::tr("delete from grade where id=%1").arg(id));
            grademodel->select();

        }
}

void teacherWindow::on_BtnAsend_clicked()
{
    model->setSort(0,Qt::AscendingOrder); //id属性，即第0列，升序排列
    model->select();
}

void teacherWindow::on_BtnDesend_clicked()
{
    model->setSort(0,Qt::DescendingOrder); //降序
    model->select();
}

void teacherWindow::on_BtnFindByID_clicked()
{
    QString id = ui->EditID->text();
    model->setFilter(QObject::tr("id = '%1'").arg(id)); //根据姓名进行筛选
    model->select(); //显示结果
}

void teacherWindow::on_BtnFindByName_clicked()
{
    QString name = ui->EditName->text();
    model->setFilter(QObject::tr("name = '%1'").arg(name)); //根据姓名进行筛选
    model->select(); //显示结果
}

void teacherWindow::on_BtnFindByDom_clicked()
{
    QString dom = ui->EditDom->text();
    model->setFilter(QObject::tr("dom = '%1'").arg(dom)); //根据宿舍进行筛选
    model->select(); //显示结果
}

void teacherWindow::on_BtnBack_clicked()
{
    model->setTable("student");   //重新关联表
    model->select();   //这样才能再次显示整个表的内容
}

void teacherWindow::on_ComboCourse_currentIndexChanged(const QString &arg1)
{
//    char a[10];
//    strcpy(a,arg1.toStdString().c_str());
//    qDebug()<<QObject::tr(arg1.toStdString().c_str())<<endl;
//        qDebug()<<QObject::tr("中文");
//        qDebug() << QString::fromUtf8("中文zhongwen");
//        qDebug()<<QTextCodec::codecForName("GB2312")->fromUnicode(QTextCodec::codecForName("UTF-8")->toUnicode("中文显示"));
    //以上方法经过尝试一个都不对 会乱码

//    QSqlQuery qu;
//    qu.exec(QObject::tr("select courseid from course where coursename = '%1'").arg(arg1));
//    qu.next();
//    QString str=qu.value(0).toString();
//    cout<<"筛选课程:"<<arg1.toStdString()<<"筛选id:"<<str.toStdString()<<endl;


//    coursemodel->setFilter(QObject::tr("courseid = %1").arg(str));

    //在这这里的两句话只要写了就会崩溃
    //    grademodel->setFilter(QObject::tr("courseid = 1"));
    //    grademodel->select();


}

void teacherWindow::on_shaixuan_clicked()
{


    QString name=ui->ComboCourse->currentText();
    QSqlQuery qu;
    qu.exec(QObject::tr("select courseid from course where coursename = '%1'").arg(name));
    qu.next();
    QString str=qu.value(0).toString();

    cout<<"筛选课程:"<<name.toStdString()<<"筛选id:"<<str.toStdString()<<QObject::tr("courseid = %1").arg(str.toInt()).toStdString()<<endl;
    grademodel->setFilter(QObject::tr("relTblAl_2.coursename = '%1'").arg(name));
    //这里有一个隐蔽的qt本身的问题，在使用QSqlrationaltalbeModel 时设置的多个外键，这个时候model里已经有了多张表了，在用filter时要在字段名字前加表名，
    //而对于外键的字段，想要filter还不能直接用名字，要用relTblAl_x x表示是第几column的字段，否则只要多个外键中有相同的filed名字 程序就会出错，什么都搜不出来
    //参考：http://blog.csdn.net/zhangzhenhu/article/details/6451980
//    grademodel->setFilter(QObject::tr("courseid = %1").arg(str.toInt()));
    grademodel->select();
}

void teacherWindow::on_BtnCal_clicked()
{
 QSqlRecord r;
 for(int i=0;i<grademodel->rowCount();i++){
     r=grademodel->record(i);
//     qDebug()<<r<<endl;
     qDebug()<<r.value("regulargrade")<<endl;
     qDebug()<<r.value("examgrade").toInt()<<endl;
     double regulargrade=r.value("regulargrade").toDouble();
     double expgrade=r.value("expgrade").toDouble();
     double examgrade=r.value("examgrade").toDouble();
     int weight=r.value("weight").toInt();
     double totalgrade=0;
     double gpa=0;
     if(regulargrade!=0){
         if(expgrade==-1)
         {
             totalgrade=regulargrade*0.3+examgrade*0.7;
         }
         else
         {
             totalgrade=regulargrade*0.15+expgrade*0.15+examgrade*0.7;
         }

         switch ((int)totalgrade/10) {
         case 10:
             gpa=weight;
             break;
         case 9:
             gpa=weight;
             break;
         case 8:
             gpa=weight*0.8;
             break;
         case 7:
             gpa=weight*0.75;
             break;
         case 6:
             gpa=weight*0.6;
             break;
         default:
             gpa=0;
             break;
         }
         r.setValue("totalgrade",totalgrade);
         r.setValue("gpa",gpa);
         grademodel->setRecord(i,r);

     }

 }
}

void teacherWindow::on_BtnSubmit_3_clicked()
{
    grademodel->database().transaction(); //开始事务操作

        if (grademodel->submitAll()) {
            grademodel->database().commit(); //提交
        } else {
            grademodel->database().rollback(); //回滚
            QMessageBox::warning(this, tr("tableModel"),tr("数据库错误: %1").arg(grademodel->lastError().text()));
        }
}

void teacherWindow::on_BtnRevert_3_clicked()
{
    grademodel->revertAll();
}

void teacherWindow::on_BtnSubmit_2_clicked()
{
    coursemodel->database().transaction(); //开始事务操作

        if (coursemodel->submitAll()) {
            coursemodel->database().commit(); //提交
        } else {
            coursemodel->database().rollback(); //回滚
            QMessageBox::warning(this, tr("tableModel"),tr("数据库错误: %1").arg(coursemodel->lastError().text()));
        }
}

void teacherWindow::on_BtnRevert_2_clicked()
{
    coursemodel->revertAll();
}

void teacherWindow::on_BtnAddCourse_clicked()
{
    int rowNum = coursemodel->rowCount(); //获得表的行数
         int id = rowNum;
          coursemodel->insertRow(rowNum); //添加一行
          coursemodel->setData(coursemodel->index(rowNum,0),id);//核心：把某一行某一列的值设为id
          //model->submitAll(); //可以直接提交
}

void teacherWindow::on_BtnDeleteCourse_clicked()//delete course
{
    int curRow = ui->tableView_2->currentIndex().row();
    int cid=coursemodel->record(curRow).value("courseid").toInt();


        //获取选中的行
        coursemodel->removeRow(curRow);
        //删除该行
        int ok = QMessageBox::warning(this,tr("删除当前行!"),tr("你确定"
                                                               "删除当前行吗？"),
                             QMessageBox::Yes,QMessageBox::No);
        if(ok == QMessageBox::No)
        {
           coursemodel->revertAll(); //如果不删除，则撤销
        }
        else {
            coursemodel->submitAll(); //否则提交，在数据库中删除该行
            QSqlQuery qq;
            qq.exec(QObject::tr("delete from grade where courseid=%1").arg(cid));//级联删除
            grademodel->select();
        }
}

void teacherWindow::on_pushButton_clicked()
{
    MainWindow *mw=new MainWindow();
    mw->show();
    this->close();
}
