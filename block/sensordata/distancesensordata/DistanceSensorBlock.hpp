#ifndef DISTANCESENSORBLOCK_HPP
#define DISTANCESENSORBLOCK_HPP
//!
//! \file DistanceSensorBlock.hpp
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

//! \class DistanceSensorBlock
//! \brief Provides data for sensor that get a distance
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class DistanceSensorBlock : public SensorDataBlock
{
    Q_OBJECT

    //! \brief Distance property
    //!
    Q_PROPERTY(quint32 distance READ distance WRITE setDistance)

public:

    //! \brief Distance property id
    //!
    static const quint8 IdPropertyDistance;

    //! \brief Default constructor
    //!
    explicit DistanceSensorDataBlock(const QString& name = QString("distancesensor"))
        : SensorDataBlock(name), _distance(0)
    {
        defineBlockIProperty(IdPropertyDistance, new IProperty("distance", IProperty::IPTypeInt, false));
    }

    // ========================================================================
    // => BotBlock redefinition

    //! \brief FROM BotBlock
    //!
    virtual float blockVersion() const { return 1.0; }

    //! \brief FROM BotBlock
    //!
    virtual QString blockTypeName() const { return QString("distancesensor"); }

    //! \brief FROM BotBlock
    //!
    virtual bool connectionHook(QWeakPointer<BotBlock> weakblock, bool master);

    //! \brief FROM BotBlock
    //!
    virtual bool disconnectionHook(QWeakPointer<BotBlock> weakblock, bool master);

    // ========================================================================
    // => Member distance

    //! \brief Distance member getter
    //!
    quint32 distance();

    //! \brief Distance member setter
    //!
    void setDistance(quint32 dist);

protected:

    //! \brief Distance member
    //!
    //! Distance measured by the sensor. Unit is the mm.
    //!
    quint32 m_distance;
    
    //! \brief Distance lock
    //!
    //! Smart mutex for distance.
    //!
    QReadWriteLock m_distanceLock;

};

/* ============================================================================
 *
 * */
inline quint32 DistanceSensorBlock::distance()
{
    QReadLocker locker(&m_distanceLock);
	return m_distance;
}

/* ============================================================================
 *
 * */
inline void DistanceSensorBlock::setDistance(quint32 distance)
{
    m_distanceLock.lockForWrite();
    m_distance = distance;
    m_distanceLock.unlock();
	
	//emit blockiPropertyValuesChanged();
}

#endif // DISTANCESENSORBLOCK_HPP
