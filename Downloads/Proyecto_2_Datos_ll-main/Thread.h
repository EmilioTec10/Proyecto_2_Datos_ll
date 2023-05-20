#ifndef  THREAD_H
#define  THREAD_H

#include <QThread>
#include <QString>


class Thread : public QThread
{
public:
    // constructor
    // set name using initializer
    explicit Thread(QString s);

    // overriding the QThread's run() method
    void run();
private:
    QString name;
};

#endif // THREAD_H

