#ifndef NETWORKTHREAD_HPP
#define NETWORKTHREAD_HPP

#include <QMutex>
#include <QThread>
#include <QPointer>

class NetworkBlock;


class NetworkThread : public QThread
{
    Q_OBJECT


public:

    explicit NetworkThread(QObject *parent = 0);


protected:

    //! FROM QThread
    void run();



};


#endif // NETWORKTHREAD_HPP
