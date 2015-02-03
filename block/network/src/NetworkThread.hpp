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
    // Pointer on the network
    QPointer<NetworkBlock> _network;

    //! FROM QThread
    void run();



};


#endif // NETWORKTHREAD_HPP
