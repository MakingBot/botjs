#ifndef BOTDEVICE_HPP
#define BOTDEVICE_HPP
//!
//! \file BotDevice.h
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

#include "Arduino.h"

//! \class BotDevice
//! \brief Global interface for BotJs device on arduino
//!
class BotDevice
{

public:

    //! \brief Default constructor
    //!
    BotDevice(byte id, HardwareSerial& serial);

    //! \brief Cyclic function that check if the device has to be refreshed
    //! \note This function is called by the device manager
    //!
    void refresh(word elapsed);

    //! \brief To read a mail for the device
    //! Mail received by device are formated as follow:
    //! '<' + '<' + device_id + property_id + w/r + data + '>' + '>'
    //!
    virtual void readMail(byte* mail, byte size);

protected:

    //! \brief Send mail start seq
    //! Mail sent by device are formated as follow:
    //! '<' + '<' + device_id + property_id + data + '>' + '>'
    //!
    void sendMailBeg();

    //! \brief Send mail stop seq
    //!
    void sendMailEnd();

    //! \brief Send mail with a byte size data
    //!
    void sendMail(byte id_property, byte data);

    //! \brief Send mail with a word size data
    //!
    void sendMail(byte id_property, word data);

    //! \brief Send mail with a long size data
    //!
    void sendMail(byte id_property, long data);

    //! \brief Cyclic action to perform
    //!
    virtual void action() = 0;

    //! \brief Device Id
    //! Each bot device must have a unique ID
    //!
    byte m_id;

    //! \brief Serial used to send mails
    //!
    HardwareSerial& m_serial;

    //! \brief 
    //!
    word m_refreshTimer;

    //! \brief 
    //!
    word m_refreshDelay;

};


#endif // BOTDEVICE_HPP
