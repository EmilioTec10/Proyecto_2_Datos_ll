#ifndef LEVELS_H
#define LEVELS_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>
#include "Pac_Man.h"

class Levels:public QGraphicsView{

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

    QPixmap m_labyrinthPixmap;
    QGraphicsPixmapItem* m_labyrinthPixmapItems[LABYRINTH_WIDTH][LABYRINTH_HEIGHT];
    QPixmap m_labyrinthPixmaps[32];

    Pac_Man *pac_man;

    QGraphicsTextItem *points_label;

    QGraphicsScene * scene;
private:
    void init_lab();
    int points = 0;
};

#endif // LEVELS_H
