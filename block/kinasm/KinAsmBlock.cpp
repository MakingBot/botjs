//!
//! \file KinAsmBlock.cpp
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

#include <KinAsmBlock.hpp>

/* ============================================================================
 *
 * */
EXPORT_BLOCK(KinAsmBlock)



/* ============================================================================
 *
 * */
BotBlock* KinAsmBlock::create(const QString& btypename, const QString& varname)
{
	BotBlock* block = BotBlock::create(btypename, varname);

	//
	if( btypename.compare("joint") != 0 )
	{
		return block;
	}

	// Set the body as a son
	QSharedPointer<JointBlock> joint = block->toSpecializedSharedPointer<JointBlock>();
	if(!_root)
	{
		beglog() << "Create joint block #" << block->blockName() << "# and set it as base" << endlog();

		setRootSharedPtr(joint);
	}

	// return
	return block;
}

/* ============================================================================
 *
 * */
void KinAsmBlock::updatePhysicSlaves()
{
    // Clear old list
    _physicSlaves.clear();

    if( _root )
    {
        // Cast and append
        _physicSlaves << qSharedPointerObjectCast<PhysicBlock, JointBlock> ( _root );
    }

    // Log
    beglog() << "Physic slaves list updated " << _physicSlaves.size() << " elements" << endlog();
}

