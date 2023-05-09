#include "Ghost.h"
#include "AStar.h"
#include <QTimer>

Ghost::Ghost()
{
    setPixmap(QPixmap(":/Images/GhostD.png"));
    /*
    set_to_pacman = new QTimer();
    connect(set_to_pacman,SIGNAL(timeout()),this,SLOT(setPos_to_pacman()));
    set_to_pacman->start(80);

    timer_move_to_pacman = new QTimer();
    connect(timer_move_to_pacman,SIGNAL(timeout()),this,SLOT(move_to_pacman())); //conect method that repeats the method everytime it recives the signal
    timer_move_to_pacman->start(80);
    */

    timer_move_to_pillow = new QTimer();
    connect(timer_move_to_pillow,SIGNAL(timeout()),this,SLOT(move_to_pillow())); //conect method that repeats the method everytime it recives the signal

    QTimer *timer_animation = new QTimer;
    connect(timer_animation,SIGNAL(timeout()),this,SLOT(change_pix())); //conect method that repeats the method everytime it recives the signal
    timer_animation->start(80); //Signal every 50 miliseconds
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
    setPos_to_pillow();
}

void Ghost::set_pac_direction(char pac_direction)
{
    this->pac_direction = pac_direction;
}

void Ghost::setList(pair<int, int> list[])
{
    for (int i = 0;i < 51;i++){
        this->list[i] = list[i];
    }
}

int i = 1;
void Ghost::setPos_to_pillow(){
    // Source is the left-most bottom-most corner
    AStar::Pair src = make_pair(position_x, position_y);

    // Destination is the left-most top-most corner
    AStar::Pair dest = make_pair(10, 14);
    astar->aStarSearch(mapa,src,dest);
    setList(astar->list);
}
void Ghost::move_to_pillow()
{
    int posx = list[i].first - position_x;
    int posy = list[i].second - position_y;
        if (posx  == 1){
            setPos(x(),y() + 5);
            direcction = 'D';
            com_y += 0.17;
            if (com_y >= 1.0){
                i++;
                position_x++;
                com_y = 0;
            }
            return;
        }
        if (posx  == -1){
            setPos(x(),y() - 5);
            direcction = 'U';
            com_y -= 0.17;
            if (com_y <= -1.0){
                i++;
                position_x--;
                com_y = 0;
            }
            return;
        }
        if (posy  == 1){
            setPos(x() + 5,y());
            direcction = 'R';
            com_x += 0.17;
            if (com_x >= 1.0){
                i++;
                position_y++;
                com_x = 0;
            }
            return;
        }
        if (posy == -1){
            setPos(x() - 5,y());
            direcction = 'L';
            com_x -= 0.17;
            if (com_x <= -1.0){
                i++;
                position_y--;
                com_x = 0;
            }
            return;
        }
        else{
            return;
        }


}

void Ghost::move_to_pacman()
{
    int posx = list[i].first - position_x;
    int posy = list[i].second - position_y;
        if (posx  == 1){
            setPos(x(),y() + 5);
            direcction = 'D';
            com_y += 0.17;
            if (com_y >= 1.0){
                i++;
                position_x++;
                com_y = 0;
            }
            return;
        }
        if (posx  == -1){
            setPos(x(),y() - 5);
            direcction = 'U';
            com_y -= 0.17;
            if (com_y <= -1.0){
                i++;
                position_x--;
                com_y = 0;
            }
            return;
        }
        if (posy  == 1){
            setPos(x() + 5,y());
            direcction = 'R';
            com_x += 0.17;
            if (com_x >= 1.0){
                i++;
                position_y++;
                com_x = 0;
            }
            return;
        }
        if (posy == -1){
            setPos(x() - 5,y());
            direcction = 'L';
            com_x -= 0.17;
            if (com_x <= -1.0){
                i++;
                position_y--;
                com_x = 0;
            }
            return;
        }
        else{
            return;
        }

}

void Ghost::setPos_to_pacman()
{
    // Source is the left-most bottom-most corner
    AStar::Pair src = make_pair(position_x, position_y);

    // Destination is the left-most top-most corner
    AStar::Pair dest = make_pair(posX_Pacman, posY_Pacman);
    astar->aStarSearch(mapa,src,dest);
    setList(astar->list);
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
