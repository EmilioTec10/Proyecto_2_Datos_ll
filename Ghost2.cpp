#include "Ghost2.h"
#include "AStar.h"
#include <QTimer>

Ghost2::Ghost2()
{
    setPixmap(QPixmap(":/Images/Ghost2D.png"));

    timer_move_to_pacman = new QTimer();
    connect(timer_move_to_pacman,SIGNAL(timeout()),this,SLOT(move_to_pacman())); //conect method that repeats the method everytime it recives the signal
    timer_move_to_pacman->start(70);


    timer_move_to_pillow = new QTimer();
    connect(timer_move_to_pillow,SIGNAL(timeout()),this,SLOT(move_to_pillow())); //conect method that repeats the method everytime it recives the signal

    timer_animation = new QTimer;
    connect(timer_animation,SIGNAL(timeout()),this,SLOT(change_pix())); //conect method that repeats the method everytime it recives the signal
    timer_animation->start(70); //Signal every 50 miliseconds

}

void Ghost2::super_pillow()
{
    superpillow = true;
    setPixmap(QPixmap(":/Images/GhostT.png"));
    timer_super = new QTimer;
    connect(timer_super,SIGNAL(timeout()),this,SLOT(quit_super_pillow()));
    timer_super->start(3000);
}

void Ghost2::setPosX_Pacman(int posX_Pacman)
{
    this->posX_Pacman = posX_Pacman;
}

void Ghost2::setPosY_Pacman(int posY_Pacman)
{
    this->posY_Pacman = posY_Pacman;
}

void Ghost2::set_mapa(char mapa[21][30])
{
    for (int i = 0;i < 21;i++){
        for(int j = 0;j < 30;j++){
            this->mapa[i][j] = mapa[i][j];
        }
    }
    setPos_to_pacman();
}

void Ghost2::set_pac_direction(char pac_direction)
{
    this->pac_direction = pac_direction;
}

void Ghost2::setList(pair<int, int> list[])
{
    for (int i = 0;i < 51;i++){
        this->list[i] = list[i];
    }
}

void Ghost2::setPos_to_pillow(){
    // Source is the left-most bottom-most corner
    AStar::Pair src = make_pair(position_x, position_y);

    // Destination is the left-most top-most corner
    AStar::Pair dest = make_pair(10, 14);
    astar->aStarSearch(mapa,src,dest);
    setList(astar->list);
}

void Ghost2::revive()
{
    int position_x = 1;
    int position_y = 1;
    float com_x = 0.0;
    float com_y = 0.0;
    char direcction = 'D';

    timer_move_to_pacman->stop();
    timer_move_to_pillow->stop();
    timer_animation->stop();
    setPos_to_pacman();
    qDebug() << posX_Pacman << ", " << posY_Pacman;
    setPos(30,30);


    timer_move_to_pacman->start(70);
    timer_animation->start(70);


}
void Ghost2::move_to_pillow()
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
            timer_move_to_pillow->stop();
            timer_move_to_pacman->start(70);
            setPos_to_pacman();
            i = 1;
            return;
        }


}

void Ghost2::move_to_pacman()
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
            setPos_to_pacman();
            i = 1;
            return;
        }

}

void Ghost2::setPos_to_pacman()
{
    // Source is the left-most bottom-most corner
    AStar::Pair src = make_pair(position_x, position_y);

    // Destination is the left-most top-most corner
    AStar::Pair dest = make_pair(posX_Pacman, posY_Pacman);
    astar->aStarSearch(mapa,src,dest);
    setList(astar->list);
}

void Ghost2::quit_super_pillow()
{
    setPixmap(QPixmap(":/Images/Ghost2D.png"));
    superpillow = false;
    timer_super->stop();
}

void Ghost2::change_pix()
{
    if (superpillow == true){
        return;
    }
    if (direcction == 'L'){
        setPixmap(QPixmap(":/Images/Ghost2L.png"));
        return;
    }
    else if (direcction == 'D'){
        setPixmap(QPixmap(":/Images/Ghost2D.png"));
        return;
    }
    else if (direcction == 'U'){
        setPixmap(QPixmap(":/Images/Ghost2U.png"));
        return;
    }
    else {
        setPixmap(QPixmap(":/Images/Ghost2R.png"));
        return;
    }
}
