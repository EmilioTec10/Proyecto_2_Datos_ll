#ifndef GHOST4_H
#define GHOST4_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include "AStar.h"

class Ghost4:public QObject , public  QGraphicsPixmapItem{
    Q_OBJECT
public:
    Ghost4();
    void super_pillow();
    bool superpillow = false;
    char direcction = 'D';
    int speed = 5;

    void setPosX_Pacman(int posX_Pacman);
    void setPosY_Pacman(int posY_Pacman);
    void set_mapa(char mapa[21][30]);
    void set_pac_direction(char pac_direction);
    void setList(pair<int,int> list[51]);
    void setPos_to_pillow();
    void revive2();

    QTimer *timer_super;
    QTimer *set_to_pacman;
    QTimer *timer_move_to_pacman;
    QTimer *timer_move_to_pillow;
    QTimer *timer_animation;
    QTimer *timer_revive = new QTimer();

    AStar *astar = new AStar();

    int i = 1;

public slots:
    void move_to_pacman();
    void setPos_to_pacman();
    void move_to_pillow();
    void quit_super_pillow();
    void change_pix();
    void revive1();
private:
    int posX_Pacman = 10;
    int posY_Pacman = 14;
    float com_x = 0.0;
    float com_y = 0.0;
    char pac_direction = 'R';
    int position_x = 18;
    int position_y = 3;
    char mapa[21][30];
    pair<int,int> list[51];
    QGraphicsScene *m_scene;
};

#endif // GHOST4_H
