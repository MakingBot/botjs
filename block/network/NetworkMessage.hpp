#ifndef NETWORKMESSAGE_HPP
#define NETWORKMESSAGE_HPP
//!
//! \file NetworkMessage.hpp
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

#include <QtGlobal>
#include <QDataStream>

//!
//! This class define a network message
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class NetworkMessage
{

public:

    //!
    //! Define the possible message type
    //!
    enum NetMsgType : quint16
    {
        NET_PING      = 10          // Ping for scanning purpose

    };

    //!
    //! Constructor for a sending message
    //!
    NetworkMessage(NetMsgType type)
        : _type(type)
    {
        updateDatagram();
    }

    //!
    //! Constructor for a incoming message
    //!
    NetworkMessage(QByteArray datagram)
        : _datagram(datagram)
    {
        decryptDatagram();
    }

    //!
    //! Type getter
    //!
    NetMsgType type()
    {
        return _type;
    }

    //!
    //! Datagram getter
    //!
    QByteArray datagram()
    {
        return _datagram;
    }

    //!
    //! Datagram updater
    //!
    void updateDatagram()
    {
        // Clear the data
        _datagram.clear();

        // Create a stream to fill it
        QDataStream stream( &_datagram, QIODevice::WriteOnly );

        // Append the type
        stream << (quint16)_type;
    }

    //!
    //! Datagram updater
    //!
    void decryptDatagram()
    {
        // Create a stream to fill it
        QDataStream stream( _datagram );

        // Get the type
        quint16 type;
        stream >> type;
        _type = (NetMsgType)type;
    }

protected:

    //! Type
    //! Message type
    NetMsgType _type;

    //! Datagram
    //! Message datagram
    QByteArray _datagram;

};

#endif // NETWORKMESSAGE_HPP
