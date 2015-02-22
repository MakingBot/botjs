//!
//! \file RobotBlock.cpp
//!
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

#include <RobotBlock.hpp>

/* ============================================================================
 *
 * */
EXPORT_BLOCK(RobotBlock)

/* ============================================================================
 *
 * */
void RobotBlock::selectBlockSons(QList<QSharedPointer<BotBlock> >& sons, const QStringList& types)
{
	BotBlock::selectBlockSons(sons, types);

	if(_base)
	{
		if( types.indexOf( _base->getBlockTypeName() ) != -1 )
		{
			sons << _base->getBlockSharedFromThis();
			std::cout << "plus one" << std::endl;
		}
	}

	foreach(QSharedPointer<KinAsmBlock> body, _bodies)
	{
		if( types.indexOf( body->getBlockTypeName() ) != -1 )
		{
			sons << body->getBlockSharedFromThis();
		}
	}
}

/* ============================================================================
 *
 * */
bool RobotBlock::connect(BotBlock* block, bool master)
{
    return BotBlock::connect(block, master);
    return true;
}

/* ============================================================================
 *
 * */
BotBlock* RobotBlock::create(const QString& btypename, const QString& varname)
{
	// If it is not a kin assembly creation follow the standard creation
	if( btypename.compare("kinasm") != 0 )
	{
		return BotBlock::create(btypename, varname);
	}

    // Check if the name already exist
    if(BotBlock::JsEngine.go().property(varname).toVariant().isValid())
    {
        beglog() << "Create block #" << btypename << "# failure: this name is already used" << endlog();
        return 0;
    }

    // Create block from the JsEngine
    QSharedPointer<BotBlock> block = BotBlock::JsEngine.createBlock(btypename, varname);

    // Set this as the block parent
    block->setBlockFather(this);

    // Set the body as a son
    QSharedPointer<KinAsmBlock> son = block->toSpecializedSharedPointer<KinAsmBlock>();
    if(!_base)
    {
    	_base = son;
    	beglog() << "Create kinasm block #" << block->getBlockName() << "# and set it as base" << endlog();
    }
    else
    {
    	_bodies << son;
    	beglog() << "Create kinasm block #" << block->getBlockName() << "# and append it as bodies" << endlog();
    }

    // return
    return block.data();
}
