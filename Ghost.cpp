#include "Ghost.h"
#include <QTimer>

Ghost::Ghost()
{
    setPixmap(QPixmap(":/Images/GhostD.png"));

    QTimer *timer_move = new QTimer;
    connect(timer_move,SIGNAL(timeout()),this,SLOT(move())); //conect method that repeats the method everytime it recives the signal
    timer_move->start(500); //Signal every 50 miliseconds
}

void Ghost::move()
{
    if (y() < 540){
        setPos(x(),y() + 30);
    }
}
