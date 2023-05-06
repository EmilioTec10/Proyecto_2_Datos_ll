#ifndef PAC_MAN_H
#define PAC_MAN_H

#include <QGraphicsPixmapItem>
#include <QTimer>

class Pac_Man: public QObject , public  QGraphicsPixmapItem{
     Q_OBJECT
public:

    Pac_Man();
    bool super_dot = false;
    int speed = 30;
    char direcction = 'R';
    void keyPressEvent(QKeyEvent *event);
    void set_points_label(QGraphicsTextItem *points_label);
    void set_lifes_label(QGraphicsTextItem *lifes_label);
    void set_mapa(char mapa[21][30]);

    int position_x = 10;
    int position_y = 14;
    int lifes = 3;

    QTimer *timer_animation = new QTimer;
    QTimer *timer_move;
    QTimer *die_timer = new QTimer;
public slots:
    void move();
    void animation_R();
    void animation_L();
    void animation_U();
    void animation_D();
    void revive();
private:
    QGraphicsTextItem *points_label;
    QGraphicsTextItem *lifes_label;
    char mapa[21][30];
};

#endif // PAC_MAN_H
