#ifndef LEVEL2_H
#define LEVEL2_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>
#include "Pac_Man.h"
#include "Ghost.h"

class Level2:public QGraphicsView{
    Q_OBJECT
public:

    Level2(QWidget * parent=0);

    static const uint LABYRINTH_WIDTH  = 21;
    static const uint LABYRINTH_HEIGHT = 31;

    char mapa[21][30] = {
        "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
        "X            XXX            X",
        "X X X X XXXX XXX XXXX X X X X",
        "X X X X XXXX XXX XXXX X X X X",
        "X X                       X X",
        "X X X XXXXX  XXX   XXXX X X X",
        "X X X X XXXX XXX XXXX X X X X",
        "X X X X X           X X X X X",
        "X X X X X XXXX XXXX X X X X X",
        "X X X X X X       X X X X X X",
        "X                           X",
        "X X X X X XXXX XXXX X X X X X",
        "X X X                   X X X",
        "X X X X X XXXXXXXXX X X X X X",
        "X X X X X           X X X X X",
        "X X X X X XXXXXXXXX X X X X X",
        "X                           X",
        "X XXXXXXXXXX XXX XXXXXXXXXX X",
        "X                           X",
        "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
    };

    void setPoints(int points);

    QPixmap m_labyrinthPixmap;
    QGraphicsPixmapItem* m_labyrinthPixmapItems[LABYRINTH_WIDTH][LABYRINTH_HEIGHT];
    QPixmap m_labyrinthPixmaps[32];

    QTimer *timer_points = new QTimer();
    QTimer *timer_level;
    QTimer *col;

    Pac_Man *pac_man;
    Ghost *ghost_1;
    Ghost *ghost_2;

    QGraphicsTextItem *points_label;
    QGraphicsTextItem *lifes_label;

    QGraphicsScene * scene;

public slots:
    void check_win();
    void check_collision();
    void check_points();
private:
    int pillows = 0;
    int level = 2;
    int points = 0;
    void init_level();
    void changemap();
};

#endif // LEVEL2_H
