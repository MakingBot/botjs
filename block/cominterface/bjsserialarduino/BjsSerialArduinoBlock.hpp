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

#include <QSerialPort>
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
    { }

    // ========================================================================
    // => BotBlock redefinition

    //! FROM BotBlock
    virtual float blockVersion() const { return 1.0; }

    //! FROM BotBlock
    virtual BlockRole blockRole() const { return BotBlock::BlockSpy; }

    //! FROM BotBlock
    virtual QString blockTypeName() const { return QString("bjsserialarduino"); }

public slots:

	//!
	//! FROM ComInterfaceBlock
	//!
	virtual void sync()
	{
		// To increment counter that check the real time
		ComInterfaceBlock::sync();

		int numRead = 0;
		char buffer[50];

//
//			while( _serial.bytesAvailable() < 50 )
//			{ }
		numRead  = _serial.read(buffer, 50);

		for(int i=0 ; i<numRead ; i++)
		{
			BLOCK_LOG(buffer[i]);
		}
	}

	//!
	//! Scan serial ports to detect the good serial port
	//!
	void autoconfig()
	{
		// Get every available serial port
		QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();

		bool ok = false;
		QSerialPortInfo info_arduino;

		foreach(const QSerialPortInfo& info, availablePorts)
		{
			if(info.manufacturer().contains("Arduino"))
			{
				ok = true;
				info_arduino = info;
			}
		}

		// Try with the first one
		if(ok)
		{
			BLOCK_LOG("Port arduino found");
			config(info_arduino);
		}
		else
		{
			BLOCK_LOG("Port arduino not found");
		}
	}

	//!
	//! Configuration the interface with the port information
	//!
	void config(QSerialPortInfo port_info)
	{
		// Try to open the port
		_serial.setPortName( port_info.portName() );
		if(!_serial.open(QIODevice::ReadWrite))
		{
			BLOCK_LOG( _serial.errorString() );
			return;
		}

		// Configuration
		_serial.setBaudRate(QSerialPort::Baud115200);
		_serial.setDataBits(QSerialPort::Data8);
		_serial.setParity(QSerialPort::NoParity);
		_serial.setStopBits(QSerialPort::OneStop);
		_serial.setFlowControl(QSerialPort::NoFlowControl);

		// Log
		BLOCK_LOG("Port OK: " << _serial.portName() << " - ( Manufacturer:" << port_info.manufacturer() << ")");
	}

protected:

	//! Serial port
	//! The serial port configuration
	QSerialPort _serial;

};

#endif // BJSSERIALARDUINOBLOCK_HPP
