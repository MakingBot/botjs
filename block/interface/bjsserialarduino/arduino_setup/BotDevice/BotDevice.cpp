//!
//! \file BotDevice.cpp
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
#include "BotDevice.h"



/* ============================================================================
 *
 */
BotDevice::BotDevice(byte id, HardwareSerial& serial)
    : m_id(id), m_serial(serial)
{ }

/* ============================================================================
 *
 */
void BotDevice::refresh(word elapsed)
{
    m_refreshTimer += elapsed;
    if(m_refreshTimer >= m_refreshDelay)
    {
        action();
        m_refreshTimer = 0;
    }
}

/* ============================================================================
 *
 */
void BotDevice::readMail(byte* mail, byte size)
{

}

/* ============================================================================
 *
 */
void BotDevice::sendMailBeg()
{
    m_serial.write("<<", 2);
    m_serial.write(m_id);
}

/* ============================================================================
 *
 */
void BotDevice::sendMailEnd()
{
    m_serial.write(">>", 2);
}

/* ============================================================================
 *
 */
void BotDevice::sendMail(byte id_property, byte data)
{
    sendMailBeg();
    m_serial.write(id_property);
    m_serial.write(data);
    sendMailEnd();
}

/* ============================================================================
 *
 */
void BotDevice::sendMail(byte id_property, word data)
{
    int i;
    sendMailBeg();
    m_serial.write(id_property);
    for(i=0 ; i<sizeof(word) ; i++)
    {
        const int shift = (i*8);
        word cast = ( data & (0xFF<<shift) ) >> shift; 
        m_serial.write(byte(cast));
    }
    sendMailEnd();
}

/* ============================================================================
 *
 */
void BotDevice::sendMail(byte id_property, long data)
{
    int i;
    sendMailBeg();
    m_serial.write(id_property);
    for(i=0 ; i<sizeof(long) ; i++)
    {
        const int shift = (i*8);
        long cast = ( data & (0xFF<<shift) ) >> shift; 
        m_serial.write(byte(cast));
    }
    sendMailEnd();
}
