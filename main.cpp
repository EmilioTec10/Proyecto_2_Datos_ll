#include "Main_Window.h"
#include <QApplication>

Main_Window *window;



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    window = new Main_Window();
    window->show();
    return a.exec();
}
