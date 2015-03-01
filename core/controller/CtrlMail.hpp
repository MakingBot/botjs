#ifndef CTRLMAIL_HPP
#define CTRLMAIL_HPP
//!
//! \file ControllerBlock.hpp
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
#include <QByteArray>

//!
//! Message to communicate between controllers and communication interface
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class CtrlMail
{

public:

    enum MsgModeFlag : quint8 { Read = 0x00, Write = 0x01 };

    //! Device id
    quint16 device;

    //! Property id
    quint8  propid;

    //! Mode
    MsgModeFlag mode;

    //! 4 bytes value
    QByteArray value;

};

#endif // 
