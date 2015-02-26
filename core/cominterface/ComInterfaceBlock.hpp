#ifndef BOTBLOCK_HPP
#define BOTBLOCK_HPP
//!
//! \file ComInterfaceBlock.hpp
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

#include <BotBlock.hpp>

//!
//! Convert controller mails into instruction messages for devices.
//! Each device must be registered with the communication interface.
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class ComInterfaceBlock : public BotBlock
{

public:

    //!
    //! Perform actions required to synchronize data and device
    //!
    virtual void doWork()
    { }


protected:

    //! Controller status
    QString _status;

    //! Refresh frequence in Hz
    //! Number of time by the second the controller is going to wake up to refresh data.
    quint32 _frequence;

    //! Tx Fifo
    //! Fifo of message that have to be treated
    QQueue<CtrlMail> _fifoTx;

    //! Pointer on controllers
    //! Each controller is associated to a device id
    QMap<quint16, QWeakPointer<ControllerBlock> > _controllers;

};



