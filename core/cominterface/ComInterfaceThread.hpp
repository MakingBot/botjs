#ifndef COMINTERFACETHREAD_HPP
#define COMINTERFACETHREAD_HPP
//!
//! \file ComInterfaceThread.hpp
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

#include <QTimer>
#include <QThread>
#include <QSharedPointer>

class ComInterfaceBlock;

//!
//! The thread that manage the communication interface
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class ComInterfaceThread : public QThread
{
	Q_OBJECT

public:
	//!
	//! Default constructor
	//!
    ComInterfaceThread(ComInterfaceBlock* block, QObject* parent = 0);

    //!
    //! Synchronization interval setter
    //!
    void setSyncInterval(quint32 msTime)
    {
        _syncTimer->setInterval(msTime);
    }

public slots:


protected:

    //! Parent block pointer
    ComInterfaceBlock* _block;

    //! Real time timer
    QSharedPointer<QTimer> _rtTimer;

    //! Synchronization action timer
    QSharedPointer<QTimer> _syncTimer;

    //! FROM QThread
    void run();

};

#endif // COMINTERFACETHREAD_HPP
