#include "plotter.h"
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QColor>
#include <cmath>
#include <QMouseEvent>


Plotter::Plotter(QWidget *parent) : QWidget(parent){

  startTimer(100);

}

void Plotter::timerEvent(QTimerEvent *e){

  repaint();
}


void Plotter::paintEvent(QPaintEvent *e){
  QPainter painter(this);
  QBrush brush;
  QPen pen;


  // habilita o anti-aliasing para que as
  // linhas sejam desenhadas sem serrilhados
  painter.setRenderHint(QPainter::Antialiasing);

  // define as props do preenchimento
  brush.setColor(QColor(255,255,0));
  brush.setStyle(Qt::SolidPattern);

  // define as props da caneta
  pen.setColor(QColor(255,0,0));
  pen.setWidth(2);

  // comunica as mudancas ao objeto painter
  painter.setBrush(brush);
  painter.setPen(pen);

  // desenha um retangulo
  painter.drawRect(0,0,width(), height());

  // atualiza as propriedades da caneta
  pen.setColor(QColor(0,0,0));
  pen.setWidth(2);
  // atualiza a caneta e desenha o eixo
  // horizontal
  painter.setPen(pen);
  painter.drawLine(0,
                   height()/2,
                   width(),
                   height()/2);


  // atualiza as propriedades da caneta
  pen.setColor(QColor(0,0,255));
  pen.setWidth(1);
  // atualiza a caneta e desenha o eixo
  // horizontal
  painter.setPen(pen);


  // primeiro ponto


}



















