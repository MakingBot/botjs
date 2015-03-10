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
#ifdef JOINT_BUILD
EXPORT_BLOCK(JointBlock)
#endif

/*
position venant de PhysicBlock                      = 0;

const quint8 JointBlock::IdPropertyAxe              = 1;
const quint8 JointBlock::IdPropertyType             = 2;

const quint8 JointBlock::IdPropertyMinValue         = 3;
const quint8 JointBlock::IdPropertyMaxValue         = 4;
const quint8 JointBlock::IdPropertyGoalValue        = 5;
const quint8 JointBlock::IdPropertyCurrentValue     = 6;

const quint8 JointBlock::IdPropertyMinSpeed         = 7;
const quint8 JointBlock::IdPropertyMaxSpeed         = 8;
const quint8 JointBlock::IdPropertyGoalSpeed        = 9;
const quint8 JointBlock::IdPropertyCurrentSpeed     = 10;

const quint8 JointBlock::IdPropertyMaxTorque        = 11;
const quint8 JointBlock::IdPropertyGoalTorque       = 12;
const quint8 JointBlock::IdPropertyCurrentTorque    = 13;
*/

/* ============================================================================
 *
 * */
void JointBlock::updateJoint()
{

    /*
    // To update a joint it must have a base link which has a base joint
    if(_inlink)
    {
        // Get base link
        QSharedPointer<LinkBlock> baseLink   = _inlink.toStrongRef();

        // Get the base joint of the base link
        QSharedPointer<JointBlock> baseJoint = baseLink->sharedBase();

        if( baseLink->hasBase() )
        {

            _pos = baseLink->transform() * baseJoint->pos();



            // Log
            beglog() << "Axe updated to "      << baseLink->transform() * QVector4D(0,0,1,0) << endlog();
            beglog() << "Position updated to " << _pos << endlog();

            // Alert chain elements
//            emit spreadKinematic();

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
    */

    // Alert BotJs
    emit blockiPropertyValuesChanged();
}

/* ============================================================================
 *
 * */
void JointBlock::updateAxe()
{
    // If there is no in link the position is the origine
    if( ! _inlink ) return;

    // The position is function of the in link
    QSharedPointer<LinkBlock> link = _inlink.toStrongRef();
    _axe = link->getPhysicTransform() * QVector4D(1,0,0,0);
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

        // Append the link in the out link list
        _outlinks << block->toSpecializedSharedPointer<LinkBlock>().toWeakRef();

        // Log and return
        beglog() << "Connection to the link #" << block->getBlockFathersChain() << "#" << endlog();

        // Alert BotJs
        emit blockfPropertyValuesChanged();

        return true;
    }
    else
    {
        // If connection exists disconnect
        if(_inlink) this->disconnect(_inlink.data());

        // Set
        _inlink = block->toSpecializedSharedPointer<LinkBlock>().toWeakRef();

        // Log and return
        beglog() << "Connection from the link #" << block->getBlockFathersChain() << "# accepted" << endlog();

        // Alert BotJs
        emit blockfPropertyValuesChanged();

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
void JointBlock::updatePhysicShapeData      ()
{
    // Reset the shape data
    _shapeData.reset();


    switch( _modelType )
    {
        case ModelTypeBase:

            break;

        case ModelTypeKinematic:
            _shapeData.createSphere( 0.05, 2 );

            //_shapeData.createCuboid( 2, 0.1, 0.1 );
            //_shapeData.createCone( 0.1, 0.3, 5 );
            break;
    }

}

/* ============================================================================
 *
 * */
void JointBlock::updatePhysicPosition       ()
{
    // If there is no in link the position is the origine
    if( ! _inlink )
    {
        _position = QVector4D(0,0,0,1);
        return;
    }

    // The position is function of the in link
    QSharedPointer<LinkBlock> link = _inlink.toStrongRef();
    _position = link->getPhysicTransform() * link->getPhysicPosition();
}

/* ============================================================================
 *
 * */
void JointBlock::updatePhysicTransform      ()
{
    // Compute global transform
    _transform = _postTransform ;

}

/* ============================================================================
 *
 * */
void JointBlock::updatePhysicPreTransform   ()
{
    // Reset matrix
    _preTransform.setToIdentity();
}

/* ============================================================================
 *
 * */
void JointBlock::updatePhysicPostTransform  ()
{
    // Reset matrix
    _postTransform.setToIdentity();

    // Compute in function of the joint type
    switch( _type )
    {
        case JointFixe:
            break;

        case JointRevolute:
            break;

        case JointPrismatic:
            break;
    }
}

/* ============================================================================
 *
 * */
void JointBlock::updatePhysicSlaves         ()
{
    // Clear old list
    _physicSlaves.clear();

    // Insert out links
    foreach( QWeakPointer<LinkBlock> link, _outlinks )
    {
    	_physicSlaves << qSharedPointerObjectCast<PhysicBlock, LinkBlock> ( link );
    }

    // Log
    beglog() << "Physic slaves list updated " << _physicSlaves.size() << " elements" << endlog();
}
