#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include<QTimer>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  socket = new QTcpSocket(this);

  //toda vez que o botao start for clicado a funcao pushButtonPut sera chamada
  connect(ui->pushButtonPut,
         SIGNAL(clicked(bool)),
         this,
         SLOT(start()));

}

void MainWindow::tcpConnect(){

  //serve para se conectar ao servidor quando o botão connect for clicado
  socket->connectToHost(texto,1234);
  //testa se foi conectado ao servidor ou nao
  if(socket->waitForConnected(3000)){
    qDebug() << "Connected";
  }
  else{
    qDebug() << "Disconnected";
  }

}

void MainWindow::textoin()
{

     //recebe o ip do servidor
     texto = ui->textEdit->toPlainText();
     tcpConnect();
}

void MainWindow::textoout()
{
  //faz com que o servidor seja desconectado e paraliza o programa
  socket->disconnectFromHost();

  if(socket->waitForDisconnected(3000)){
    qDebug() << "Connected";
  }
  else{
    qDebug() << "Disconnected";
  }
}



void MainWindow::putData()
{
  QDateTime datetime;
  QString str;




  if(socket->state()== QAbstractSocket::ConnectedState){
      datetime = QDateTime::currentDateTime();
      //guarda em um string a data, hora e o numero aleatorio
      str = "set "+
          datetime.toString(Qt::ISODate)+
          " "+
          //cria um intervalo entre um valor maximo e minimo para se gerar um numero aleatorio
          QString::number((qrand()%(max-min))+min)+"\r\n";



      qDebug() << str;
      qDebug() << socket->write(str.toStdString().c_str()) << " bytes written";
      if(socket->waitForBytesWritten(3000)){
      qDebug() << "wrote";

      //mostra na saida a hora, data e o numero aleatório
      ui->textBrowser->setText(str);

      }
  }


}


void MainWindow::setMin(int min)
{
    //recebe um inteiro gerado no momento que o horizontalSlider é modificado
    this->min = min;
}

void MainWindow::setMax(int max)
{
    //recebe um inteiro gerado no momento que o horizontalSlider é modificado
    this->max = max;
}

void MainWindow::start()
{
     //faz com que a fucao putData seja chamada em um determiando tempo
     connect(timer, SIGNAL(timeout()), this, SLOT(putData()));
     timer->start(tempo*1000);
}

void MainWindow::stop()
{
    //para o contador de tempo
    timer->stop();
}

void MainWindow::setTempo(int tempo)
{
   //modifica o tempo toda vez que o horizontalSlider for modificado
   timer->stop();
    this-> tempo= tempo;
   timer->start(tempo*1000);

}
MainWindow::~MainWindow()
{
  //apaga todas as memorias que foram usadas no programa
  delete socket;
  delete ui;
}
