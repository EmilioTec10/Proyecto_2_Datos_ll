#include "Pac_Man.h"
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>

int cycle = 0;

Pac_Man::Pac_Man()
{
    setPixmap(QPixmap(":/Images/pac_man_0R.png"));

    QTimer *timer_move = new QTimer;
    connect(timer_move,SIGNAL(timeout()),this,SLOT(move())); //conect method that repeats the method everytime it recives the signal
    timer_move->start(50); //Signal every 50 miliseconds

    connect(timer_animation,SIGNAL(timeout()),this,SLOT(animation_R())); //conect method that repeats the method everytime it recives the signal
    timer_animation->start(150); //Signal every 50 miliseconds
}

void Pac_Man::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W){
        direcction = 'U';
        cycle = 0;
        connect(timer_animation,SIGNAL(timeout()),this,SLOT(animation_U())); //conect method that repeats the method everytime it recives the signal
    }
    if (event->key() == Qt::Key_S){
        direcction = 'D';
        cycle = 0;
        connect(timer_animation,SIGNAL(timeout()),this,SLOT(animation_D())); //conect method that repeats the method everytime it recives the signal
    }
    if (event->key() == Qt::Key_A){
        direcction = 'L';
        cycle = 0;
        connect(timer_animation,SIGNAL(timeout()),this,SLOT(animation_L())); //conect method that repeats the method everytime it recives the signal
    }
    if (event->key() == Qt::Key_D){
        direcction = 'R';
        cycle = 0;
        connect(timer_animation,SIGNAL(timeout()),this,SLOT(animation_R())); //conect method that repeats the method everytime it recives the signal
    }
}

void Pac_Man::move()
{
    if (direcction == 'R'){
        if (x() < 810){
            setPos(x() + speed,y());
        }
    }
    else if (direcction == 'L'){
        if (x() > 30){
            setPos(x() - speed,y());
        }
    }
    else if (direcction == 'U'){
        if (y() > 30){
            setPos(x(),y() - speed);
        }
    }
    else if (direcction == 'D'){
        if (y() < 540){
            setPos(x(),y() + speed);
        }
    }
}

void Pac_Man::animation_R()
{
    if (cycle == 0){
        setPixmap(QPixmap(":/Images/pac_man_0R.png"));
        cycle++;
    }

    else if (cycle == 1){
        setPixmap(QPixmap(":/Images/pac_man_1R.png"));
        cycle++;
    }

    else if (cycle == 2){
        setPixmap(QPixmap(":/Images/pac_man_2.png"));
        cycle = 0;
    }
}

void Pac_Man::animation_L()
{
    if (cycle == 0){
        setPixmap(QPixmap(":/Images/pac_man_0L.png"));
        cycle++;
    }

    else if (cycle == 1){
        setPixmap(QPixmap(":/Images/pac_man_1L.png"));
        cycle++;
    }

    else if (cycle == 2){
        setPixmap(QPixmap(":/Images/pac_man_2.png"));
        cycle = 0;
    }
}

void Pac_Man::animation_U()
{
    if (cycle == 0){
        setPixmap(QPixmap(":/Images/pac_man_0U.png"));
        cycle++;
    }

    else if (cycle == 1){
        setPixmap(QPixmap(":/Images/pac_man_1U.png"));
        cycle++;
    }

    else if (cycle == 2){
        setPixmap(QPixmap(":/Images/pac_man_2.png"));
        cycle = 0;
    }
}

void Pac_Man::animation_D()
{
    if (cycle == 0){
        setPixmap(QPixmap(":/Images/pac_man_0D.png"));
        cycle++;
    }

    else if (cycle == 1){
        setPixmap(QPixmap(":/Images/pac_man_1D.png"));
        cycle++;
    }

    else if (cycle == 2){
        setPixmap(QPixmap(":/Images/pac_man_2.png"));
        cycle = 0;
    }
}

