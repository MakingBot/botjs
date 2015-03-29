//!
//! \file BotDeviceManager.cpp
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
#include "BotDeviceManager.h"

/* ============================================================================
 *
 */
BotDeviceManager::BotDeviceManager(HardwareSerial& serial)
    : m_deviceNb(0)
    , m_flagNb  (0)
    , m_rxMail  (false), m_newMail(false)
    , m_mailSize(0)    , m_serial(serial)
{
    m_time = 0xFFFFFFFF;
}

/* ============================================================================
 *
 */
byte BotDeviceManager::registerDevice(BotDevice* device)
{
    if(m_deviceNb >= BOTDEVICEMANAGER_MAX_NB_DEVICE)
    {
        return 1;
    }

    m_devices[m_deviceNb] = device;
    m_deviceNb++;
    return 0;
}

/* ============================================================================
 *
 */
byte BotDeviceManager::step()
{
    byte i;
    byte rx;
    byte sts = 0;

    // === Get a mail ===

    if( !m_newMail )
    {
        // Rx Mail Step
        while( m_serial.available() && !m_newMail )
        {
            // read the incoming byte
            rx = m_serial.read();

            // check for a mail start seq
            if(!m_rxMail)
            {
                if( (char)rx == '<' )
                {
                    m_flagNb++;
                    if(m_flagNb >= 2)
                    {
                        m_flagNb = 0;
                        m_rxMail = true;
                    }
                }
                else
                {
                    m_flagNb = 0;
                }
            }
            else
            {
                if( (char)rx == '>' )
                {
                    m_flagNb++;
                    if(m_flagNb >= 2)
                    {
                        m_flagNb = 0;
                        m_newMail= true;
                        m_rxMail = false;
                    }
                }
                else
                {
                    m_mail[m_mailSize] = rx;
                    m_mailSize++;
                    m_flagNb = 0;
                }
            }
        }
    }

    // === Execute mail ===

    else
    {
        if(m_mailSize>=1)
        {
            byte id = m_mail[0];
            if(id < m_deviceNb)
            {
                m_devices[id]->readMail(m_mail+1, m_mailSize-1);
            }
        }
    }

    // === Refresh time ===

    m_elapsed = millis() - m_time;
    if( m_elapsed >= 0 )
    {
        // Refresh time
        m_time += m_elapsed;
        
        // Refresh step
        for(i=0 ; i<m_deviceNb ; i++)
        {
            m_devices[i]->refresh(m_elapsed);
        }
    }
    else
    {
        m_elapsed = 0;
        m_time = millis();
    }

    return sts;
}