//!
//! \file JointBlock.cpp
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

#include <JointBlock.hpp>
#include <LinkBlock.hpp>

/* ============================================================================
 *
 * */
EXPORT_BLOCK(JointBlock)

/* ============================================================================
 *
 * */
void JointBlock::updateKinematic()
{
    // To update a joint it must have a base link which has a base joint
    if(_baseLink)
    {
        // Get base link
        QSharedPointer<LinkBlock> baseLink   = _baseLink.toStrongRef();

        // Get the base joint of the base link
        QSharedPointer<JointBlock> baseJoint = baseLink->sharedBase();

        if( baseLink->hasBase() )
        {

            _pos = baseLink->transform() * baseJoint->pos();



            // Log
            beglog() << "Axe updated to "      << baseLink->transform() * QVector4D(0,0,1,0) << endlog();
            beglog() << "Position updated to " << _pos << endlog();

            // Alert chain elements
            emit spreadKinematic();

            // Alert BotJs
            emit blockiPropertyValuesChanged();

            return;
        }
        else
        {
            // Initialize position
            _pos = QVector4D(0,0,0,1);

            // Log
            beglog() << "Base Link #" << baseLink->getBlockFathersChain() << "# has no base joint! Position reset to " << _pos << endlog();

            // Alert chain elements
            emit spreadKinematic();
        }
    }
    else
    {
        // Initialize position
        _pos = QVector4D(0,0,0,1);

        // Log
        beglog() << "No base link! Position reset to " << _pos << endlog();

        // Alert chain elements
        emit spreadKinematic();
    }

    // Alert BotJs
    emit blockiPropertyValuesChanged();
}

/* ============================================================================
 *
 * */
QList<QSharedPointer<PhysicBlock> > JointBlock::getPhysicSlaves()
{
    QList<QSharedPointer<PhysicBlock> > slaves;
    
    foreach( QWeakPointer<LinkBlock> link, _outputLinks )
    {
        QSharedPointer<LinkBlock> shared_link = link.toStrongRef();

        QSharedPointer<PhysicBlock> shared_physic = qSharedPointerObjectCast<PhysicBlock, LinkBlock>(shared_link);

        slaves << shared_physic;
    }

    return slaves;
}

/* ============================================================================
 *
 * */
bool JointBlock::connect(BotBlock* block, bool master)
{
    // Basic checks
    if(!block)        { beglog() << "Connection to null block failure" << endlog(); return false; }
    if(block == this) { beglog() << "Connection to itself refused"     << endlog(); return false; }

    // Check if the block is a link block
    LinkBlock* link = qobject_cast<LinkBlock*>(block);
    if(!link)
    {
        return BotBlock::connect(block, master);
    }
    
    // 
    if(master)
    {
        // Ask for connection
        if( ! block->connect(this, false) )
        {
            // If the other block rejected the connection and log it
            beglog() << "Connection to the link #" << block->getBlockFathersChain() << "# failure: connection return refused" << endlog();
            return false;
        }

        // Create the shared pointer
        QSharedPointer<LinkBlock> shared_link = qSharedPointerObjectCast<LinkBlock, BotBlock>( block->getBlockSharedFromThis() );
        
        // Set the new output joint
        QWeakPointer<LinkBlock> weak_link = shared_link.toWeakRef();

        // 
        _outputLinks << weak_link;

        // Log and return
        beglog() << "Connection to the link #" << block->getBlockFathersChain() << "#" << endlog();
        return true;
    }
    else
    {

        // If output already exist
        if(_baseLink)
        {
            // this->disconnect(_baseLink.data());
        }

        // Create the shared pointer
        QSharedPointer<LinkBlock> shared_based = qSharedPointerObjectCast<LinkBlock, BotBlock>( block->getBlockSharedFromThis() );
        
        // Set the new output joint
        _baseLink = shared_based.toWeakRef();

        // Alert BotJs
        emit blockfPropertyValuesChanged();

        // Log and return
        beglog() << "Connection from the link #" << block->getBlockFathersChain() << "# accepted" << endlog();
        return true;
    }

}

/* ============================================================================
 *
 * */
void JointBlock::disconnect(BotBlock* block, bool master)
{

}

/* ============================================================================
 *
 * */
void JointBlock::disconnectAll()
{

}


/* ============================================================================
 *
 * */
void JointBlock::updateShapeData()
{
    // Reset the shape data
    _shapeData.reset();


    switch( _modelType )
    {
        case ModelTypeBase:

            break;

        case ModelTypeKinematic:
            _shapeData.createSphere( 2, 2 );
            break;
    }

}


