#include "tcpserver.h"

TcpServer::TcpServer(QWidget *parent,Qt::WindowFlags f)
    : QDialog(parent,f)
{
    setWindowTitle(tr("TCP Server"));

    ContentListWidget = new QListWidget;

    PortLabel = new QLabel(tr("接听端口："));
    PortLineEdit = new QLineEdit;

    CreateBtn = new QPushButton(tr("创建聊天室"));

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(ContentListWidget,0,0,1,2);
    mainLayout->addWidget(PortLabel,1,0);
    mainLayout->addWidget(PortLineEdit,1,1);
    mainLayout->addWidget(CreateBtn,2,0,1,2);

    port=4444;
    PortLineEdit->setText(QString::number(port));

    connect(CreateBtn,SIGNAL(clicked()),this,SLOT(slotCreateServer()));
}

TcpServer::~TcpServer()
{
    
}
//创建聊天室
void TcpServer::slotCreateServer()
{
    //启动服务器
    server = new Server(this,port);
    //检测更新服务器信号
    connect(server,SIGNAL(updateServer(QString,int)),this,SLOT(updateServer(QString,int)));

    CreateBtn->setEnabled(false);
}
//更新服务器
void TcpServer::updateServer(QString msg,int length)
{
    ContentListWidget->addItem(msg.left(length));
//    PortLineEdit->setText(msg);
}
