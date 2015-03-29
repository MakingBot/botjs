#ifndef HCSR04DEVICE_HPP
#define HCSR04DEVICE_HPP
//!
//! \file HcSr04Device.h
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
#include <NewPing.h>
#include <BotDevice.h>

//! \brief Id of the distance property
//!
#define HCSR04DEVICE_ID_PROPERTY_DISTANCE 0

//! \class HcSr04Device
//! \brief Global interface for BotJs device on arduino
//!
class HcSr04Device : public BotDevice, public NewPing
{

public:

    //! \brief Default constructor
    //!
    HcSr04Device(byte id, HardwareSerial& serial, byte trigger_pin, byte echo_pin, byte max_distance);


    //! \brief FROM BotDevice
    //!
    virtual void readMail(byte* mail, byte size);

protected:

    //! \brief FROM BotDevice
    //!
    virtual void action();

};

#endif // HCSR04DEVICE_HPP
