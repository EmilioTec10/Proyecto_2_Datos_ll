#include "Level2.h"
#include "Blocks.h"
#include "Ghost.h"
#include "Dots.h"
#include "SuperDot.h"
#include <QTimer>
#include <QGraphicsRectItem>
#include <iostream>

Level2::Level2(QWidget *parent)
{
    //Creation and configuration of the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,870,620);
    scene->setBackgroundBrush(QBrush(QImage(":/Images/back.png")));
    QFont font("Arial", 15, QFont::Helvetica);

    init_level();

    ghost_1 = new Ghost();
    ghost_2 = new Ghost();
    pac_man = new Pac_Man();

    col = new QTimer();
    connect(col,SIGNAL(timeout()),this,SLOT(check_collision()));
    col->start(100);

    /*
    timer_level = new QTimer();
    connect(timer_level,SIGNAL(timeout()),this,SLOT(check_win()));
    timer_level->start(800);
    */

    connect(timer_points, SIGNAL(timeout()),this, SLOT(check_points()));
    timer_points->start(500);

    points_label = new QGraphicsTextItem("Points: " + QString::number(0));
    points_label->setFont(font);
    points_label->setDefaultTextColor(Qt::red);

    lifes_label = new QGraphicsTextItem("Lifes: " + QString::number(3));
    lifes_label->setFont(font);
    lifes_label->setDefaultTextColor(Qt::red);

    scene->addItem(pac_man);
    scene->addItem(ghost_1);
    scene->addItem(ghost_2);
    scene->addItem(points_label);
    scene->addItem(lifes_label);

    points_label->setPos(720,590);
    lifes_label->setPos(600,590);
    ghost_1->setPos(810,30);
    ghost_2->setPos(30,30);

    pac_man->set_points_label(points_label);
    pac_man->set_lifes_label(lifes_label);
    pac_man->set_mapa(mapa);
    pac_man->setFlag(QGraphicsItem::ItemIsFocusable);
    pac_man->setFocus();
    pac_man->setPos(420,600/2);

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(870,620);

}

void Level2::setPoints(int points)
{
    this->points = points;
}

void Level2::check_win()
{
    if (pillows == 0){
        if (level == 2){
            delete pac_man;
            delete ghost_1;
            delete ghost_2;
            delete points_label;
            delete lifes_label;
            delete timer_points;
            delete timer_level;
            delete col;
            scene->clear();
           for (int i = 0;i < 21;i++){
               for (int j = 0;j < 30;i++){
                   mapa[i][j] = ' ';
               }
           }
           init_level();
           level++;

        }
        else if (level == 3){

        }
        else if (level == 4){

        }
    }
}

void Level2::check_collision()
{
    QList<QGraphicsItem *> colliding_items = pac_man->collidingItems(); //List of the colliding items
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Dot)){
            scene->removeItem(colliding_items[i]);
            delete colliding_items[i];
            points += 10;
            points_label->setPlainText("Points: " + QString::number(points));
            pillows--;
            return;
        }
        else if (typeid(*(colliding_items[i])) == typeid(SuperDot)){
            scene->removeItem(colliding_items[i]);
            delete colliding_items[i];
            pac_man->super_dot = true;
            return;
        }
        else if (typeid(*(colliding_items[i])) == typeid(Ghost)){
            pac_man->lifes--;
            pac_man->position_x = 10;
            pac_man->position_y = 14;
            pac_man->setPos(420,600/2);
            lifes_label->setPlainText("Lifes: " + QString::number(pac_man->lifes));
            return;
        }
    }
}

void Level2::check_points()
{
    if (points % 200 == 0){

        SuperDot *super_dot = new SuperDot();
        scene->addItem(super_dot);
        super_dot->setPos(420,600/2);
    }
}

void Level2::init_level()
{

    int index = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            m_labyrinthPixmaps[index] = m_labyrinthPixmap.copy(i * 30, j * 30, 30, 30);
            index++;
        }
    }
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < int(31); j++)
        {
            if (mapa[i][j] == 'X'){
                Block *block = new Block();
                block->setPos(j*30, i*30);
                scene->addItem(block);
            }
            else if (mapa[i][j] == ' '){
                Dot *dot = new Dot();
                dot->setPos((j*30)+10, (i*30)+10);
                scene->addItem(dot);
                pillows++;
            }

        }
    }
}
