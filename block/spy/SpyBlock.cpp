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
SpyBlock::SpyBlock(const QString& name)
    : GuiBlock(name)
{
    // Create the spy widget
    _widget = qSharedPointerObjectCast<QWidget, SpyWidget>( QSharedPointer<SpyWidget>( new SpyWidget(this) ) );
}

/* ============================================================================
 *
 * */
bool SpyBlock::connectionHook(QWeakPointer<BotBlock> weakblock, bool master)
{
	// get a strong reference
	QSharedPointer<BotBlock> block = weakblock.toStrongRef();

	// This block ask for a connection
	if(master)
	{
		// Disconnect old
		if(_spiedBlock)
		{
			this->dco(_spiedBlock.data());
		}

		// Track the new spied block
		_spiedBlock = block->toBlockWeakPointer();

		// Alert the view
		emit spiedBlockChanged();
	}
	// Other block ask for a connection
	else
	{
		// If an other spy ask for a connection accept it
		QSharedPointer<SpyBlock> spy = qSharedPointerObjectCast<SpyBlock, BotBlock>(block);
		if(!spy)
		{
			BLOCK_LOG("Connection from #" << block->blockIdChain() << "# refused: it is not a spy block");
			return false;
		}
	}

	// End
	return BotBlock::connectionHook(weakblock, master);
}

/* ============================================================================
 *
 * */
bool SpyBlock::disconnectionHook(QWeakPointer<BotBlock> weakblock, bool master)
{

	// End
	return BotBlock::disconnectionHook(weakblock, master);
}




// }

/* ============================================================================
 *
 * */
// void SpyBlock::disconnect(BotBlock* block, bool master)
// {
//     // Basic checks
//     if(!block)        { beglog() << "Disconnection from null block failure" << endlog(); return ; }
//     if(block == this) { beglog() << "Disconnection from itself refused"     << endlog(); return ; }
    
//     if( _spiedBlock.data() == block )
//     {
//         if(master)
//         {
//             block->disconnect(this, false); 
//         }
//         _spiedBlock.clear();
//     }
//     else 
//     {
//         BotBlock::disconnect(block, master);
//     }

//     // Log
//     beglog() << "Disconnection from #" << block->getBlockFathersChain() << "#" << endlog();
// }

/* ============================================================================
 *
 * */
// void SpyBlock::disconnectAll()
// {
//     // Disconnect from spied
//     this->disconnect(_spiedBlock.data());

//     // Log
//     beglog() << "All connections has been removed" << endlog();

//     // Alert the view
//     emit spiedBlockChanged();
// }
