#include "Ghost4.h"
#include "AStar.h"
#include <QTimer>
#include <QGraphicsScene>

/**
 * @brief Ghost4::Ghost4 Constructor que crea un fantasma de color rosado apartir del nivel 4
 */
Ghost4::Ghost4()
{
    setPixmap(QPixmap(":/Images/Ghost4D.png"));

    timer_move_to_pacman = new QTimer();
    connect(timer_move_to_pacman,SIGNAL(timeout()),this,SLOT(move_to_pacman())); //conect method that repeats the method everytime it recives the signal
    timer_move_to_pacman->start(70);


    timer_move_to_pillow = new QTimer();
    connect(timer_move_to_pillow,SIGNAL(timeout()),this,SLOT(move_to_pillow())); //conect method that repeats the method everytime it recives the signal

    timer_animation = new QTimer;
    connect(timer_animation,SIGNAL(timeout()),this,SLOT(change_pix())); //conect method that repeats the method everytime it recives the signal
    timer_animation->start(70); //Signal every 50 miliseconds

}

/**
 * @brief Ghost4::super_pillow Metodo que pone vulnerable al fantasma cuando pacman se come la superpastilla
 */
void Ghost4::super_pillow()
{
    superpillow = true;
    setPixmap(QPixmap(":/Images/GhostT.png"));
    timer_super = new QTimer;
    connect(timer_super,SIGNAL(timeout()),this,SLOT(quit_super_pillow()));
    timer_super->start(3000);
}

/**
 * @brief Ghost4::setPosX_Pacman Configura la varible de la posicion en x del pacaman
 * @param posX_Pacman posicion en x del pac man
 */
void Ghost4::setPosX_Pacman(int posX_Pacman)
{
    this->posX_Pacman = posX_Pacman;
}

/**
 * @brief Ghost4::setPosY_Pacman Configura la variable de la posicion actuaal del pacman en el eje y
 * @param posY_Pacman Posicion en el eje y
 */
void Ghost4::setPosY_Pacman(int posY_Pacman)
{
    this->posY_Pacman = posY_Pacman;
}

/**
 * @brief Ghost4::set_mapa Configura la varible del mapa al inicio de cada nivel
 * @param mapa Mapa del laberinto
 */
void Ghost4::set_mapa(char mapa[21][30])
{
    for (int i = 0;i < 21;i++){
        for(int j = 0;j < 30;j++){
            this->mapa[i][j] = mapa[i][j];
        }
    }
    setPos_to_pacman();
}

/**
 * @brief Ghost4::set_pac_direction Configura la direccion del pacaman
 * @param pac_direction direccion actual del pacman
 */
void Ghost4::set_pac_direction(char pac_direction)
{
    this->pac_direction = pac_direction;
}

/**
 * @brief Ghost4::setList Define la lista de el algoritmo a* en esta clase
 * @param list lista del a*
 */
void Ghost4::setList(pair<int, int> list[])
{
    for (int i = 0;i < 51;i++){
        this->list[i] = list[i];
    }
}

/**
 * @brief Ghost4::setPos_to_pillow Define la posicion de la superpastilla para que el fantasma vaya hacia el
 */
void Ghost4::setPos_to_pillow(){
    // Source is the left-most bottom-most corner
    AStar::Pair src = make_pair(position_x, position_y);

    // Destination is the left-most top-most corner
    AStar::Pair dest = make_pair(10, 14);
    astar->aStarSearch(mapa,src,dest);
    setList(astar->list);
}

/**
 * @brief Ghost4::revive Metodo que hace que el fantasma reviva
 */
void Ghost4::revive1()
{
    position_x = 18;
    position_y = 3;
    com_x = 0.0;
    com_y = 0.0;
    direcction = 'D';
    superpillow = false;

    timer_move_to_pacman->stop();
    timer_move_to_pillow->stop();
    timer_animation->stop();
    setPos_to_pacman();
    qDebug() << posX_Pacman << ", " << posY_Pacman;
    setPos(90,540);


    timer_move_to_pacman->start(70);
    timer_animation->start(70);

    m_scene->addItem(this);
}


void Ghost4::revive2()
{
    position_x = 18;
    position_y = 3;
    com_x = 0.0;
    com_y = 0.0;
    direcction = 'D';
    superpillow = false;

    timer_move_to_pacman->stop();
    timer_move_to_pillow->stop();
    timer_animation->stop();
    setPos_to_pacman();
    qDebug() << posX_Pacman << ", " << posY_Pacman;
    setPos(90,540);


    timer_move_to_pacman->start(70);
    timer_animation->start(70);
}

/**
 * @brief Ghost4::move_to_pillow Define la posicion del pacman para que el fantasma vaya hacia el
 */
void Ghost4::move_to_pillow()
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

/**
 * @brief Ghost4::move_to_pacman Funcion que se mueve el fantasma en direccion al pacman
 */
void Ghost4::move_to_pacman()
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

/**
 * @brief Ghost4::setPos_to_pacman Define la poscion actual del pacman como obejtivo
 */
void Ghost4::setPos_to_pacman()
{
    // Source is the left-most bottom-most corner
    AStar::Pair src = make_pair(position_x, position_y);

    // Destination is the left-most top-most corner
    AStar::Pair dest = make_pair(posX_Pacman, posY_Pacman);
    astar->aStarSearch(mapa,src,dest);
    setList(astar->list);
}

/**
 * @brief Ghost4::quit_super_pillow Quita el efecto de superpastilla en el fantasma
 */
void Ghost4::quit_super_pillow()
{
    setPixmap(QPixmap(":/Images/Ghost4D.png"));
    superpillow = false;
    timer_super->stop();
}

/**
 * @brief Ghost4::change_pix Cambia las animaciones en timepo real
 */
void Ghost4::change_pix()
{
    if (superpillow == true){
        return;
    }
    if (direcction == 'L'){
        setPixmap(QPixmap(":/Images/Ghost4L.png"));
        return;
    }
    else if (direcction == 'D'){
        setPixmap(QPixmap(":/Images/Ghost4D.png"));
        return;
    }
    else if (direcction == 'U'){
        setPixmap(QPixmap(":/Images/Ghost4U.png"));
        return;
    }
    else {
        setPixmap(QPixmap(":/Images/Ghost4R.png"));
        return;
    }
}
