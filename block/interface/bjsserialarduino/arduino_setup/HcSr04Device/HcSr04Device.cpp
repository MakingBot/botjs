//!
//! \file HcSr04Device.cpp
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
#include "HcSr04Device.h"

/* ============================================================================
 *
 */
HcSr04Device::HcSr04Device(byte id, HardwareSerial& serial, byte trigger_pin, byte echo_pin, byte max_distance)
    : BotDevice(id, serial), NewPing(trigger_pin, echo_pin, max_distance)
{ }

/* ============================================================================
 *
 */
void HcSr04Device::readMail(byte* mail, byte size)
{

}


/* ============================================================================
 *
 */
void HcSr04Device::action()
{

    // Get the distance value and send it
    word us_ping = (ping()/US_ROUNDTRIP_CM)*10;
    sendMail(HCSR04DEVICE_ID_PROPERTY_DISTANCE, us_ping);

}

