#include "Levels.h"
#include "Blocks.h"
#include "Ghost.h"
#include "Dots.h"
#include <QTimer>
#include <QGraphicsRectItem>
#include <iostream>

Levels::Levels(QWidget *parent)
{
    //Creation and configuration of the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,870,620);
    scene->setBackgroundBrush(QBrush(QImage(":/Images/back.png")));
    QFont font("Arial", 15, QFont::Helvetica);

    init_lab();

    pac_man = new Pac_Man();
    Ghost *ghost = new Ghost();

    QTimer *col = new QTimer();
    connect(col,SIGNAL(timeout()),pac_man,SLOT(check_collision()));
    col->start(100);

    points_label = new QGraphicsTextItem("Points: " + QString::number(points));
    points_label->setFont(font);
    points_label->setDefaultTextColor(Qt::red);

    scene->addItem(pac_man);
    scene->addItem(ghost);
    scene->addItem(points_label);

    points_label->setPos(720,590);
    ghost->setPos(810,30);

    pac_man->set_points_label(points_label);
    //pac_man->set_mapa(mapa);
    pac_man->setFlag(QGraphicsItem::ItemIsFocusable);
    pac_man->setFocus();
    pac_man->setPos(420,600/2);

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(870,620);

}

void Levels::init_lab()
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
                dot->setPos(j*30, i*30);
                scene->addItem(dot);
            }

        }
    }
}
