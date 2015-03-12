//!
//! \file NetworkBlock.cpp
//!
// Copyright 2015 MakingBot
// This file is part of BotJs.
//
// BotJs is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// BotJs is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with BotJs.  If not, see <http://www.gnu.org/licenses/>.

#include <NetworkBlock.hpp>

#include <iostream>
using namespace std;

/* ============================================================================
 *
 * */
EXPORT_BLOCK(NetworkBlock)

/* ============================================================================
 *
 * */
NetworkBlock::NetworkBlock(const QString& name)
    : BotBlock(name)
    , _isActivated(false), _thread(this)
    , _udpSocket(new QUdpSocket())
    , _tcpSocket(new QTcpSocket())
{


//   _udpSocket->moveToThread(this);


    
    
    connect(_udpSocket.data(), SIGNAL(readyRead()), this, SLOT(processPendingUdpDatagrams()));

}

/* ============================================================================
 *
 * */
void NetworkBlock::dispatch(const QHostAddress& sender, const QByteArray& datagram)
{
    // Create a stream to parse the datagram
    QDataStream stream( datagram );
    
    // Get the message type
    quint16 type;
    stream >> type;
    NetMsgType msgType = (NetMsgType)type;
    
    // Action depend on the message type
    switch( msgType )
    {
        case NET_PING               :
            onRxPing(sender);
            break;
            
        case NET_PING_ACK           :
            onRxPingAck(sender, stream);
            break;
            
        case NET_TEST               :
            break;
            
        case NET_BLOCK_CREATE       :
            break;
        
        case NET_BLOCK_UPDATE       :
            break;
        
        case NET_BLOCK_CONNECT      :
            break;
            
        case NET_BLOCK_DISCONNECT   :
            break;
        
        case NET_BLOCK_DESTROY      :
            break;
        
        default:
            BLOCK_WARNING("Unknown network message !");
            break;
    }
}

/* ============================================================================
 *
 * */
void NetworkBlock::onRxPing(const QHostAddress& sender)
{
    // Log
    BLOCK_LOG("Ping received !");


}

void NetworkBlock::onRxPingAck(const QHostAddress& sender, QDataStream& stream);

/* ============================================================================
 *
 * */
void NetworkBlock::processPendingUdpDatagrams()
{
    quint16      port;
    QHostAddress sender;     
    QByteArray   datagram;
    
    // Prepare the datagram
    datagram.resize( _udpSocket->pendingDatagramSize() );
    
    // Read data
    _udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &port);

    // Dispatch the message
    dispatch(sender, datagram);
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


/* ============================================================================
 *
 * */
void NetworkBlock::ping()
{
    switch( coreCfg() )
    {
        case CoreCfgDev :
        {
            // Declare the datagram
            QByteArray datagram;

            // Create a stream to fill it
            QDataStream stream( &datagram, QIODevice::WriteOnly );

            // Append the type
            stream << (quint16)NET_PING;

            // Broadcast the message
            _udpSocket->writeDatagram(datagram.data(), datagram.size(), QHostAddress::Broadcast, _port);
            
            // Log
            BLOCK_LOG("Message broadcasted: Ping !");
            break;
        }

        case CoreCfgBot :
        {
            BLOCK_WARNING("Core in Bot Cfg, Ping is not autorized");
            break;
        }
    }
}


