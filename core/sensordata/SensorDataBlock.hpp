#ifndef SENSORDATABLOCK_HPP
#define SENSORDATABLOCK_HPP
//!
//! \file SensorDataBlock.hpp
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
//!
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class SensorDataBlock : public BotBlock
{
    Q_OBJECT

public:

    //!
    //! Default constructor
    //!
    explicit SensorDataBlock(const QString& name = QString("mutabledata"))
        : BotBlock(name)
    { }

    //! FROM BotBlock
    virtual BlockRole blockRole() const { return BotBlock::BlockData; }


protected:



};



#endif // SENSORDATABLOCK_HPP
