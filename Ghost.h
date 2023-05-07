#ifndef GHOST_H
#define GHOST_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Ghost:public QObject , public  QGraphicsPixmapItem{
    Q_OBJECT
public:
    Ghost();
    void super_pillow();
    bool superpillow = false;
    char direcction = 'D';
    int speed = 5;

    void setPosX_Pacman(int posX_Pacman);
    void setPosY_Pacman(int posY_Pacman);
    void set_mapa(char mapa[21][30]);
    void set_pac_direction(char pac_direction);

    QTimer *timer_super;

public slots:
    void move();
    void quit_super_pillow();
    void change_pix();
private:
    int posX_Pacman = 10;
    int posY_Pacman = 14;
    float com_x = 0.0;
    float com_y = 0.0;
    char pac_direction = 'R';
    int position_x = 1;
    int position_y = 27;
    char mapa[21][30];
};

#endif // GHOST_H
