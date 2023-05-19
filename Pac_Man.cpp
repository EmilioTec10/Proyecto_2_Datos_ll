#include "Pac_Man.h"
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include <iostream>

int cycle = 0;

/**
 * @brief Pac_Man::Pac_Man Constructor que crea el objeto del pacman
 */
Pac_Man::Pac_Man()
{
    setPixmap(QPixmap(":/Images/pac_man_0R.png"));

    timer_move = new QTimer;
    connect(timer_move,SIGNAL(timeout()),this,SLOT(move())); //conect method that repeats the method everytime it recives the signal
    timer_move->start(55); //Signal every 50 miliseconds


    connect(timer_animation_R,SIGNAL(timeout()),this,SLOT(animation_R())); //conect method that repeats the method everytime it recives the signal
    connect(timer_animation_U,SIGNAL(timeout()),this,SLOT(animation_U())); //conect method that repeats the method everytime it recives the signal
    connect(timer_animation_D,SIGNAL(timeout()),this,SLOT(animation_D())); //conect method that repeats the method everytime it recives the signal
    connect(timer_animation_L,SIGNAL(timeout()),this,SLOT(animation_L())); //conect method that repeats the method everytime it recives the signal
    timer_animation_R->start(100); //Signal every 50 miliseconds
}

/**
 * @brief Pac_Man::keyPressEvent Funcion que detecta las entradas del teclado para mover el pacman
 * @param event Evento detectado
 */
void Pac_Man::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W){
        direcction = 'U';
        cycle = 0;
        timer_animation_D->stop();
        timer_animation_L->stop();
        timer_animation_R->stop();
        timer_animation_U->start(100);
    }
    if (event->key() == Qt::Key_S){
        direcction = 'D';
        cycle = 0;
        timer_animation_L->stop();
        timer_animation_R->stop();
        timer_animation_U->stop();
        timer_animation_D->start(100);
    }
    if (event->key() == Qt::Key_A){
        direcction = 'L';
        cycle = 0;
        timer_animation_L->start(100);
        timer_animation_R->stop();
        timer_animation_U->stop();
        timer_animation_D->stop();
    }
    if (event->key() == Qt::Key_D){
        direcction = 'R';
        cycle = 0;
        timer_animation_L->stop();
        timer_animation_R->start(100);
        timer_animation_U->stop();
        timer_animation_D->stop();
    }
}

/**
 * @brief Pac_Man::set_points_label Funcion que define la etiqueta de texto de los puntos
 * @param points_label Etiqueta de texto
 */
void Pac_Man::set_points_label(QGraphicsTextItem *points_label)
{
    this->points_label = points_label;
}

/**
 * @brief Pac_Man::set_lifes_label Define la etiqueta de texto de las vidas
 * @param lifes_label Etiqueta de las vidas
 */
void Pac_Man::set_lifes_label(QGraphicsTextItem *lifes_label)
{
    this->lifes_label = lifes_label;
}

/**
 * @brief Pac_Man::set_mapa Define el mapa en el objeto del pacman
 * @param mapa LAberinto a definir
 */
void Pac_Man::set_mapa(char mapa[21][30])
{
    for (int i = 0;i < 21;i++){
        for(int j = 0;j < 30;j++){
            this->mapa[i][j] = mapa[i][j];
        }
    }
}

/**
 * @brief Pac_Man::revive Hace que el pacman reviva con la posicion ajustada
 */
void Pac_Man::revive()
{
    timer_move->stop();

    lifes--;
    com_x = 0.0;
    com_y = 0.0;
    position_x = 10;
    position_y = 14;
    setPos(420,600/2);

    timer_move->start();
}

/**
 * @brief Pac_Man::move Funcion que hace posible que se mueva el pacman
 */
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

/**
 * @brief Pac_Man::animation_R Funcion de la animacion del movimiento a la derecha
 */
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

/**
 * @brief Pac_Man::animation_L Funcion de la animacion de movimiento a la izquierda
 */
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

/**
 * @brief Pac_Man::animation_U Funcion de la animacion del movimiento hacia arriba
 */
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

/**
 * @brief Pac_Man::animation_D Funcion de la animacion del movimiento hacia abajo
 */
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
