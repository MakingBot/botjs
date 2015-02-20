//!
//! \file Viewer3DBlock.cpp
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

#include <Viewer3DBlock.hpp>

/* ============================================================================
 *
 * */
EXPORT_BLOCK(Viewer3DBlock)

/* ============================================================================
 *
 * */
Viewer3DBlock::Viewer3DBlock(const QString& name, QObject *parent)
    : GuiBlock(name, parent), _bgColor(240,240,240)
{
    // MODEL
    // QMap<QString, int> model_enum;
    // model_enum["Base"     ] = PhysicBlock::ModelTypeBase     ;
    // model_enum["Kinematic"] = PhysicBlock::ModelTypeKinematic;
    // appendBlockIProperty("model" , IProperty(IProperty::IPTypeEnum, true, model_enum));

    // VBO Used Size
    // appendBlockIProperty("vboUsedSize"        , IProperty(IProperty::IPTypeInt , false));
    
    // // 
    // appendBlockIProperty("nbOfRenderedObject" , IProperty(IProperty::IPTypeInt , false));

    // Widget creation
    _widget = qSharedPointerObjectCast<QWidget, Viewer>( QSharedPointer<Viewer>(new Viewer(this)) );
}




/* ============================================================================
 *
 * */
bool Viewer3DBlock::connect(BotBlock* block, bool master)
{
    // Basic checks
    if(!block)        { beglog() << "Connection to null block failure" << endlog(); return false; }
    if(block == this) { beglog() << "Connection to itself refused"     << endlog(); return false; }

    // Check if the block is a physic object block
    PhysicBlock* physic_object = qobject_cast<PhysicBlock*>(block);
    if(!physic_object)
    {
        return BotBlock::connect(block, master);
    }

    // Else it is a physic object block
    // if this ask for the connection
    if(master)
    {
        /*
        // Ask for connection return
        if( ! block->connect(this, false) )
        {
            // If the other block rejected the connection and log it
            beglog() << "Connection to the link #" << block->getBlockFathersChain() << "# failure: connection return refused" << endlog();
            return false;
        }

        // Set
        QSharedPointer<PhysicBlock> shared_physic_object = qSharedPointerObjectCast<PhysicBlock, BotBlock>( block->getBlockSharedFromThis() );        
        _object = shared_physic_object.toWeakRef();

        // Log
        beglog() << "Connection to the joint #" << block->getBlockFathersChain() << "#" << endlog();

        // Alert BotJs
        emit blockfPropertyValuesChanged();
        return true;
        */
    }
    else
    {

        // // Create the shared pointer
        // QSharedPointer<RobotBlock> shared_physic_object = qSharedPointerObjectCast<RobotBlock, BotBlock>( block->getBlockSharedFromThis() );
        
        // // Set the new output joint
        // _robot = shared_physic_object.toWeakRef();




        // // Log
        // beglog() << "Connection from the joint #" << block->getBlockFathersChain() << "# accepted" << endlog();

        // // Alert BotJs
        // emit blockfPropertyValuesChanged();
        // return true;

    }

}

/* ============================================================================
 *
 * */
void Viewer3DBlock::disconnect(BotBlock* block, bool master)
{
    // TODO
    BotBlock::disconnect(block, master);
}

/* ============================================================================
 *
 * */
void Viewer3DBlock::disconnectAll()
{
    // TODO
    BotBlock::disconnectAll();
}
