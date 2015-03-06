#ifndef NETWORKBLOCK_HPP
#define NETWORKBLOCK_HPP
//!
//! \file NetworkBlock.hpp
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

#include <QUdpSocket>
#include <BotBlock.hpp>
#include <QHostAddress>
#include <NetworkThread.hpp>

//!
//! Block that provides a communication interface for Network using IP on UDP/TCP
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class NetworkBlock : public BotBlock
{
    Q_OBJECT

    Q_PROPERTY(bool     activated   READ isActivated WRITE setActivated MEMBER _isActivated)
    Q_PROPERTY(quint16  port        READ port        WRITE setPort      MEMBER _port       )

public:

    //!
    //! Default constructor
    //!
    explicit NetworkBlock(const QString& name = QString("network"));

    // ========================================================================
    // => BotBlock redefinition

    //! FROM BotBlock
    virtual float blockVersion() const { return 1.0; }

    //! FROM BotBlock
    virtual BlockRole blockRole() const { return BotBlock::BlockSpy; }

    //! FROM BotBlock
    virtual QString blockTypeName() const { return QString("spy"); }

    // ========================================================================
    // => Network activation

    //!
    //! Activation status getter
    //!
    bool isActivated()
    {
        return _isActivated;
    }
    
    //!
    //! Activation status setter
    //!
    void setActivated(bool active)
    {
        if(active)
        {
            activate();
        }
        else
        {
            disactivate();
        } 
    }
    
    //!
    //! Activation status enable
    //!
    void activate()
    {
        _isActivated = true; 
    }

    //!
    //! Activation status disable
    //!
    void disactivate()
    {
        _isActivated = false;
    }

    // ========================================================================
    // => Network information

    //!
    //! Port getter
    //!
    quint16 port()
    {
        return _port;
    }

    //!
    //! Port setter
    //!
    void setPort(quint16 port)
    {
        // Set the new port
        _port = port;

        // Bind the new port
        _udpSocket->bind(_port, QUdpSocket::ShareAddress);
    }

public slots:

    //!
    //! Function that process incoming udp datagrams
    //!
    void processPendingUdpDatagrams();


    void ping()
    {

        QByteArray datagram("un message venu du block !!!!ddddddddddddddddddddddddddddddd\n"
       
        );

        _udpSocket->writeDatagram(datagram.data(),
                                    datagram.size(),
                                    QHostAddress::Broadcast,
                                    _port);
    }

protected:

    // ========================================================================
    // => Network activation

    //! Activated ?
    //! Activation status, True if the interface is activated
    bool _isActivated;
    
    // ========================================================================
    // => Network information

    //! Port
    //! Used port for the udp/tcp interface
    quint16  _port;

    //! Host address
    //! Address of the target robot
    QHostAddress _address;

    // ========================================================================
    // => Network socket

    //! UDP Socket
    QSharedPointer<QUdpSocket> _udpSocket;


    // //! Role of this interface
    // InterfaceRole _role;

    // //! Configuration type of this interface
    // InterfaceConfiguration _configuration;
    

    // // status: inactive, scanning, connected
    

    // QHostAddress  _target;
    // QStringList <name,ip>
    
// master, manual
// write port
// start spy
// start scan
// write target
// inactive -> activate
    
    
};

#endif // NETWORKBLOCK_HPP
