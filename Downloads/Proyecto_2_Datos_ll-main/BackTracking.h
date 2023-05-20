#ifndef PROYECTO_2_DATOS_LL_BACKTRACKING_H
#define PROYECTO_2_DATOS_LL_BACKTRACKING_H

#include <QGraphicsPixmapItem>


class BackTracking: public QObject , public  QGraphicsPixmapItem{
    Q_OBJECT
public:


    QTimer *timer;
    QPoint currentPoint = {1, 27};  // Punto actual
    QPoint targetPoint;

    double distance(const QPoint& p1, const QPoint& p2);
    bool backtrack(const QPoint& current, const QPoint& target, std::vector<QPoint>& moves, int maxDepth);

    void backtrack(QPoint currentPoint, QPoint targetPoint, int& nextMoveX, int& nextMoveY);
    QPoint  determineNextMove(const QPoint& current, const QPoint& target, int maxDepth);

};
#endif
