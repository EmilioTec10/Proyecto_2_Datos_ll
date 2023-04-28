#include "Pac_Man.h"
#include "Dots.h"
#include "SuperDot.h"
#include "Ghost.h"
#include "qgraphicsscene.h"
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>

int cycle = 0;

Pac_Man::Pac_Man()
{
    setPixmap(QPixmap(":/Images/pac_man_0R.png"));

    QTimer *timer_move = new QTimer;
    connect(timer_move,SIGNAL(timeout()),this,SLOT(move())); //conect method that repeats the method everytime it recives the signal
    timer_move->start(500); //Signal every 50 miliseconds


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

void Pac_Man::set_points_label(QGraphicsTextItem *points_label)
{
    this->points_label = points_label;
}

void Pac_Man::set_mapa(char mapa[21][30])
{
    for (int i = 0;i < 21;i++){
        for(int j = 0;j < 30;j++){
            this->mapa[i][j] = mapa[i][j];
            qDebug() << mapa[i][j];
        }
    }
}


void Pac_Man::check_collision()
{
    QList<QGraphicsItem *> colliding_items = collidingItems(); //List of the colliding items
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Dot)){
            scene()->removeItem(colliding_items[i]);
            delete colliding_items[i];
            points += 10;
            points_label->setPlainText("Points: " + QString::number(points));
            return;
        }
        else if (typeid(*(colliding_items[i])) == typeid(SuperDot)){
            scene()->removeItem(colliding_items[i]);
            delete colliding_items[i];
            super_dot = true;
            return;
        }
        else if (typeid(*(colliding_items[i])) == typeid(Ghost)){
            scene()->removeItem(this);
            lifes--;
            return;
        }
    }
}

void Pac_Man::check_points()
{
    if (points % 200 == 0){

        SuperDot *super_dot = new SuperDot();
        scene()->addItem(super_dot);
        super_dot->setPos(420,600/2);
    }
}


void Pac_Man::move()
{
    if (direcction == 'R'){
        if (x() < 810 && mapa[position_x][position_y + 1] != 'X'){
            setPos(x() + speed,y());
            position_y++;
        }
    }
    else if (direcction == 'L'){
        if (x() > 30 && mapa[position_x][position_y - 1] != 'X'){
            setPos(x() - speed,y());
            position_y--;
        }
    }
    else if (direcction == 'U'){
        if (y() > 30 && mapa[position_x - 1][position_y] != 'X'){
            setPos(x(),y() - speed);
            position_x--;
        }
    }
    else if (direcction == 'D'){
        if (y() < 540 && mapa[position_x + 1][position_y] != 'X'){
            setPos(x(),y() + speed);
            position_x++;
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

