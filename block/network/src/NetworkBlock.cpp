#include <NetworkBlock.hpp>

//! Block properties
#define _BLOCK_PROPERTIES_  {"netname"}

/* ============================================================================
 *
 * */
EXPORT_BLOCK(NetworkBlock);

/* ============================================================================
 *
 * */
NetworkBlock::NetworkBlock(const QString& name, QObject *parent)
    : BotBlock(name, QVector<QString>(_BLOCK_PROPERTIES_), parent)
    , _udpSocket(new QUdpSocket(this))
{
/*    udpSocket->bind(QHostAddress::LocalHost, 7755);

    connect(udpSocket, SIGNAL(readyRead()),
             this, SLOT(readPendingDatagrams()));*/
}


/* ============================================================================
 *
 * */
void NetworkBlock::init(QSharedPointer<BotEngine> js_engine)
{
    BotBlock::init(js_engine);
}



/*void Server::readPendingDatagrams()
 {
     while (udpSocket->hasPendingDatagrams()) {
         QByteArray datagram;
         datagram.resize(udpSocket->pendingDatagramSize());
         QHostAddress sender;
         quint16 senderPort;

         udpSocket->readDatagram(datagram.data(), datagram.size(),
                                 &sender, &senderPort);

         processTheDatagram(datagram);
     }
 }*/
