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

#include <QThread>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QHostAddress>
#include <BotBlock.hpp>

//!
//! Block that provides a communication interface for Network using IP on UDP/TCP
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class NetworkBlock : public BotBlock
{
    Q_OBJECT

    Q_PROPERTY(bool     activated   READ isActivated WRITE setActivated)
    Q_PROPERTY(quint16  port        READ port        WRITE setPort     )
    Q_PROPERTY(QString  address     READ address     WRITE setAddress  )

public:

    //!
    //! Define the possible message type
    //!
    enum NetMsgType : quint16
    {
        NET_PING                    = 10 ,
        NET_PING_ACK                = 11 ,

        NET_TEST                    = 20 ,

        NET_BLOCK_CREATE            = 30 ,
        NET_BLOCK_UPDATE            = 31 ,
        NET_BLOCK_CONNECT           = 32 ,
        NET_BLOCK_DISCONNECT        = 33 ,
        NET_BLOCK_DESTROY           = 34 
    };

    //!
    //! Default constructor
    //!
    explicit NetworkBlock(const QString& name = QString("network"));

    // ========================================================================
    // => BotBlock redefinition

    //! FROM BotBlock
    virtual float blockVersion() const { return 1.0; }

    //! FROM BotBlock
    virtual BlockRole blockRole() const { return BotBlock::BlockInterface; }

    //! FROM BotBlock
    virtual QString blockTypeName() const { return QString("network"); }

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
    quint16 port() const
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

    //!
    //! Address getter
    //!
    QString address() const
    { 
        return _address.toString();
    }

    //!
    //! Address setter
    //!
    void setAddress(const QString& addr)
    {
        _address.setAddress(addr);
    }

    // ========================================================================
    // => Network rx actions

    //!
    //! Trig the actions associated to the incoming message
    //!
    void dispatch(const QHostAddress& sender, const QByteArray& datagram);
    
    //!
    //! Called when a ping message is received
    //!
    void onRxPing(const QHostAddress& sender);
    
    //!
    //! Called when a ping ack message is received
    //!
    void onRxPingAck(const QHostAddress& sender, QDataStream& stream);

    //!
    //! Called when a test message is received
    //!
    void onRxTest(const QByteArray& datagram);

    // ========================================================================
    // => Network tx actions

    //!
    //! In response to a ping message
    //! This function can be called only in bot cfg
    //!
    void pingAck(const QHostAddress& sender);

public slots:

    //!
    //! Function that process incoming udp datagrams
    //!
    void processPendingUdpDatagrams();

    //!
    //! To scan the network
    //! Search for an other BotJs in bot cfg
    //! This function can be called only in dev cfg
    //!
    void ping();

protected:

    // ========================================================================
    // => Network activation

    //! Activated ?
    //! Activation status, True if the interface is activated
    bool _isActivated;

    //! Is Connected ?
    //! Connection status, True if this core is connected to a distant one
    bool _isConnected;
    
    //! Thread
    //! Independant thread to support the communication
    QThread _thread;

    // ========================================================================
    // => Network information

    //! Port
    //! Used port for the udp/tcp interface
    quint16  _port;

    //! Host address
    //! Address of the target robot
    QHostAddress _address;

    //! Bad messages
    //! Number of no-readble message received
    quint32 _badMsgReceived;

    // ========================================================================
    // => Network socket

    //! UDP Socket
    QSharedPointer<QUdpSocket> _udpSocket;

    //! Tcp Socket
    QSharedPointer<QTcpSocket> _tcpSocket;

    // ========================================================================
    // => Network ping and test variables
    
    //! Test Timer
    //! To measure the time between the test message emission and the reception
    QTime _testTimer;

    //! Test Number 
    //! Number of test messages sent to the distant core 
    quint16 _testNumber;

    //! Distant core
    //! Cores that have answer the ping message
    QMap<QString, QHostAddress> _distantCore;

    // ========================================================================
    // => Utile functions

    //!
    //! Provide the core cfg
    //!
    inline CoreCfg coreCfg()
    {
        return BotBlock::CoreConfiguration();
    }
    
    //!
    //! Provide the core cfg
    //!
    inline QString coreTag()
    {
        return BotBlock::CoreTag();
    }
    
};

#endif // NETWORKBLOCK_HPP
