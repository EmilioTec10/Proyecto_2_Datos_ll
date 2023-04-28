#ifndef GHOST_H
#define GHOST_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Ghost:public QGraphicsPixmapItem,public QObject{
public:
    Ghost();
public slots:
    void move();
};

#endif // GHOST_H
