#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QListWidget>
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    tcpConnect();
    //botão getdata(não modificado)
    connect(ui->pushButtonGet,
            SIGNAL(clicked(bool)),
            this,
            SLOT(getData()));
    //função para quando um item da lista foi clicado
    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(lista(QListWidgetItem*)));

}

//conecta-se ao servidor
void MainWindow::tcpConnect(){
    socket->connectToHost(texto,1234);
    if(socket->waitForConnected(3000)){
        qDebug() << "Connected";
    }
    else{
        qDebug() << "Disconnected";
    }
}
//esta funcao eh chamada quando o botao para se conectar eh clicado
void MainWindow::con()
{
    texto = ui->textEdit->toPlainText();
    //chama a funcao para se conectar
    tcpConnect();

}

void MainWindow::lista(QListWidgetItem *item)
{
    //seleciona o item clicado
    int i;
    for(i=0;i < ui->listWidget->count();i++){
        if(ui->listWidget->item(i)==item){
            ip = ui->listWidget->item(i)->text();
        }
    }


}
//função que desconecta o servidor
void MainWindow::discon()
{
    socket->disconnectFromHost();

    if(socket->waitForDisconnected(3000)){
        qDebug() << "Connected";
    }
    else{
        qDebug() << "Disconnected";
    }
}

//não modificado
void MainWindow::getData(){
    QString str;
    QByteArray array;
    QStringList list;
    QDateTime datetime;
    qDebug() << "to get data...";
    if(socket->state() == QAbstractSocket::ConnectedState){
        if(socket->isOpen()){
            qDebug() << "reading...";
            socket->write("get 127.0.0.1\r\n");
            socket->waitForBytesWritten();
            socket->waitForReadyRead();
            qDebug() << socket->bytesAvailable();
            while(socket->bytesAvailable()){
                str = socket->readLine().replace("\n","").replace("\r","");
                list = str.split(" ");
                if(list.size() == 2){
                    datetime.fromString(list.at(0),Qt::ISODate);
                    str = list.at(1);
                    qDebug() << datetime << ": " << str;
                }
            }
        }
    }
}
//mostra na lista os srvidores ao clicar no botao update
void MainWindow::up()
{
    QString str;
    QByteArray array;
    QStringList list;
    QDateTime datetime;
    if(socket->state() == QAbstractSocket::ConnectedState){
        if(socket->isOpen()){
            socket->write("list\r\n");
            socket->waitForBytesWritten();
            socket->waitForReadyRead();
            qDebug() << socket->bytesAvailable();
            while(socket->bytesAvailable()){
                str = socket->readLine().replace("\n","").replace("\r","");
                list = str.split(" ");
                if(list.size() == 1){
                    str = list.at(0);
                    qDebug() << str;
                }
            }
        }
    }
    ui->listWidget->addItem(str);
}
MainWindow::~MainWindow()
{
    delete socket;
    delete ui;
}
