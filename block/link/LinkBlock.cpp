//!
//! \file LinkBlock.cpp
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

#include <math.h>
#include <LinkBlock.hpp>
#include <JointBlock.hpp>
#include <QtCore/qmath.h>

/* ============================================================================
 *
 * */
#ifndef JOINT_BUILD
EXPORT_BLOCK(LinkBlock)
#endif

/* ============================================================================
 *
 * */
void LinkBlock::updateLink()
{
    // Update transformation
    updatePhysicPreTransform   ();
    updatePhysicPostTransform  ();
    updatePhysicTransform      ();
    updatePhysicShapeData      ();

    // Alert BotJs
    emit blockiPropertyValuesChanged();
}

/* ============================================================================
 *
 * */
bool LinkBlock::connect(BotBlock* block, bool master)
{
    // Basic checks
    if(!block)        { beglog() << "Connection to null block failure" << endlog(); return false; }
    if(block == this) { beglog() << "Connection to itself refused"     << endlog(); return false; }

    // Check if the block is a joint block
    JointBlock* joint = qobject_cast<JointBlock*>(block);
    if(!joint)
    {
        return BotBlock::connect(block, master);
    }

    // Else it is a joint block

    if(master)
    {
        // In the case this link ask for the connection

        // Ask for connection
        if( ! block->connect(this, false) )
        {
            beglog() << "Connection to #" << block->getBlockFathersChain() << "# failure: connection return refused" << endlog();
            return false;
        }

        // If connection exists disconnect
        if(_outjoint) this->disconnect(_outjoint.data());

        // Set
        _outjoint = block->toSpecializedSharedPointer<JointBlock>().toWeakRef();

        // Log and return
        beglog() << "Connection to the joint #" << block->getBlockFathersChain() << "#" << endlog();

        // Update physic slaves
        this->updatePhysicSlaves();

        // Alert BotJs
        emit blockfPropertyValuesChanged();

        return true;
    }
    else
    {
        // In this case a joint ask for a connection

        // If connection exists disconnect
        if(_injoint) this->disconnect(_injoint.data());

        // Set
        _injoint = block->toSpecializedSharedPointer<JointBlock>().toWeakRef();

        // Log
        beglog() << "Connection from the joint #" << block->getBlockFathersChain() << "# accepted" << endlog();

        // Alert BotJs
        emit blockfPropertyValuesChanged();

        return true;
    }
}

/* ============================================================================
 *
 * */
void LinkBlock::disconnect(BotBlock* block, bool master)
{
    // Check if the block is a joint block
    JointBlock* joint = qobject_cast<JointBlock*>(block);
    if(!joint)
    {
        BotBlock::disconnect(block, master);
        return;
    }

    bool flagdone = false;
    if(master)
    {
        block->disconnect(this, false);
    }

    // Check if the block is in joint
    if( _injoint )
    {
        QSharedPointer<JointBlock> injoint = _injoint.toStrongRef();
        if( injoint.data() == joint )
        {
            _injoint.clear();
            flagdone = true;
        }
    }
    // Check if the block is out joint
    else if( _outjoint )
    {
        QSharedPointer<JointBlock> outjoint = _outjoint.toStrongRef();
        if( outjoint.data() == joint )
        {
            _outjoint.clear();
            flagdone = true;
        }
    }

    // Terminal actions
    if(flagdone)
    {
        // Alert BotJs
        emit blockfPropertyValuesChanged();

        // Log
        beglog() << "Disconnection from #" << block->getBlockFathersChain() << "#" << endlog();
    }
}

/* ============================================================================
 *
 * */
void LinkBlock::disconnectAll()
{
	// Check if the block is in joint
	if( _injoint )
	{
		_injoint.clear();
	}

	// Check if the block is out joint
	if( _outjoint )
	{
		_outjoint.clear();
	}

	BotBlock::disconnectAll();
}

/* ============================================================================
 *
 * */
void LinkBlock::updatePhysicShapeData      ()
{
    // Reset the shape data
    _shapeData.reset();


    //_shapeData.createCuboid( 1, 0.1, 0.1 );

    switch( _modelType )
    {
        case ModelTypeBase:

            break;

        case ModelTypeKinematic:
            // _shapeData.createSphere( 0.10, 2 );
            _shapeData.createCylinder ( 0.20, length(), 10 );
            

            break;
    }
}

/* ============================================================================
 *
 * */
void LinkBlock::updatePhysicPosition       ()
{
    // If there is no in joint the position is the origine
    if( ! _injoint )
    {
        _position = QVector4D(0,0,0,1);
        return;
    }

    // The position is function of the in joint
    QSharedPointer<JointBlock> joint = _injoint.toStrongRef();
    _position = joint->getPhysicTransform() * joint->getPhysicPosition();
}

/* ============================================================================
 *
 * */
void LinkBlock::updatePhysicTransform      ()
{
    // Compute global transform
    _transform = _postTransform * _preTransform ;

    // Log
    beglog() << "Physic transform updated" << endlog();

    // Update out joint
    if( _outjoint )
    {
        QSharedPointer<JointBlock> out = _outjoint.toStrongRef();
        out->updateJoint();
    }
}

/* ============================================================================
 *
 * */
void LinkBlock::updatePhysicPreTransform   ()
{
    auto sign = [](float val) { if(val>=0) return 1; else return -1; };

    const float degpi = 180/M_PI;
    const QVector3D vecX(1,0,0);
    const QVector3D vecY(0,1,0);
    const QVector3D vecZ(0,0,1);

    // Angle xz
    QVector3D projxz = _translation;
    projxz.setY(0);
    qreal anglexz = qAcos( QVector3D::dotProduct( vecZ, projxz ) / projxz.length() );
    QVector3D vec = QVector3D::crossProduct( vecZ, projxz );
    anglexz *= sign( vec.y() );

    // Angle yz
    QVector3D projyz = _translation;
    projyz.setX(0);
    qreal angleyz = qAcos( QVector3D::dotProduct( vecZ, projyz ) / projyz.length() );
              vec = QVector3D::crossProduct( vecZ, projyz );
    angleyz *= sign( vec.x() );

    // Apply transformations
    _preTransform.setToIdentity();
    _preTransform.rotate( anglexz*degpi, vecY );
    _preTransform.rotate( angleyz*degpi, vecX );
    _preTransform.translate( vecZ * ( length()/2.0f ) );

    // Log
    beglog() << "Physic pre-transform updated" << endlog();
}

/* ============================================================================
 *
 * */
void LinkBlock::updatePhysicPostTransform  ()
{
    // Compute post transformation
    _postTransform.setToIdentity();
    _postTransform.translate( QVector3D(0,0,1) * ( length()/ 1.5 ) );

    // End rotation
    // _postTransform.rotate( _rotation[0], QVector3D(1,0,0) );
    // _postTransform.rotate( _rotation[1], QVector3D(0,1,0) );
    // _postTransform.rotate( _rotation[2], QVector3D(0,0,1) );

    // Log
    beglog() << "Physic post-transform updated" << endlog();
}

/* ============================================================================
 *
 * */
void LinkBlock::updatePhysicSlaves         ()
{
    // Clear old list
    _physicSlaves.clear();

    // Cast and append
    _physicSlaves << qSharedPointerObjectCast<PhysicBlock, JointBlock> ( _outjoint );

    // Log
    beglog() << "Physic slaves list updated " << _physicSlaves.size() << " elements" << endlog();
}
