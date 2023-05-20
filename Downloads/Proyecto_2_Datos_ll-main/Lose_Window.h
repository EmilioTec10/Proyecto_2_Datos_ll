#ifndef LOSE_WINDOW_H
#define LOSE_WINDOW_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>


class Game_Over: public QGraphicsView{
public:

  Game_Over(QWidget * parent=0);

  void main_menu();

  QGraphicsScene * scene;
};

#endif // LOSE_WINDOW_H
