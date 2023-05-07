#include "Pac_Man.h"
#include "qgraphicsscene.h"
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include <iostream>

int cycle = 0;

Pac_Man::Pac_Man()
{
    setPixmap(QPixmap(":/Images/pac_man_0R.png"));

    timer_move = new QTimer;
    connect(timer_move,SIGNAL(timeout()),this,SLOT(move())); //conect method that repeats the method everytime it recives the signal
    timer_move->start(80); //Signal every 50 miliseconds


    connect(timer_animation_R,SIGNAL(timeout()),this,SLOT(animation_R())); //conect method that repeats the method everytime it recives the signal
    connect(timer_animation_U,SIGNAL(timeout()),this,SLOT(animation_U())); //conect method that repeats the method everytime it recives the signal
    connect(timer_animation_D,SIGNAL(timeout()),this,SLOT(animation_D())); //conect method that repeats the method everytime it recives the signal
    connect(timer_animation_L,SIGNAL(timeout()),this,SLOT(animation_L())); //conect method that repeats the method everytime it recives the signal
    timer_animation_R->start(150); //Signal every 50 miliseconds
}



void Pac_Man::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W){
        direcction = 'U';
        cycle = 0;
        timer_animation_D->stop();
        timer_animation_L->stop();
        timer_animation_R->stop();
        timer_animation_U->start(150);
    }
    if (event->key() == Qt::Key_S){
        direcction = 'D';
        cycle = 0;
        timer_animation_L->stop();
        timer_animation_R->stop();
        timer_animation_U->stop();
        timer_animation_D->start(150);
    }
    if (event->key() == Qt::Key_A){
        direcction = 'L';
        cycle = 0;
        timer_animation_L->start(150);
        timer_animation_R->stop();
        timer_animation_U->stop();
        timer_animation_D->stop();
    }
    if (event->key() == Qt::Key_D){
        direcction = 'R';
        cycle = 0;
        timer_animation_L->stop();
        timer_animation_R->start(150);
        timer_animation_U->stop();
        timer_animation_D->stop();
    }
}

void Pac_Man::set_points_label(QGraphicsTextItem *points_label)
{
    this->points_label = points_label;
}

void Pac_Man::set_lifes_label(QGraphicsTextItem *lifes_label)
{
    this->lifes_label = lifes_label;
}

void Pac_Man::set_mapa(char mapa[21][30])
{
    for (int i = 0;i < 21;i++){
        for(int j = 0;j < 30;j++){
            this->mapa[i][j] = mapa[i][j];
        }
    }
}

void Pac_Man::revive()
{
    Pac_Man *pac_man = new Pac_Man();
    pac_man->setPos(420,600/2);
    com_x = 0.0;
    com_y = 0.0;
    position_x = 10;
    position_y = 14;
    scene()->addItem(pac_man);
    die_timer->stop();
}

void Pac_Man::move()
{
    if (direcction == 'R'){
        if (x() < 810 && mapa[position_x][position_y + 1] != 'X'){
            setPos(x() + speed,y());
            com_x += 0.17;
            if (com_x >= 1.0){
                position_y++;
                com_x = 0;
            }
        }
    }
    else if (direcction == 'L'){
        if (x() > 30 && mapa[position_x][position_y - 1] != 'X'){
            setPos(x() - speed,y());
            com_x -= 0.17;
            if (com_x <= -1.0){
                position_y--;
                qDebug() << position_y;
                com_x = 0;
            }
        }
    }
    else if (direcction == 'U'){
        if (y() > 30 && mapa[position_x - 1][position_y] != 'X'){
            setPos(x(),y() - speed);
            com_y += 0.17;
            if (com_y >= 1.0){
                position_x--;
                com_y = 0;
            }
        }
    }
    else if (direcction == 'D'){
        if (y() < 540 && mapa[position_x + 1][position_y] != 'X'){
            setPos(x(),y() + speed);
            com_y -= 0.17;
            if (com_y <= -1.0){
                position_x++;
                com_y = 0;
            }
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
