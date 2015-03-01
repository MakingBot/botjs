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

    Q_PROPERTY(quint16 distancemm READ distancemm WRITE setDistancemm MEMBER _distancemm)

public:

    //!
    //! Default constructor
    //!
    explicit DistanceSensorDataBlock(const QString& name = QString("distancesensordata"))
        : SensorDataBlock(name), _distancemm(0)
    {
    	appendBlockIProperty("distancemm", IProperty(IProperty::IPTypeInt, false));
    }

    // ========================================================================
    // => BotBlock redefinition

    //! FROM BotBlock
    virtual float blockVersion() const { return 1.0; }

    //! FROM BotBlock
    virtual QString blockTypeName() const { return QString("distancesensordata"); }

    //! FROM BotBlock
    virtual bool connectionHook(QWeakPointer<BotBlock> weakblock, bool master);

    //! FROM BotBlock
    virtual bool disconnectionHook(QWeakPointer<BotBlock> weakblock, bool master);

    // ========================================================================
    // => Property distance mm

    //!
    //! Distance in mm getter
    //!
    quint16 distancemm()
    {
    	return _distancemm;
    }

    //!
    //! Distance in mm setter
    //!
    void setDistancemm(quint16 dist)
    {
    	_distancemm = dist;
    	emit blockiPropertyValuesChanged();
    }

protected:

    //! Distance in mm
    quint16 _distancemm;

};

#endif // DISTANCESENSORBLOCK_HPP
