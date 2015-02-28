//!
//! \file ComInterfaceThread.cpp
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

#include <ComInterfaceThread.hpp>
#include <QObject>
#include <iostream>
#include <stdexcept>
#include <exception>
#include <ComInterfaceBlock.hpp>

/* ============================================================================
 *
 * */
ComInterfaceThread::ComInterfaceThread(ComInterfaceBlock* block, QObject* parent)
    : QThread(parent), _block(block)
{
    if(!_block)
    {
        throw std::runtime_error("Parent block is null");
    }

    // Real time checker timer
    _rtTimer = QSharedPointer<QTimer>( new QTimer() );
    _rtTimer->moveToThread(this);
    _rtTimer->setInterval(1000);
    connect( _rtTimer.data(), SIGNAL(timeout()), _block, SLOT(checkRealTime()), Qt::QueuedConnection );

    // Sync timer
    _syncTimer = QSharedPointer<QTimer>( new QTimer() );
    _syncTimer->moveToThread(this);
    _syncTimer->setInterval(1000);
    connect( _syncTimer.data(), SIGNAL(timeout()), _block, SLOT(sync()), Qt::DirectConnection );
}

/* ============================================================================
 *
 * */
void ComInterfaceThread::run()
{
    _rtTimer->start();
    _syncTimer->start();
    exec();
}

