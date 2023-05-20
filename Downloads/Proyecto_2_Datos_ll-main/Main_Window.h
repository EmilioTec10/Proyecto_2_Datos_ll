#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>

class Main_Window: public QGraphicsView{
public:

  Main_Window(QWidget * parent=0);

  //Game dificulties
  void game();

  QGraphicsScene * scene;
private:
  int width = 800;
  int height = 600;

};

#endif // MAIN_WINDOW_H
