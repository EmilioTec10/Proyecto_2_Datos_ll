#include "Ghost.h"
#include <QTimer>

Ghost::Ghost()
{
    setPixmap(QPixmap(":/Images/GhostD.png"));

    QTimer *timer_move = new QTimer;
    connect(timer_move,SIGNAL(timeout()),this,SLOT(move())); //conect method that repeats the method everytime it recives the signal
    timer_move->start(500); //Signal every 50 miliseconds
}

void Ghost::super_pillow()
{
    superpillow = true;
    setPixmap(QPixmap(":/Images/GhostT.png"));
    timer_super = new QTimer;
    connect(timer_super,SIGNAL(timeout()),this,SLOT(quit_super_pillow()));
    timer_super->start(3000);
}

void Ghost::move()
{
    if (y() < 540){
        setPos(x(),y() + 30);
    }
}

void Ghost::quit_super_pillow()
{
    setPixmap(QPixmap(":/Images/GhostD.png"));
    superpillow = false;
    timer_super->stop();
}
