#ifndef COMINTERFACEBLOCK_HPP
#define COMINTERFACEBLOCK_HPP
//!
//! \file ComInterfaceBlock.hpp
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

#include <QQueue>
#include <BotBlock.hpp>
#include <CtrlMail.hpp>
#include <ComInterfaceThread.hpp>

class ControllerBlock;

//!
//! Convert controller mails into instruction messages for devices.
//! Each device must be registered with the communication interface.
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class ComInterfaceBlock : public BotBlock
{
    Q_OBJECT
    Q_PROPERTY(quint32 frequency READ frequency WRITE setFrequency MEMBER _frequency)

public:
    //!
    //! Default constructor
    //!
    ComInterfaceBlock(const QString& name = QString("cominterface"))
        : BotBlock(name), _enable(false), _counter(0)
        , _thread(new ComInterfaceThread(this))
    {

        setFrequency(2);
    }

    // ========================================================================
    // => BotBlock redefinition

    //! FROM BotBlock
    bool connectionHook(QWeakPointer<BotBlock> weakblock, bool master);

    //! FROM BotBlock
    bool disconnectionHook(QWeakPointer<BotBlock> weakblock, bool master)
    {

        // End
        return BotBlock::disconnectionHook(weakblock, master);
    }


    //!
    //! Status getter
    //!
    const QString& status()
    {
        return _status;
    }

    //!
    //! Status setter
    //!
    void setStatus(const QString& sts)
    {
        _status = sts;

        // emit
    }

    // ========================================================================
    // => Property frequency

    //!
    //! Frequency getter
    //!
    quint32 frequency()
    {
    	return _frequency;
    }

    //!
    //! Define the thread work frequency
    //!
    void setFrequency(quint32 f)
    {
        _frequency = f;
        quint32 msSleepTime = 1000/_frequency;
        _thread->setSyncInterval(msSleepTime);
    }

public slots:

    void registerController(quint16 device, ControllerBlock* block);

	//!
	//! Start the communication interface
	//!
	void start()
	{
		_thread->start(QThread::HighestPriority);
	}

    //!
    //! Perform actions required to synchronize data and device
    //!
    virtual void sync()
    {
        _counter++;
    }

    //!
    //! Check every second if sync function id really called with the good frequency
    //!
    void checkRealTime()
    {
        const int seuil = 1;
        if( _counter < (_frequency-seuil) || (_frequency+seuil) < _counter )
        {
            setStatus("RealTime Error");
        }
        else
        {
            setStatus("RealTime OK");
        }
        // Reset the counter
        _counter = 0;
    }

protected:

    //!
    bool _enable;

    //! Controller status
    QString _status;

    //!
    quint32 _counter;

    //! Refresh frequency in Hz
    //! Number of time by the second the controller is going to wake up to refresh data.
    quint32 _frequency;

    //! Tx queue
    //! Queue of messages that have to be treated
    QQueue<CtrlMail> _fifoTx;

    //! Thread
    QSharedPointer<ComInterfaceThread> _thread;

    //! Pointer on controllers
    //! Each controller is associated to a device id
    QMap<quint16, QWeakPointer<ControllerBlock> > _controllers;

};


#endif // COMINTERFACEBLOCK_HPP
