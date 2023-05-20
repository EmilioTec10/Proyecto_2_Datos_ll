#ifndef PROYECTO_2_DATOS_LL_VELOCIMETER_H
#define PROYECTO_2_DATOS_LL_VELOCIMETER_H


#include <QArgument>

class Velocimeter {
public:
   char primerDato[1024];
   char segundoDato[1024];
public slots:
    void SocketServer();
    void setLevel(char level);
    void setPoints(char points);
    void setLifes(char lifes);
    int data1;
    int data2;

private:
    char level;
    char points;
    char lifes;

};
#endif //PROYECTO_2_DATOS_LL_VELOCIMETER_H
