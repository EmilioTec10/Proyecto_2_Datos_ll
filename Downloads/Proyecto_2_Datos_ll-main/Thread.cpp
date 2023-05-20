

#include "Thread.h"
#include <QDebug>
#include <iostream>
#include "Main_Window.h"
#include "Velocimeter.h"
Velocimeter *velo;
Thread::Thread(QString s) : name(s)
{
}

// We overrides the QThread's run() method here
// run() will be called when a thread starts
// the code will be shared by all threads

void Thread::run()
{
    while (true){
        velo->SocketServer();
    }

}
