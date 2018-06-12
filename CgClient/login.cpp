#include "login.h"
#include "ui_login.h"

#define ip "10.14.108.44"
#define port 8000

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    setUi();
    init();


}

Login::~Login()
{
    delete ui;
}

void Login::setUi()
{
    setWindowFlags(Qt::FramelessWindowHint);
    this->setObjectName("dialog");
    this->setStyleSheet("QDialog#dialog{border-image:url(Login.png)}");
    ui->exitButton->setStyleSheet("border-image:url(exitbutton.png)");
    ui->minButton->setStyleSheet("border-image:url(minbutton.png)");
    ui->lineEdit->setStyleSheet("border-image:url(lineedit.png)");
    ui->lineEdit_pass->setStyleSheet("border-image:url(lineedit.png)");
    ui->icon1->setStyleSheet("border-image:url(loginicon.png)");
    ui->icon2->setStyleSheet("border-image:url(passicon.png)");
    ui->lineEdit_pass->setEchoMode(QLineEdit::Password);//输入的时候就显示圆点
    ui->pushButton->setStyleSheet("border-image:url(loginbutton.png)");
}

void Login::init()
{
    tcpSocket=new QTcpSocket(this);
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(displayError(QAbstractSocket::SocketError)));   //发生错误时执行displayError函数
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessages()));
}

void Login::readMessages()
{
    QString recieveData=tcpSocket->readAll();
    QStringList list=recieveData.split("#");
    QString bs=list[0];
    if(bs=="true"){
        this->close();


    }
    else if(bs=="false1"){
        QMessageBox::information(this,"警告","用户不存在",QMessageBox::Ok);
        ui->lineEdit->clear();
        ui->lineEdit_pass->clear();
    }
    else if(bs=="false2"){
        QMessageBox::information(this,"警告","密码错误",QMessageBox::Ok);
        ui->lineEdit_pass->clear();
    }
    else{
        QMessageBox::information(this,"警告","未知错误",QMessageBox::Ok);
        ui->lineEdit->clear();
        ui->lineEdit_pass->clear();
    }
    return;
}


void Login::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<tcpSocket->errorString();   //输出出错信息
}


void Login::on_exitButton_clicked()
{
    //系统自定义的窗口关闭函数
    close();
}

void Login::on_minButton_clicked()
{
    //系统自定义的最小化窗口函数
    showMinimized();
    //最大化 showMaximized()
}


//自己实现的窗口拖动操作
void Login::mousePressEvent(QMouseEvent *event)
{
    mMoveing = true;
    //记录下鼠标相对于窗口的位置
    //event->globalPos()鼠标按下时，鼠标相对于整个屏幕位置
    //pos() this->pos()鼠标按下时，窗口相对于整个屏幕位置
    mMovePosition = event->globalPos() - pos();
    return QDialog::mousePressEvent(event);
}

void Login::mouseMoveEvent(QMouseEvent *event)
{
    //(event->buttons() && Qt::LeftButton)按下是左键
    //鼠标移动事件需要移动窗口，窗口移动到哪里呢？就是要获取鼠标移动中，窗口在整个屏幕的坐标，然后move到这个坐标，怎么获取坐标？
    //通过事件event->globalPos()知道鼠标坐标，鼠标坐标减去鼠标相对于窗口位置，就是窗口在整个屏幕的坐标
    if (mMoveing && (event->buttons() && Qt::LeftButton)
        && (event->globalPos()-mMovePosition).manhattanLength() > QApplication::startDragDistance())
    {
        move(event->globalPos()-mMovePosition);
        mMovePosition = event->globalPos() - pos();
    }
    return QDialog::mouseMoveEvent(event);
}

void Login::mouseReleaseEvent(QMouseEvent *event)
{
    mMoveing = false;
}

void Login::on_pushButton_clicked()
{
    tcpSocket->abort();   //取消已有的连接
    tcpSocket->connectToHost(ip,port);
    QString username=ui->lineEdit->text();
    QString passward=ui->lineEdit_pass->text();
    if(username==""){
        QMessageBox::information(this,"警告","请输入账号后再登陆",QMessageBox::Ok);
        return;
    }
    if(passward==""){
        QMessageBox::information(this,"警告","请输入密码",QMessageBox::Ok);
        return;
    }
    QString sendData="a#"+username+"#"+passward;
    if(tcpSocket->write(sendData.toLatin1())==-1) qDebug()<<"unconnected";
}
