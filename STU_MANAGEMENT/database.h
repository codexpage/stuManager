#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QObject>
#include<iostream>
static bool createConnection()
{
    std::cout<<"ywx"<<std::endl;

    //在这里初始化数据库连接并且   建表
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");
    if(!db.open()) return false;
    QSqlQuery query;
    query.exec(QObject::tr("create table student (id int primary key, name vchar,dom vchar,sex int,school vchar,specialty vchar,inyear int,class int,province vchar,email vchar)"));
    query.exec(QObject::tr("insert into student values(13216080,'刘敏','101',0,'计算机','计算机',2013,3,'湖北','lm@tju.edu.cn')"));
    query.exec(QObject::tr("insert into student values(13216081,'承钢','101',1,'软件','软工',2013,1,'上海','cg@tju.edu.cn')"));
    query.exec(QObject::tr("insert into student values(13216082,'王红','102',0,'软件','软工',2013,4,'广东','wh@tju.edu.cn')"));
    query.exec(QObject::tr("insert into student values(13216083,'木易','102',1,'计算机','计算机',2013,3,'江苏','ywx@tju.edu.cn')"));

    query.exec(QObject::tr("create table course (courseid int primary key, coursename vchar, weight int)"));
    query.exec(QObject::tr("insert into course values(0,'数据结构',4)"));
    query.exec(QObject::tr("insert into course values(1,'算法设计',4)"));
    query.exec(QObject::tr("insert into course values(2,'数据库',3)"));
    query.exec(QObject::tr("insert into course values(3,'人工智能',2)"));

    query.exec(QObject::tr("create table grade (gradeid int primary key, id int, courseid int, weightid int, regulargrade double, expgrade double,examgrade double,totalgrade double, gpa double)"));
    query.exec(QObject::tr("insert into grade values(0,13216080,1,1,0,0,0,0,0)"));
    query.exec(QObject::tr("insert into grade values(1,13216080,2,2,0,0,0,0,0)"));
    query.exec(QObject::tr("insert into grade values(2,13216081,0,0,0,0,0,0,0)"));
    query.exec(QObject::tr("insert into grade values(3,13216081,3,3,0,0,0,0,0)"));
    query.exec(QObject::tr("insert into grade values(4,13216082,0,0,0,0,0,0,0)"));
    query.exec(QObject::tr("insert into grade values(5,13216082,1,1,0,0,0,0,0)"));
    query.exec(QObject::tr("insert into grade values(6,13216082,2,2,0,0,0,0,0)"));
    query.exec(QObject::tr("insert into grade values(7,13216082,3,3,0,0,0,0,0)"));
    query.exec(QObject::tr("insert into grade values(8,13216083,0,0,0,0,0,0,0)"));
    query.exec(QObject::tr("insert into grade values(9,13216083,1,1,0,0,0,0,0)"));
    query.exec(QObject::tr("insert into grade values(10,13216083,2,2,0,0,0,0,0)"));
    query.exec(QObject::tr("insert into grade values(11,13216083,3,3,0,0,0,0,0)"));

    query.exec(QObject::tr("create table user (userid int primary key, password varchar)"));
    query.exec(QObject::tr("insert into user values(13216080,'123')"));
    query.exec(QObject::tr("insert into user values(13216081,'123')"));
    query.exec(QObject::tr("insert into user values(13216082,'123')"));
    query.exec(QObject::tr("insert into user values(13216083,'123')"));

    return true;
}
#endif // DATABASE_H

