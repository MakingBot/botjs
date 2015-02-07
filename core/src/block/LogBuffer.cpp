//!
//! \file LogBuffer.cpp
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

#include <LogBuffer.hpp>

#include <BotBlock.hpp>

/* ============================================================================
 *
 * */
LogBuffer::LogBuffer(QObject* parent)
    : QObject(parent), _newLog(true), _state(StateCreated), _coutstream(stdout)
{
    // TODO SegFault because parent is not totaly created when it is accessed here...
    //BotBlock* bparent = qobject_cast<BotBlock*>(parent);
    //_blockchain = bparent->getBlockFathersChain();
}

