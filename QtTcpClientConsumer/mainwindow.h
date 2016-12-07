#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <QListWidget>

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
  void con();
  void lista(QListWidgetItem* item);
  void discon();
  void getData();
  void up();
private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;
  QString texto;
  QString ip;
  QListWidgetItem* item;
};

#endif // MAINWINDOW_H
