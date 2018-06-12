#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QMouseEvent>
#include <QtNetwork>
#include <QMessageBox>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();



private slots:
    void on_exitButton_clicked();
    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent(QMouseEvent *);
    void on_minButton_clicked();
    void readMessages();
    void on_pushButton_clicked();
    void displayError(QAbstractSocket::SocketError);

private:
    Ui::Login *ui;
    bool mMoveing;
    QPoint mMovePosition;
    QTcpSocket *tcpSocket;
    void setUi();
    void init();
};

#endif // LOGIN_H
