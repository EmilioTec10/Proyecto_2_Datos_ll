#include "Levels.h"
#include "Level2.h"
#include "Blocks.h"
#include "Ghost.h"
#include "Dots.h"
#include "SuperDot.h"
#include "Lose_Window.h"
#include <QTimer>
#include <QGraphicsRectItem>
#include <iostream>

/**
 * @brief Levels::Levels Construcotr que inicia la pantalla del juego
 * @param parent Hace posible que se incie
 */
Levels::Levels(QWidget *parent)
{
    //Creation and configuration of the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,870,620);
    scene->setBackgroundBrush(QBrush(QImage(":/Images/back.png")));
    QFont font("Arial", 15, QFont::Helvetica);

    init_level();

    ghost = new Ghost();
    pac_man = new Pac_Man();

    col = new QTimer();
    connect(col,SIGNAL(timeout()),this,SLOT(check_collision()));
    col->start(100);

    timer_lose = new QTimer();
    connect(timer_lose,SIGNAL(timeout()),this,SLOT(check_lose()));
    timer_lose->start(100);

    col_ghost = new QTimer();
    connect(col_ghost,SIGNAL(timeout()),this,SLOT(check_ghost_collision()));
    col_ghost->start(100);

    timer_level = new QTimer();
    connect(timer_level,SIGNAL(timeout()),this,SLOT(check_win()));
    timer_level->start(800);

    timer_set = new QTimer();
    connect(timer_set,SIGNAL(timeout()),this, SLOT(set_pac_position()));
    timer_set->start(500);

    connect(timer_points, SIGNAL(timeout()),this, SLOT(check_points()));
    timer_points->start(300);

    points_label = new QGraphicsTextItem("Points: " + QString::number(0));
    points_label->setFont(font);
    points_label->setDefaultTextColor(Qt::red);

    lifes_label = new QGraphicsTextItem("Lifes: " + QString::number(3));
    lifes_label->setFont(font);
    lifes_label->setDefaultTextColor(Qt::red);

    level_label = new QGraphicsTextItem("Level: " + QString::number(level));
    level_label->setFont(font);
    level_label->setDefaultTextColor(Qt::red);

    scene->addItem(pac_man);
    scene->addItem(ghost);
    scene->addItem(points_label);
    scene->addItem(lifes_label);
    scene->addItem(level_label);

    points_label->setPos(720,593);
    lifes_label->setPos(600,593);
    level_label->setPos(480,593);
    ghost->setScene(scene);
    ghost->setPos(810,30);
    ghost->set_mapa(mapa);

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

/**
 * @brief Levels::check_win Verifica si el jugador consiguio todas las pastillas para pasar de nivel
 */
void Levels::check_win()
{
    if (pillows == 0){
        timer_level->stop();
        timer_points->stop();
        this->close();
        Level2 *level2 = new Level2();
        level2->setPoints(points);
        level2->show();
    }
}

/**
 * @brief Levels::check_lose Verifica la cantidad de vidas del jugador para ver si ya perdio
 */
void Levels::check_lose()
{
    if (pac_man->lifes == 0){
        timer_level->stop();
        timer_points->stop();
        timer_lose->stop();
        this->close();
        Game_Over *window = new Game_Over();
        window->show();
    }
}

/**
 * @brief Levels::check_collision Verifica la colision de el pacman con los objetos
 */
void Levels::check_collision()
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
            points += 50;
            ghost->super_pillow();
            return;
        }

        else if (typeid(*(colliding_items[i])) == typeid(Ghost)){
            if (ghost->superpillow == false){
                pac_man->revive();
                ghost->revive2();
                lifes_label->setPlainText("Lifes: " + QString::number(pac_man->lifes));
                return;
            }
            else {
                scene->removeItem(ghost);
                connect(ghost->timer_revive,SIGNAL(timeout()),ghost,SLOT(revive1()));
                ghost->timer_revive->start(5000);
                points += 50;
                points_label->setPlainText("Points: " + QString::number(points));
                return;
            }

        }
    }
}

/**
 * @brief Levels::check_ghost_collision Verfica la colision del fantasma con los objetos
 */
void Levels::check_ghost_collision()
{
        QList<QGraphicsItem *> colliding_items_ghost = ghost->collidingItems();
        for (int i = 0, n = colliding_items_ghost.size(); i < n; ++i){
            if (typeid(*(colliding_items_ghost[i])) == typeid(SuperDot)){
                        scene->removeItem(colliding_items_ghost[i]);
                        delete colliding_items_ghost[i];
                        return;
                    }
        }
}

/**
 * @brief Levels::check_points Verifica la cantidad de putnos para poner una super pastilla
 */
void Levels::check_points()
{
    if (points % 200 == 0){

        SuperDot *super_dot = new SuperDot();
        scene->addItem(super_dot);
        super_dot->setPos(420,600/2);
        points += 10;

        ghost->timer_move_to_pacman->stop();
        ghost->setPos_to_pillow();
        ghost->i = 1;
        ghost->timer_move_to_pillow->start(70); //Signal every 50 miliseconds

    }
}

/**
 * @brief Levels::set_pac_position Define la poscion de el pacman a los fantasmas
 */
void Levels::set_pac_position()
{
    ghost->setPosX_Pacman(pac_man->position_x);
    ghost->setPosY_Pacman(pac_man->position_y);
    ghost->set_pac_direction(pac_man->direcction);
}

/**
 * @brief Levels::init_level Inicia el laberinto con los obstaculos y las pastillas
 */
void Levels::init_level()
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
