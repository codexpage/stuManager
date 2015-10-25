#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QMainWindow>
#include<QWidget>
#include<QSplitter>
#include<QSqlRelationalTableModel>

namespace Ui {
class studentWindow;
}

class studentWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit studentWindow(int sid,QWidget *parent = 0);
    ~studentWindow();

    QSqlRelationalTableModel *model;

    void refresh(int sid);
private slots:
    void on_pushButton_clicked();

    void on_btnsort_clicked();
    void exit();

    void on_pushButton_2_clicked();

private:
    Ui::studentWindow *ui;
    int stuid;
};

#endif // STUDENTWINDOW_H
