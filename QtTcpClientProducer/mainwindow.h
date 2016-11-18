#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  
  void tcpConnect();
public slots:
  void textoin();
  void textoout();
  void putData();
  void setMin(int min);
  void setMax(int max);
  void start();
  void stop();
  void setTempo(int tempo);
private:
  int min;
  int max;
  int tempo;
  QString texto;
  QTimer *timer = new QTimer(this);
  Ui::MainWindow *ui;
  QTcpSocket *socket;

};

#endif // MAINWINDOW_H
