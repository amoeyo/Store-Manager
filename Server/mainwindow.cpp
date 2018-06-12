#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setText("开启服务器");

    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::openDatabase()
{
    db = QSqlDatabase::addDatabase("QODBC");   //数据库驱动类型为SQL Server
    qDebug()<<"ODBC driver?"<<db.isValid();
    QString dsn = QString::fromLocal8Bit("Store-Database");      //数据源名称
    db.setHostName("localhost");                        //选择本地主机，127.0.1.1
    db.setDatabaseName(dsn);                            //设置数据源名称
    db.setUserName("U201514650");                               //登录用户
    db.setPassword("123456");                              //密码
    if(!db.open())                                      //打开数据库
    {
        qDebug()<<db.lastError().text();
        return false;                                   //打开失败
    }
    return true;
}

void MainWindow::on_pushButton_clicked()
{
    ui->pushButton->setEnabled(false);
    if(!tcpServer->listen(QHostAddress::AnyIPv4,8000))
    {
        qDebug()<<tcpServer->errorString();
        return;
    }
    else{
        showText="开启服务器";
        ui->textBrowser->setText(showText);
        if(openDatabase()) qDebug()<<"open database successfully";
    }


}

void MainWindow::init()
{
    this->tcpServer=new QTcpServer(this);
    this->tcpSocket=new QTcpSocket(this);

    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
                     this,SLOT(displayError(QAbstractSocket::SocketError)));
}

void MainWindow::acceptConnection()
{
    tcpSocket=tcpServer->nextPendingConnection();
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(receiveData()));
}

void MainWindow::receiveData()
{
    QString receiveData=tcpSocket->readAll();
    QStringList list=receiveData.split("#");
    QString bs=list[0];
    QString username=list[1];
    QString passward=list[2];
    if(bs=="a"){//登陆
        QSqlQuery query(db); //查询     表并输出，测试能否正常操作数据库
        QString sql="SELECT * FROM EMPLOYEE WHERE ID='"+username+"'";
        query.exec(sql);
        while(query.next())
        {
            qDebug()<<query.value(0).toString();
        }
    }
}



