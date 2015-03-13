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

    Q_PROPERTY(quint32 distance READ distance WRITE setDistance)

public:

    //! Id of the visible property
    static const quint8 IdPropertyDistance;

    //!
    //! Default constructor
    //!
    explicit DistanceSensorDataBlock(const QString& name = QString("distancesensor"))
        : SensorDataBlock(name), _distance(0)
    {
        defineBlockIProperty(IdPropertyDistance, new IProperty("distance", IProperty::IPTypeInt, false));
    }

    // ========================================================================
    // => BotBlock redefinition

    //! FROM BotBlock
    virtual float blockVersion() const { return 1.0; }

    //! FROM BotBlock
    virtual QString blockTypeName() const { return QString("distancesensor"); }

    //! FROM BotBlock
    virtual bool connectionHook(QWeakPointer<BotBlock> weakblock, bool master);

    //! FROM BotBlock
    virtual bool disconnectionHook(QWeakPointer<BotBlock> weakblock, bool master);

    // ========================================================================
    // => Property distance

    //!
    //! Distance in mm getter
    //!
    quint32 distance()
    {
        QReadLocker locker(&_distanceLock);
    	return _distance;
    }

    //!
    //! Distance in mm setter
    //!
    void setDistance(quint32 dist)
    {
        _distanceLock.lockForWrite();
        _distance = dist;
        _distanceLock.unlock();
    	
    	//emit blockiPropertyValuesChanged();
    }

protected:

    //! Distance
    //! Distance measured by the sensor in mm
    quint32 _distance;
    
    //! Lock
    //! Smart mutex for distance property
    QReadWriteLock _distanceLock;

};

#endif // DISTANCESENSORBLOCK_HPP
