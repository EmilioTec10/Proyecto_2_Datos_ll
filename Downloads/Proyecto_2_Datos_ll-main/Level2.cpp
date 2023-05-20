#include "Level2.h"
#include "Level3.h"
#include "Blocks.h"
#include "Ghost.h"
#include "Dots.h"
#include "SuperDot.h"
#include "Lose_Window.h"
#include <QTimer>
#include <QGraphicsRectItem>
#include <iostream>

/**
 * @brief Level2::Level2 Construcotr que inicia la pantalla del juego
 * @param parent Hace posible que se incie
 */
Level2::Level2(QWidget *parent)
{
    //Creation and configuration of the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,870,620);
    scene->setBackgroundBrush(QBrush(QImage(":/Images/back.png")));
    QFont font("Arial", 15, QFont::Helvetica);

    init_level();

    ghost_1 = new Ghost();
    ghost_2 = new Ghost2();
    pac_man = new Pac_Man();
    pac_man->lifes = 3;

    col = new QTimer();
    connect(col,SIGNAL(timeout()),this,SLOT(check_collision()));
    col->start(100);

    timer_lose = new QTimer();
    connect(timer_lose,SIGNAL(timeout()),this,SLOT(check_lose()));
    timer_lose->start(100);

    col_ghost1 = new QTimer();
    connect(col_ghost1,SIGNAL(timeout()),this,SLOT(check_ghost1_collision()));
    col_ghost1->start(100);

    col_ghost2 = new QTimer();
    connect(col_ghost2,SIGNAL(timeout()),this,SLOT(check_ghost2_collision()));
    col_ghost2->start(100);

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

    scene->addItem(pac_man);
    scene->addItem(ghost_1);
    scene->addItem(ghost_2);
    scene->addItem(points_label);
    scene->addItem(lifes_label);

    points_label->setPos(720,590);
    lifes_label->setPos(600,590);
    ghost_1->setPos(810,30);
    ghost_1->set_mapa(mapa);
    ghost_1->setScene(scene);
    ghost_2->setPos(90,30);
    ghost_2->set_mapa(mapa);
    ghost_2->setScene(scene);

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
 * @brief Level2::setPoints Define los puntos actuales en una varible
 * @param points Variable a definir
 */
void Level2::setPoints(int points)
{
 this->points = points;
}

/**
 * @brief Level2::check_win Verifica si el jugador consiguio todas las pastillas para pasar de nivel
 */
void Level2::check_win()
{
    if (pillows == 0){
        timer_level->stop();
        timer_points->stop();
        this->close();
        Level3 *level3 = new Level3();
        level3->setPoints(points);
        level3->show();
    }
}

/**
 * @brief Level2::check_lose Verifica la cantidad de vidas del jugador para ver si ya perdio
 */
void Level2::check_lose()
{
    if (pac_man->lifes <= 0){
        timer_level->stop();
        timer_points->stop();
        timer_lose->stop();
        this->close();
        Game_Over *window = new Game_Over();
        window->show();
    }
}

/**
 * @brief Level2::check_collision Verifica la colision de el pacman con los objetos
 */
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
            points += 50;
            ghost_1->super_pillow();
            ghost_2->super_pillow();
            return;
        }
    }
}

/**
 * @brief Level2::check_ghost1_collision Verfica la colision del fantasma con los objetos
 */
void Level2::check_ghost1_collision()
{
        QList<QGraphicsItem *> colliding_items_ghost = ghost_1->collidingItems();
        for (int i = 0, n = colliding_items_ghost.size(); i < n; ++i){
            if (typeid(*(colliding_items_ghost[i])) == typeid(SuperDot)){
                        scene->removeItem(colliding_items_ghost[i]);
                        delete colliding_items_ghost[i];
                        return;
                    }
            else if (typeid(*(colliding_items_ghost[i])) == typeid(Pac_Man)){
                if (ghost_1->superpillow == false){
                    pac_man->revive();
                    lifes_label->setPlainText("Lifes: " + QString::number(pac_man->lifes));
                    ReviveGhosts();
                    return;
                }
                else {
                    scene->removeItem(ghost_1);
                    connect(ghost_1->timer_revive,SIGNAL(timeout()),ghost_1,SLOT(revive1()));
                    ghost_1->timer_revive->start(5000);
                    points += 50;
                    points_label->setPlainText("Points: " + QString::number(points));
                    return;
                }

            }
        }
}

/**
 * @brief Level2::check_ghost2_collision Verfica la colision del fantasma con los objetos
 */
void Level2::check_ghost2_collision()
{
        QList<QGraphicsItem *> colliding_items_ghost = ghost_2->collidingItems();
        for (int i = 0, n = colliding_items_ghost.size(); i < n; ++i){
            if (typeid(*(colliding_items_ghost[i])) == typeid(SuperDot)){
                        scene->removeItem(colliding_items_ghost[i]);
                        delete colliding_items_ghost[i];
                        return;
                    }
            else if (typeid(*(colliding_items_ghost[i])) == typeid(Pac_Man)){
                if (ghost_2->superpillow == false){
                    pac_man->revive();
                    ReviveGhosts();
                    lifes_label->setPlainText("Lifes: " + QString::number(pac_man->lifes));
                    return;
                }
                else {
                    scene->removeItem(ghost_2);
                    connect(ghost_2->timer_revive,SIGNAL(timeout()),ghost_2,SLOT(revive1()));
                    ghost_2->timer_revive->start(5000);
                    points += 50;
                    points_label->setPlainText("Points: " + QString::number(points));
                    return;
                }

            }
        }
}

/**
 * @brief Level2::check_points Verifica la cantidad de putnos para poner una super pastilla
 */
void Level2::check_points()
{
    if (points % 200 == 0){

        SuperDot *super_dot = new SuperDot();
        scene->addItem(super_dot);
        super_dot->setPos(420,600/2);
        //ghost->set_to_pacman->stop();

        ghost_1->timer_move_to_pacman->stop();
        ghost_1->setPos_to_pillow();
        ghost_1->i = 1;
        ghost_1->timer_move_to_pillow->start(70); //Signal every 50 miliseconds

        ghost_2->timer_move_to_pacman->stop();
        //se pone el baxktracking

    }
}

/**
 * @brief Level2::set_pac_position Define la poscion de el pacman a los fantasmas
 */
void Level2::set_pac_position()
{
    ghost_1->setPosX_Pacman(pac_man->position_x);
    ghost_1->setPosY_Pacman(pac_man->position_y);
    ghost_1->set_pac_direction(pac_man->direcction);

    ghost_2->setPosX_Pacman(pac_man->position_x);
    ghost_2->setPosY_Pacman(pac_man->position_y);
    ghost_2->set_pac_direction(pac_man->direcction);
}

/**
 * @brief Level2::ReviveGhosts Funcion que revive los fantasmas del nivel
 */
void Level2::ReviveGhosts()
{
    ghost_1->revive2();
    ghost_2->revive2();
}

/**
 * @brief Level2::init_level Inicia el laberinto con los obstaculos y las pastillas
 */
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

