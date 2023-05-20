#ifndef PROYECTO_2_DATOS_LL_VELOCIMETER_H
#define PROYECTO_2_DATOS_LL_VELOCIMETER_H


#include <QArgument>

class Velocimeter {
public:
   char primerDato;
   char segundoDato;
public slots:
    void SocketServer();
    void setX(char x);
    void setY(char y);
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
