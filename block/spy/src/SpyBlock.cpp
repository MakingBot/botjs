//!
//! \file SpyBlock.cpp
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

#include <SpyBlock.hpp>

/* ============================================================================
 *
 * */
EXPORT_BLOCK(SpyBlock)

/* ============================================================================
 *
 * */
SpyBlock::SpyBlock(const QString& name, QObject *parent)
    : BotBlock(name, parent)
{
    appendBlockIProperty("visible", IProperty(IProperty::IPTypeBool, true));
}

/* ============================================================================
 *
 * */
bool SpyBlock::connect(BotBlock* block, bool master)
{
    // Basic checks
    if(!block)        { beglog() << "Connection to null block failure" << endlog(); return false; }
    if(block == this) { beglog() << "Connection to itself refused"     << endlog(); return false; }


    // This block ask for a connection
    if(master)
    {
        // Ask for connection back
        if(! block->connect(this, false))
        {
            // Log and return
            beglog() << "Connection to " << block->getBlockFathersChain() << " failure: connection return refused" << endlog();
            return false;
        }

        // TODO Disconnect old
        if(_spiedBlock)
        {

        }

        // Check widget creation
        createWidgetIfRequired();

        // Track the new spied block
        _spiedBlock = block->getBlockWeakFromThis();

        // Alert the view
        emit spiedBlockChanged();

        // Log and return
        beglog() << "Connection to #" << block->getBlockFathersChain() << "#" << endlog();
        return true;
    }
    // Other block ask for a connection
    else
    {
        // If an other spy ask for a connection accept it
        SpyBlock* spy = qobject_cast<SpyBlock*>(block);
        if(spy)
        {
            // Use main connect function
            return BotBlock::connect(block, master);            
        }

        // Log and return
        beglog() << "Connection from #" << block->getBlockFathersChain() << "# refused: it is not a spy block" << endlog();
        return false;
    }
}

/* ============================================================================
 *
 * */
bool SpyBlock::disconnectAll()
{
    // Clear connection
    _spiedBlock.clear();

    // Log
    beglog() << "Remove all connection" << endlog();

    // Alert the view
    emit spiedBlockChanged();
}

/* ============================================================================
 *
 * */
void SpyBlock::blockInit(QSharedPointer<BotEngine> js_engine)
{
    BotBlock::blockInit(js_engine);
}
