#include "Levels.h"
#include <QGraphicsRectItem>
#include <iostream>

char mapa[21][31] = {
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
    "X            XXX            X",
    "X XXXXX XXXX XXX XXXX XXXXX X",
    "X                           X",
    "X XXX XXXXX XXXXX XXXXX XXX X",
    "X                           X",
    "X                           X",
    "XXXXXXX     XXXXXX   XXXXXXXX",
    "XXXXXXX          X   XXXXXXXX",
    "X           XXXXXX          X",
    "X           X        XXX X  X",
    "X           XXXXX           X",
    "X            XXX            X",
    "X                           X",
    "X           XXXXX           X",
    "X             X             X",
    "X                           X",
    "X XXXXX XXXX XXX XXXX XXXXX X",
    "X            XXX            X",
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
};


Levels::Levels(QWidget *parent)
{
    //Creation and configuration of the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,880,600);
    QFont font("Arial", 15, QFont::Helvetica);

    init_lab();

    pac_man = new Pac_Man();

    scene->addItem(pac_man);

    pac_man->setFlag(QGraphicsItem::ItemIsFocusable);
    pac_man->setFocus();
    pac_man->setPos(880/2,600/2);

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
