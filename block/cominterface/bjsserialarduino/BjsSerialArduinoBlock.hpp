#ifndef BJSSERIALARDUINOBLOCK_HPP
#define BJSSERIALARDUINOBLOCK_HPP
//!
//! \file BjsSerialArduinoBlock.hpp
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

#include <QSerialPortInfo>
#include <ComInterfaceBlock.hpp>

//!
//! Communication interface for custom Arduino configuration
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class BjsSerialArduinoBlock : public ComInterfaceBlock
{
	Q_OBJECT

public:
    //!
    //! Default constructor
    //!
    explicit BjsSerialArduinoBlock(const QString& name = QString("bjsserialarduino"))
        : ComInterfaceBlock(name)
    {



    }

    // ========================================================================
    // => BotBlock redefinition

    //! FROM BotBlock
    virtual float blockVersion() const { return 1.0; }

    //! FROM BotBlock
    virtual BlockRole blockRole() const { return BotBlock::BlockSpy; }

    //! FROM BotBlock
    virtual QString blockTypeName() const { return QString("bjsserialarduino"); }


public slots:

	void doli()
	{
		BLOCK_LOG( "dodldododo" );

		QList<QSerialPortInfo> list = QSerialPortInfo::availablePorts();

		foreach(QSerialPortInfo info, list)
		{
			BLOCK_LOG( info.portName() );
		}
	}


protected:

//    QString _serialPort;

//    QSerialPortInfo  QList<QSerialPortInfo>  availablePorts()

};

#endif // BJSSERIALARDUINOBLOCK_HPP
