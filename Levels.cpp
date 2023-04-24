#include "Levels.h"
#include <QGraphicsRectItem>
#include <iostream>

char mapa[21][31] = {
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
    "X           XXXXX           X",
    "X           XXXXX           X",
    "X XXX XXXX         XXXX XXX X",
    "X XXX XXXX  XXXXX  XXXX XXX X",
    "X                           X",
    "X                           X",
    "X            XXX            X",
    "XXXXXXX              XXXXXXXX",
    "X           XXXXX           X",
    "X           XXXXX           X",
    "XXXXXXX              XXXXXXXX",
    "X            XXX            X",
    "X                           X",
    "X                           X",
    "X                           X",
    "X XXX XXXX  XXXXX  XXXX XXX X",
    "X XXX XXXX         XXXX XXX X",
    "X           XXXXX           X",
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
};


Levels::Levels(QWidget *parent)
{
    //Creation and configuration of the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,880,600);
    QFont font("Arial", 15, QFont::Helvetica);

    init_lab();

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(880,600);

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
                m_labyrinthPixmapItems[i][j] =  new QGraphicsPixmapItem();
                m_labyrinthPixmapItems[i][j]->setPixmap(QPixmap(":/Images/block (1).png"));
                m_labyrinthPixmapItems[i][j]->setPos(j*30, i*30);
                scene->addItem(m_labyrinthPixmapItems[i][j]);
            }

        }
    }
}
