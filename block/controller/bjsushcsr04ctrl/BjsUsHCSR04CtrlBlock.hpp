#ifndef BJSUSHCSR04CTRLBLOCK_HPP
#define BJSUSHCSR04CTRLBLOCK_HPP
//!
//! \file BjsUsHCSR04CtrlBlock.hpp
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

#include <CtrlMail.hpp>
#include <QMetaProperty>
#include <ControllerSensorBlock.hpp>

//!
//!
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class BjsUsHCSR04CtrlBlock : public ControllerSensorBlock
{
    Q_OBJECT

public:

    //!
    //! Default constructor
    //!
    explicit BjsUsHCSR04CtrlBlock(const QString& name = QString("bjsushcsr04ctrl"))
        : ControllerSensorBlock(name)
    { }

    // ========================================================================
    // => BotBlock redefinition

    //! FROM BotBlock
    virtual float blockVersion() const { return 1.0; }

    //! FROM BotBlock
    virtual BlockRole blockRole() const { return BotBlock::BlockController; }

    //! FROM BotBlock
    virtual QString blockTypeName() const { return QString("bjsushcsr04ctrl"); }

    // ========================================================================
    // => ControllerBlock redefinition

    //! FROM ControllerBlock
    virtual void newMail(CtrlMail& mail)
    {
    	_datasensor.toStrongRef()->setBlockIPropertyValue(mail.propid, mail.valueToQuint16());
    }

    // ========================================================================
    // => ControllerSensorBlock redefinition

    //! FROM ControllerSensorBlock
    virtual bool checkDataProperties(QWeakPointer<SensorDataBlock> data)
    {
    	QSharedPointer<SensorDataBlock> sdata = data.toStrongRef();
    	if( sdata->metaObject()->property(sdata->metaObject()->indexOfProperty("distancemm")).isValid() )
    	{
    		return true;
    	}
    	return false;
    }

protected:


};

#endif // BJSUSHCSR04CTRLBLOCK_HPP
