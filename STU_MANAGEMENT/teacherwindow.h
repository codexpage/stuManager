#ifndef TEACHERWINDOW_H
#define TEACHERWINDOW_H

#include <QMainWindow>
#include<QSqlTableModel>
#include<QSqlRelationalTableModel>
#include<QSqlRelationalDelegate>

namespace Ui {
class teacherWindow;
}

class teacherWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit teacherWindow(QWidget *parent = 0);
    ~teacherWindow();

private slots:

    void on_BtnRevert_clicked();

    void on_BtnSubmit_clicked();

    void on_BtnAdd_clicked();

    void on_BtnDelete_clicked();

    void on_BtnAsend_clicked();

    void on_BtnDesend_clicked();

    void on_BtnFindByID_clicked();

    void on_BtnFindByName_clicked();

    void on_BtnFindByDom_clicked();

    void on_BtnBack_clicked();

    void on_ComboCourse_currentIndexChanged(const QString &arg1);

    void on_shaixuan_clicked();

    void on_BtnCal_clicked();

    void on_BtnSubmit_3_clicked();

    void on_BtnRevert_3_clicked();

    void on_BtnSubmit_2_clicked();

    void on_BtnRevert_2_clicked();

    void on_BtnAddCourse_clicked();

    void on_BtnDeleteCourse_clicked();

    void on_pushButton_clicked();

private:
    Ui::teacherWindow *ui;
     QSqlRelationalTableModel *model;
     QSqlRelationalTableModel *coursemodel;
     QSqlRelationalTableModel *grademodel;
};

#endif // TEACHERWINDOW_H
