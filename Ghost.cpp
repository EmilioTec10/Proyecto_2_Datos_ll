#include "Ghost.h"
#include <QTimer>

Ghost::Ghost()
{
    setPixmap(QPixmap(":/Images/GhostD.png"));

    QTimer *timer_move = new QTimer;
    connect(timer_move,SIGNAL(timeout()),this,SLOT(move())); //conect method that repeats the method everytime it recives the signal
    timer_move->start(500); //Signal every 50 miliseconds

    QTimer *timer_animation = new QTimer;
    connect(timer_animation,SIGNAL(timeout()),this,SLOT(change_pix())); //conect method that repeats the method everytime it recives the signal
    timer_animation->start(500); //Signal every 50 miliseconds
}

void Ghost::super_pillow()
{
    superpillow = true;
    setPixmap(QPixmap(":/Images/GhostT.png"));
    timer_super = new QTimer;
    connect(timer_super,SIGNAL(timeout()),this,SLOT(quit_super_pillow()));
    timer_super->start(3000);
}

void Ghost::setPosX_Pacman(int posX_Pacman)
{
    this->posX_Pacman = posX_Pacman;
}

void Ghost::setPosY_Pacman(int posY_Pacman)
{
    this->posY_Pacman = posY_Pacman;
}

void Ghost::set_mapa(char mapa[21][30])
{
    for (int i = 0;i < 21;i++){
        for(int j = 0;j < 30;j++){
            this->mapa[i][j] = mapa[i][j];
        }
    }
}

void Ghost::set_pac_direction(char pac_direction)
{
    this->pac_direction = pac_direction;
}

void Ghost::move()
{
    if (position_x == posX_Pacman){
        if (position_y > posY_Pacman){
            if (x() > 30 && mapa[position_x][position_y - 1] != 'X'){
               setPos(x() - 30,y());
               direcction = 'L';
               position_y--;
               return;
            }
            else if (y() > 30 && mapa[position_x - 1][position_y] != 'X'){
                setPos(x(),y() - 30);
                direcction = 'U';
                position_x--;
                return;
            }
            else if (y() < 540 && mapa[position_x + 1][position_y] != 'X'){
                setPos(x(),y() + 30);
                direcction = 'D';
                position_x++;
                return;
            }
            if (x() < 810 && mapa[position_x][position_y + 1] != 'X'){
               setPos(x() + 30,y());
               direcction = 'R';
               position_y++;
               return;
            }
        }
        else if (position_y < posY_Pacman){
            if (x() < 810 && mapa[position_x][position_y + 1] != 'X'){
               setPos(x() + 30,y());
               direcction = 'R';
               position_y++;
               return;
            }
            else if (y() > 30 && mapa[position_x - 1][position_y] != 'X'){
                setPos(x(),y() - 30);
                direcction = 'U';
                position_x--;
                return;
            }
            else if (y() < 540 && mapa[position_x + 1][position_y] != 'X'){
                setPos(x(),y() + 30);
                direcction = 'D';
                position_x++;
                return;
            }
            else if (x() > 30 && mapa[position_x][position_y - 1] != 'X'){
                setPos(x() - 30,y());
                direcction = 'L';
                position_y--;
                return;
             }
        }
    }
    else if (position_x < posX_Pacman){
        if (y() < 540 && mapa[position_x + 1][position_y] != 'X'){
            setPos(x(),y() + 30);
            direcction = 'D';
            position_x++;
            return;
        }
        else if (pac_direction == 'R' && x() < 810 && mapa[position_x][position_y + 1] != 'X'){
            setPos(x() + 30,y());
            direcction = 'R';
            position_y++;
            return;
        }
        else if (pac_direction == 'L' && x() > 30 && mapa[position_x][position_y - 1] != 'X'){
            setPos(x() - 30,y());
            direcction = 'L';
            position_y--;
            return;
        }
        else if (y() > 30 && mapa[position_x - 1][position_y] != 'X'){
            setPos(x(),y() - 30);
            direcction = 'U';
            position_x--;
            return;
        }
    }
    else {
        qDebug() << mapa[position_x][position_y - 1];
        if (y() > 30 && mapa[position_x - 1][position_y] != 'X'){
            setPos(x(),y() - 30);
            direcction = 'U';
            position_x--;
            return;
        }
        else if (x() > 30 && mapa[position_x][position_y - 1] != 'X'){
            setPos(x() - 30,y());
            direcction = 'L';
            position_y--;
            return;
        }
        else if (x() < 810 && mapa[position_x][position_y + 1] != 'X'){
            setPos(x() + 30,y());
            direcction = 'R';
            position_y++;
            return;
        }
        else if (y() < 540 && mapa[position_x + 1][position_y] != 'X'){
            setPos(x(),y() + 30);
            direcction = 'D';
            position_x++;
            return;
        }
    }
}

void Ghost::quit_super_pillow()
{
    setPixmap(QPixmap(":/Images/GhostD.png"));
    superpillow = false;
    timer_super->stop();
}

void Ghost::change_pix()
{
    if (superpillow == true){
        return;
    }
    if (direcction == 'L'){
        setPixmap(QPixmap(":/Images/GhostL.png"));
        return;
    }
    else if (direcction == 'D'){
        setPixmap(QPixmap(":/Images/GhostD.png"));
        return;
    }
    else if (direcction == 'U'){
        setPixmap(QPixmap(":/Images/GhostU.png"));
        return;
    }
    else {
        setPixmap(QPixmap(":/Images/GhostR.png"));
        return;
    }
}
