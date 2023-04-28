#ifndef PAC_MAN_H
#define PAC_MAN_H

#include <QGraphicsPixmapItem>
#include <QTimer>

class Pac_Man: public QObject , public  QGraphicsPixmapItem{
     Q_OBJECT
public:

    Pac_Man();
    bool super_pastilla = false;
    int speed = 30;
    int points = 0;
    char direcction = 'R';
    void keyPressEvent(QKeyEvent *event);
    void set_points_label(QGraphicsTextItem *points_label);

    QTimer *timer_animation = new QTimer;
public slots:
    void check_collision();
    void move();
    void animation_R();
    void animation_L();
    void animation_U();
    void animation_D();
private:
    QGraphicsTextItem *points_label;
};

#endif // PAC_MAN_H
