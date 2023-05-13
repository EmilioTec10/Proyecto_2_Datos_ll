#ifndef LEVELS_H
#define LEVELS_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>
#include "Pac_Man.h"
#include "Ghost.h"

class Levels:public QGraphicsView{
    Q_OBJECT
public:

    Levels(QWidget * parent=0);

    static const uint LABYRINTH_WIDTH  = 21;
    static const uint LABYRINTH_HEIGHT = 31;

    char mapa[21][30] = {
        "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
        "X            XXX            X",
        "X XXXXX XXXX XXX XXXX XXXXX X",
        "X                           X",
        "X XXX XXXXX XXXXX XXXXX XXX X",
        "X XXX X               X XXX X",
        "X XXX X XXXXXXXXXXXXX X XXX X",
        "X XXX X X           X X XXX X",
        "X XXX X X XXXXXXXXX X X XXX X",
        "X XXX X X X       X X X XXX X",
        "X                           X",
        "X XXX X X XXXXXXXXX X X XXX X",
        "X XXX X X           X X XXX X",
        "X XXX X X XXXXXXXXX X X XXX X",
        "X XXX X X           X X XXX X",
        "X XXX X X XXXXXXXXX X X XXX X",
        "X                           X",
        "X XXX X XXXX XXX XXXX XXXXX X",
        "X            XXX            X",
        "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
    };

    void setPoints(int points);

    QPixmap m_labyrinthPixmap;
    QGraphicsPixmapItem* m_labyrinthPixmapItems[LABYRINTH_WIDTH][LABYRINTH_HEIGHT];
    QPixmap m_labyrinthPixmaps[32];

    QTimer *timer_points = new QTimer();
    QTimer *timer_level;
    QTimer *col;
    QTimer *col_ghost;
    QTimer *timer_set;

    Pac_Man *pac_man;
    Ghost *ghost;

    QGraphicsTextItem *points_label;
    QGraphicsTextItem *lifes_label;

    QGraphicsScene * scene;

public slots:
    void check_win();
    void check_collision();
    void check_ghost_collision();
    void check_points();
    void set_pac_position();
private:
    int pillows = 0;
    int points = 0;
    int level = 2;
    void init_level();
    void changemap();
};

#endif // LEVELS_H
