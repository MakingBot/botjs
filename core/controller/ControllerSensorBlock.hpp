#ifndef CONTROLLERSENSORBLOCK_HPP
#define CONTROLLERSENSORBLOCK_HPP
//!
//! \file ControllerSensorBlock.hpp
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

#include <ControllerBlock.hpp>
//#include <SensorDataBlock.hpp>

//!
//!
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class ControllerSensorBlock : public ControllerBlock
{
    Q_OBJECT

public:

    //!
    //! Default constructor
    //!
    explicit ControllerSensorBlock(const QString& name = QString("controllersensor"))
        : ControllerBlock(name)
    { }

    // ========================================================================
    // => BotBlock redefinition

//    //! FROM BotBlock
//    virtual BlockRole blockRole() const { return BotBlock::BlockController; }

//    //!
//    //! Hook on the connection process
//    //!
//    virtual bool connectionHook(QWeakPointer<BotBlock> weakblock, bool master)
//    {
//
//
//        // End
//        return ControllerBlock::connectionHook(weakblock, master);
//    }
//
//    //!
//    //! Hook on the disconnection process
//    //!
//    virtual bool disconnectionHook(QWeakPointer<BotBlock> weakblock, bool master)
//    {
//
//        return true;
//    }

    // ========================================================================
    // => Block data initialization

//    //!
//    //!
//    //!
//    virtual void iniSensorData()
//    { }
//
//    //!
//    //!
//    //!
//    virtual void clearSensorData()
//    { }

protected:

    //! Data sensor connection
//    QWeakPointer<SensorDataBlock> _datasensor;

};

#endif // CONTROLLERSENSORBLOCK_HPP
