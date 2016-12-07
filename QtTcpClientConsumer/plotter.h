#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>

class Plotter : public QWidget{
  Q_OBJECT
private:

public:
  explicit Plotter(QWidget *parent = 0);

  void paintEvent(QPaintEvent *e);

signals:


public slots:

  void timerEvent(QTimerEvent *e);

};

#endif // PLOTTER_H
