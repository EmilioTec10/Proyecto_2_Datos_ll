#ifndef PAC_MAN_H
#define PAC_MAN_H

#include <QGraphicsPixmapItem>
#include <QTimer>

class Pac_Man: public QObject , public  QGraphicsPixmapItem{
     Q_OBJECT
public:

    Pac_Man();
    bool super_pastilla = false;
    int speed = 5;
    char direcction = 'R';
    void keyPressEvent(QKeyEvent *event);

    QTimer *timer_animation = new QTimer;;
public slots:

    void move();
    void animation_R();
    void animation_L();
    void animation_U();
    void animation_D();
};

#endif // PAC_MAN_H
