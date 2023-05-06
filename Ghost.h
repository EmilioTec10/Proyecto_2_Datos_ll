#ifndef GHOST_H
#define GHOST_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Ghost:public QObject , public  QGraphicsPixmapItem{
    Q_OBJECT
public:
    Ghost();
    void super_pillow();
    bool superpillow = false;
    char direcction = 'D';

    QTimer *timer_super;

public slots:
    void move();
    void quit_super_pillow();
private:
    int posX_pacman = 10;
    int posY_pacamn = 14;
};

#endif // GHOST_H
