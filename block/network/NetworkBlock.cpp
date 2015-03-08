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
void NetworkBlock::processPendingUdpDatagrams()
{

    std::cout << "data income: " << _udpSocket->pendingDatagramSize() << std::endl;

    quint16      port;
    QHostAddress sender;     
    QByteArray   datagram;
    
    // Read data
    datagram.resize( _udpSocket->pendingDatagramSize() );
    _udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &port);

    std::cout << QString(datagram).toStdString() << std::endl;

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
