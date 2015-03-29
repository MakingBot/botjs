#ifndef BOTDEVICEMANAGER_HPP
#define BOTDEVICEMANAGER_HPP
//!
//! \file BotDeviceManager.h
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
#include <BotDevice.h>

//! \brief Number max of device that can be managed
//!
#define BOTDEVICEMANAGER_MAX_NB_DEVICE 20

//! \brief Number max of byte in a mail
//!
#define BOTDEVICEMANAGER_MAX_MAIL_SIZE 256


//! \class BotDeviceManager
//! \brief Manage a list of device
//!
class BotDeviceManager
{

public:

    //! \brief Default constructor
    //!
    BotDeviceManager(HardwareSerial& serial);

    //! \brief Append a managed device
    //!
    byte registerDevice(BotDevice* device);

    //! \brief Loop step
    //! This function perform device cyclic actions.
    //! It must be called in arduino loop function.
    //!
    byte step();

private:

    //! \brief Number of device managed
    //!
    byte m_deviceNb;

    //! \brief Store devices used by the application
    //!
    BotDevice* m_devices[BOTDEVICEMANAGER_MAX_NB_DEVICE];

    //! \brief To count the number of flag received < or >
    //!
    byte m_flagNb;

    //! \brief true if the mail start seq has been received
    //!
    boolean m_rxMail;

    //! \brief true if a new mail is has been received
    //!
    boolean m_newMail;

    //! \brief Size of the new mail
    //!
    byte m_mailSize;

    //! \brief buffer to store the new mail
    //!
    byte m_mail[BOTDEVICEMANAGER_MAX_MAIL_SIZE];

    //! \brief Serial used to received mails
    //!
    HardwareSerial& m_serial;

    //! \brief Elasped time since the last loop step
    //!
    word m_elapsed;

    //! \brief Time mesured the last loop step
    //!
    unsigned long m_time;

};

#endif // BOTDEVICEMANAGER_HPP
