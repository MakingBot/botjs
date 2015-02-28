#ifndef CONTROLLERBLOCK_HPP
#define CONTROLLERBLOCK_HPP
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

#include <BotBlock.hpp>

//!
//! A controller must synchronize data and real component through a communication interface
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class ControllerBlock : public BotBlock
{
	Q_OBJECT

public:



    //! FROM BotBlock
    virtual bool connectionHook(QWeakPointer<BotBlock> weakblock, bool master)
    {
        return true;
    }

protected:



    //! Pointer on the interface used
    // QWeakPointer<ComInterfaceBlock> _interface;

};


#endif // CONTROLLERBLOCK_HPP
