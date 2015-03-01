#ifndef DISTANCESENSORBLOCK_HPP
#define DISTANCESENSORBLOCK_HPP
//!
//! \file DistanceSensorDataBlock.hpp
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

#include <SensorDataBlock.hpp>

//!
//!
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class DistanceSensorDataBlock : public SensorDataBlock
{
    Q_OBJECT

public:

    //!
    //! Default constructor
    //!
    explicit DistanceSensorDataBlock(const QString& name = QString("distancesensordata"))
        : SensorDataBlock(name)
    { }

    // ========================================================================
    // => BotBlock redefinition

    //! FROM BotBlock
    virtual float blockVersion() const { return 1.0; }

    //! FROM BotBlock
    virtual QString blockTypeName() const { return QString("distancesensordata"); }



};

#endif // DISTANCESENSORBLOCK_HPP