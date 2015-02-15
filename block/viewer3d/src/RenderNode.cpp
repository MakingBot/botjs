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
RenderNode::RenderNode( QSharedPointer<PhysicBlock> ref, Viewer& viewer )
    : _viewer(viewer)
{
    // Reset object config
    _viewer.vbo().ini(_objConfig);

    if( viewer.model() == PhysicBlock::ModelTypeBase )
    {

        _viewer.vbo().createBase( _objConfig );

    }
    else
    {

        switch( ref->getShapeType(viewer.model()) )
        {
            

            case PhysicBlock::ShapeTypeSphere:

                _viewer.vbo().createSphere( 0.25, 4, _objConfig );
                break;

            case PhysicBlock::ShapeTypeArrow :
                _viewer.vbo().createArrow( 0.25, ref->getShapeLenght(), 10, _objConfig );

                

                break;

            default: break;
        }
    
    }

    //QObject::connect( ref.data(), SIGNAL(blockiPropertyValuesChanged()), &viewer, SLOT(onBlockPropertiesChange()) );
    


    QList<QSharedPointer<PhysicBlock> > slaves = ref->getPhysicSlaves();
    foreach(QSharedPointer<PhysicBlock> slave, slaves)
    {
        _nodeChilds << QSharedPointer<RenderNode>( new RenderNode(slave, _viewer) );
    }

    // Track the reference
    _ref = ref.toWeakRef();
}


/* ============================================================================
 *
 * */
void RenderNode::draw()
{
    if(!_ref) { }


    QSharedPointer<PhysicBlock> ref = _ref.toStrongRef();



    glPushMatrix();


    glMultMatrixf( ref->getPreTransform().constData()  );


    // Draw the shape triangles
    glDrawElements(GL_TRIANGLES, _objConfig.isize, GL_UNSIGNED_INT, GLUB_BUFFER_OFFSET(_objConfig.iindex) );


    // Draw child nodes
    foreach(QSharedPointer<RenderNode> node, _nodeChilds)
    {
        node->draw();
    }


    glPopMatrix();
}
