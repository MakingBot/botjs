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

#include <LinkBlock.hpp>
#include <JointBlock.hpp>

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
QString LinkBlock::endName()
{
    QSharedPointer<JointBlock> end = sharedOutput();
    if( end )  { return end->getBlockName(); }
    else       { return QString("Undefined");}
}

/* ============================================================================
 *
 * */
void LinkBlock::updateTransform()
{
    // Start with the identity matrix
    QMatrix4x4 new_transform;

    // Translate
    new_transform.translate(_translation.toVector3D());

    new_transform.rotate( _rotation[0], QVector3D(1, 0, 0) );
    new_transform.rotate( _rotation[1], QVector3D(0, 1, 0) );
    new_transform.rotate( _rotation[2], QVector3D(0, 0, 1) );

    // Set the new transformation
    _transform = new_transform;
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
        if(!block->connect(this, false))
        {
            // Log and return
            beglog() << "Connection to #" << block->getBlockFathersChain() << "# failure: connection return refused" << endlog();
            return false;
        }

        // Assume that if the link ask, then the joint is the output
        
        // If output already exist
        if(_outputJoint)
        {
            this->disconnect(_outputJoint.data());
        }

        // Create the shared pointer
        QSharedPointer<JointBlock> sh_out = qSharedPointerObjectCast<JointBlock, BotBlock>( block->getBlockSharedFromThis() );
        
        // Set the new output joint
        _outputJoint = sh_out.toWeakRef();

        // Alert BotJs
        emit blockfPropertyValuesChanged();

        // Log and return
        beglog() << "Connection to #" << block->getBlockFathersChain() << "#" << endlog();
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
        beglog() << "Connection from #" << block->getBlockFathersChain() << "# accepted" << endlog();
        return true;

    }
    
}
