#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include<QSql>
#include<QSqlError>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QtNetwork>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool openDatabase();

private slots:
    void on_pushButton_clicked();
    void acceptConnection();
    void receiveData();

private:
    Ui::MainWindow *ui;
    QTcpSocket *tcpSocket;
    QTcpServer *tcpServer;
    QString showText;
    QSqlDatabase db;
    void init();

};

#endif // MAINWINDOW_H
