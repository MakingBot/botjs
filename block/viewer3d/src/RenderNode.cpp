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

std::cout << "plop" << std::endl;
    switch( ref->getShapeType(viewer.model()) )
    {
        

        case PhysicBlock::ShapeTypeSphere:
            _viewer.vbo().createSphere( 0.5, 4, _objConfig );
            std::cout << "sphere" << std::endl;
            break;

        case PhysicBlock::ShapeTypeArrow :
            _viewer.vbo().createCylinder( 0.5, 1, 5, _objConfig );
            std::cout << "arrow" << std::endl;
            break;

        default: break;
    }

    //ShapeType

// ShapeTypeNone, ShapeTypeBox, ShapeTypeSphere, ShapeTypeCylender, ShapeTypeArrow
    

    



    // Track the reference
    _ref = ref.toWeakRef();
}


/* ============================================================================
 *
 * */
void RenderNode::draw()
{

    // Draw the shape triangles
    glDrawElements(GL_TRIANGLES, _objConfig.isize, GL_UNSIGNED_INT, GLUB_BUFFER_OFFSET(_objConfig.iindex) );

}
