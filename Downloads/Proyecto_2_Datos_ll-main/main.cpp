#include "Main_Window.h"
#include "Thread.h"
#include <QApplication>

Main_Window *window;

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Thread thread1("A");
    thread1.start();
    window = new Main_Window();
    window->show();



    return a.exec();


}
