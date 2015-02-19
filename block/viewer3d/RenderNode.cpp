//!
//! \file RenderNode.cpp
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

#include <RenderNode.hpp>

#include <Viewer.hpp>

#include <iostream>

/* ============================================================================
 *
 * */
RenderNode::RenderNode( QSharedPointer<PhysicBlock> ref, Viewer* viewer )
    :  _viewer(viewer), _physicObject(ref)
{

    _physicObject->updateShapeData();



    // Disconnect precedent connection
    QObject::disconnect( _physicObject.data(), SIGNAL(blockPhysicStructureChanged()), _viewer, SLOT(onBlockPropertiesChange()) );


    QObject::connect( _physicObject.data(), SIGNAL(blockPhysicStructureChanged()), viewer, SLOT(onBlockPropertiesChange()) );



    _sector = _viewer->vbo().append( _physicObject->getPhysicShapeData() );



    QList<QSharedPointer<PhysicBlock> > slaves = ref->getPhysicSlaves();
    foreach(QSharedPointer<PhysicBlock> slave, slaves)
    {

        if(slave)
        {
            RenderNode* node = new RenderNode(slave, _viewer);
            std::cout << "liena ok == " << slave->getBlockName().toStdString() << std::endl;
            _nodeChilds << QSharedPointer<RenderNode>( node );
       
        }
        else
        {
            std::cout << "nnununuunununullll" << std::endl;
        }

        

       // 
    }

}

/* ============================================================================
 *
 * */
RenderNode::~RenderNode()
{



    
}




#define BUFFER_OFFSET(bytes) ((GLuint*) NULL + (bytes)) 


/* ============================================================================
 *
 * */
void RenderNode::draw()
{
    
//    if(!_ref) { }


    glPushMatrix();


    glMultMatrixf( _physicObject->getPreTransform().constData() );

    // std::cout << _physicObject->getPreTransform()(0,0) << "  " << _physicObject->getPreTransform()(1,0) << "  " << _physicObject->getPreTransform()(2,0) << "  " << _physicObject->getPreTransform()(3,0)  << std::endl;
    // std::cout << _physicObject->getPreTransform()(0,1) << "  " << _physicObject->getPreTransform()(1,1) << "  " << _physicObject->getPreTransform()(2,1) << "  " << _physicObject->getPreTransform()(3,1)  << std::endl;
    // std::cout << _physicObject->getPreTransform()(0,2) << "  " << _physicObject->getPreTransform()(1,2) << "  " << _physicObject->getPreTransform()(2,2) << "  " << _physicObject->getPreTransform()(3,2)  << std::endl;
    // std::cout << _physicObject->getPreTransform()(0,3) << "  " << _physicObject->getPreTransform()(1,3) << "  " << _physicObject->getPreTransform()(2,3) << "  " << _physicObject->getPreTransform()(3,3)  << std::endl;

    if( _physicObject->colorize() )
    {
        glColor3f(1.0f, 1.0f, 0.0f);
    }
    else
    {
        glColor3f(1.0f, 0.0f, 1.0f);
    }
    

    // Draw the shape triangles
    glDrawElements(GL_TRIANGLES, _sector.isize, GL_UNSIGNED_INT, (GLvoid*)( _sector.iindex*sizeof(GLuint) ) );
   //     GLUB_BUFFER_OFFSET(_sector.iindex) );

    glMultMatrixf( _physicObject->getPostTransform().constData() );

    // Draw child nodes
    foreach(QSharedPointer<RenderNode> node, _nodeChilds)
    {
        node->draw();
    }


    glPopMatrix();
    
}
