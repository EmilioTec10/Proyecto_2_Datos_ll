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

    QPixmap m_labyrinthPixmap;
    QGraphicsPixmapItem* m_labyrinthPixmapItems[LABYRINTH_WIDTH][LABYRINTH_HEIGHT];
    QPixmap m_labyrinthPixmaps[32];

    Pac_Man *pac_man;

    QGraphicsScene * scene;
private:
    void init_lab();
};

#endif // LEVELS_H
