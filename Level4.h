#ifndef LEVEL4_H
#define LEVEL4_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>
#include "Pac_Man.h"
#include "Ghost.h"
#include "Ghost2.h"
#include "Ghost3.h"
#include "Ghost4.h"

class Level4:public QGraphicsView{
    Q_OBJECT
public:

    Level4(QWidget * parent=0);

    static const uint LABYRINTH_WIDTH  = 21;
    static const uint LABYRINTH_HEIGHT = 31;

    char mapa[21][30] = {
           "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
           "X                           X",
           "X X X X X X X X X X X X X X X",
           "X                           X",
           "X X X X X X X X X X X X X X X",
           "X                           X",
           "X X X X X X X X X X X X X X X",
           "X                           X",
           "X X X X X X X X X X X X X X X",
           "X X X X X X X X X X X X X X X",
           "X X X X X X X   X X X X X X X",
           "X X X X X X X X X X X X X X X",
           "X                           X",
           "X X X X X X X X X X X X X X X",
           "X                           X",
           "X X X X X X X X X X X X X X X",
           "X                           X",
           "X X X X X X X X X X X X X X X",
           "X                           X",
           "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
       };

    void setPoints(int points);
    void ReviveGhosts();

    QPixmap m_labyrinthPixmap;
    QGraphicsPixmapItem* m_labyrinthPixmapItems[LABYRINTH_WIDTH][LABYRINTH_HEIGHT];
    QPixmap m_labyrinthPixmaps[32];

    QTimer *timer_points = new QTimer();
    QTimer *timer_lose;
    QTimer *timer_level;
    QTimer *col;
    QTimer *col_ghost1;
    QTimer *col_ghost2;
    QTimer *col_ghost3;
    QTimer *col_ghost4;
    QTimer *timer_set;

    Pac_Man *pac_man;
    Ghost *ghost1;
    Ghost2 *ghost2;
    Ghost3 *ghost3;
    Ghost4 *ghost4;

    QGraphicsTextItem *points_label;
    QGraphicsTextItem *lifes_label;

    QGraphicsScene * scene;

public slots:
    void check_win();
    void check_lose();
    void check_collision();
    void check_ghost1_collision();
    void check_ghost2_collision();
    void check_ghost3_collision();
    void check_ghost4_collision();
    void check_points();
    void set_pac_position();
private:
    int pillows = 0;
    int points = 0;
    int level = 2;
    void init_level();
    void changemap();
};


#endif // LEVEL4_H
