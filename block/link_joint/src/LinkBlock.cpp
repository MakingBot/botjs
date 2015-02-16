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
EXPORT_BLOCK(LinkBlock)


/* ============================================================================
 *
 * */
QString LinkBlock::baseName()
{
    QSharedPointer<JointBlock> base = sharedBase();
    if( base ) { return base->getBlockName();}
    else       { return QString("Undefined");}
}

/* ============================================================================
 *
 * */
QList<QSharedPointer<PhysicBlock> > LinkBlock::getPhysicSlaves()
{

    QList<QSharedPointer<PhysicBlock> > slaves;


    QSharedPointer<JointBlock> shared_joint = _outputJoint.toStrongRef();

    QSharedPointer<PhysicBlock> shared_physic = qSharedPointerObjectCast<PhysicBlock, JointBlock>(shared_joint);

    slaves << shared_physic;
    

    return slaves;

}

/* ============================================================================
 *
 * */
QMatrix4x4 LinkBlock::getPreTransform()
{
    return _preTransform;
}

/* ============================================================================
 *
 * */
QMatrix4x4 LinkBlock::getPostTransform()
{
    return QMatrix4x4();
}

/* ============================================================================
 *
 * */
QString LinkBlock::endName()
{
    QSharedPointer<JointBlock> end = sharedOutput();
    if( end )  { return end->getBlockName(); }
    else       { return QString("Undefined");}
}

/* ============================================================================
 *
 * */
void LinkBlock::updateKinematic()
{
    auto sign = [](float val) { if(val>=0) return 1; else return -1; };

    // Angle xz
    QVector3D projxz = _translation;
    projxz.setY(0);
    qreal anglexz = qAcos( QVector3D::dotProduct( QVector3D(0,0,1), projxz ) / projxz.length() );
    QVector3D vec = QVector3D::crossProduct( QVector3D(0,0,1), projxz );
    anglexz *= sign( vec.y() );

    // Angle yz
    QVector3D projyz = _translation;
    projyz.setX(0);
    qreal angleyz = qAcos( QVector3D::dotProduct( QVector3D(0,0,1), projyz ) / projyz.length() );
              vec = QVector3D::crossProduct( QVector3D(0,0,1), projyz );
    angleyz *= sign( vec.x() );

    // Apply rotations
    _preTransform.setToIdentity();
    _preTransform.rotate( ((anglexz * 180)/M_PI), QVector3D(0, 1, 0) );
    _preTransform.rotate( ((angleyz * 180)/M_PI), QVector3D(1, 0, 0) );






    // Start with the identity matrix
    QMatrix4x4 new_transform;

    // Translate
    new_transform.translate( translation() );
    new_transform.rotate( _rotation[0], QVector3D(1, 0, 0) );
    new_transform.rotate( _rotation[1], QVector3D(0, 1, 0) );
    new_transform.rotate( _rotation[2], QVector3D(0, 0, 1) );


    //_preTransform.rotate( 45, QVector3D(1, 0, 0) );



    // Set the new transformation
    _transform = new_transform;

    // Alert chain elements
    emit spreadKinematic();

    // Alert BotJs
    emit blockiPropertyValuesChanged();

    if( _outputJoint )
    {
        QSharedPointer<JointBlock> shared_endjoint = _outputJoint.toStrongRef();

        shared_endjoint->updateKinematic();
    }

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
    // if the link ask for the connection
    if(master)
    {
        // Ask for connection
        if( ! block->connect(this, false) )
        {
            // If the other block rejected the connection and log it
            beglog() << "Connection to #" << block->getBlockFathersChain() << "# failure: connection return refused" << endlog();
            return false;
        }

        // If output already exist
        if(_outputJoint)
        {
            this->disconnect(_outputJoint.data());
        }

        // Recover the shared pointer of the connection block
        QSharedPointer<JointBlock> shared_end = qSharedPointerObjectCast<JointBlock, BotBlock>( block->getBlockSharedFromThis() );

        // Connect signals
        QObject::connect( this, SIGNAL(spreadKinematic()), shared_end.data(), SLOT(updateKinematic()) );

        // Set the new end joint
        _outputJoint = shared_end.toWeakRef();

        // Alert chain elements
        emit spreadKinematic();

        // Alert BotJs
        emit blockfPropertyValuesChanged();

        // Log and return
        beglog() << "Connection to the joint #" << block->getBlockFathersChain() << "#" << endlog();
        return true;
    }
    else
    {
        // If output already exist
        if(_baseJoint)
        {
            this->disconnect(_baseJoint.data());
        }

        // Create the shared pointer
        QSharedPointer<JointBlock> sh_out = qSharedPointerObjectCast<JointBlock, BotBlock>( block->getBlockSharedFromThis() );
        
        // Set the new output joint
        _baseJoint = sh_out.toWeakRef();

        // Alert BotJs
        emit blockfPropertyValuesChanged();
        // Log and return
        beglog() << "Connection from the joint #" << block->getBlockFathersChain() << "# accepted" << endlog();
        return true;

    }
    
}

/* ============================================================================
 *
 * */
void LinkBlock::disconnect(BotBlock* block, bool master)
{
    // TODO
    BotBlock::disconnect(block, master);
}

/* ============================================================================
 *
 * */
void LinkBlock::disconnectAll()
{
    // TODO
    BotBlock::disconnectAll();
}


/* ============================================================================
 *
 * */
void LinkBlock::updateShapeData()
{
    // Reset the shape data
    _shapeData.reset();


    switch( _modelType )
    {
        case ModelTypeBase:

            break;

        case ModelTypeKinematic:
            
            _shapeData.createCylinder ( 0.5, lenght(), 5 );

            break;
    }

}
