//!
//! \file VertexBufferObject.cpp
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

#include <VertexBufferObject.hpp>

/* ============================================================================
 *
 * */
VertexBufferObject::VertexBufferObject()
    : _vertexBuffer (QGLBuffer::VertexBuffer)
    , _indiceBuffer (QGLBuffer::IndexBuffer )
{

}

/* ============================================================================
 *
 * */
void VertexBufferObject::subdivide( QVector3D p1, QVector3D p2, QVector3D p3, qreal radius, ObjBufferConfig& obj, int depth )
{
    if(depth <= 0)
    {
        const GLuint vindex = _vertexArray.size();

        // Append indices
        _indiceArray << QVector<GLuint>( { vindex + 0, vindex + 1, vindex + 2} );
        
        // Append vertices
        _vertexArray << p1 << p2 << p3;

        // Adjust the number of vertex to render
        obj.isize += 3;
    }
    else
    {
        auto moy = [](float n1, float n2) { return (n1+n2)/2; };

        QVector3D p12( moy(p1.x(), p2.x()), moy(p1.y(), p2.y()), moy(p1.z(), p2.z()) );
        p12 = p12.normalized() * radius;
        QVector3D p23( moy(p3.x(), p2.x()), moy(p3.y(), p2.y()), moy(p3.z(), p2.z()) );
        p23 = p23.normalized() * radius;
        QVector3D p31( moy(p1.x(), p3.x()), moy(p1.y(), p3.y()), moy(p1.z(), p3.z()) );
        p31 = p31.normalized() * radius;

        subdivide( p1 , p12, p31, radius, obj, depth-1 );
        subdivide( p12, p2 , p23, radius, obj, depth-1 );
        subdivide( p12, p23, p31, radius, obj, depth-1 );
        subdivide( p31, p23, p3 , radius, obj, depth-1 );
    }
}

/* ============================================================================
 *
 * */
void VertexBufferObject::createSphere( qreal radius, GLuint subdiv, ObjBufferConfig& obj )
{
    // Compute initial points
    QVector3D pA(  radius,  0     ,  0     );
    QVector3D pB(  0     ,  radius,  0     );
    QVector3D pC( -radius,  0     ,  0     );
    QVector3D pD(  0     , -radius,  0     );

    QVector3D pE(  0     ,  0     ,  radius);
    QVector3D pF(  0     ,  0     , -radius);

    // sub
    subdivide( pE, pA, pB, radius, obj, subdiv );
    subdivide( pE, pB, pC, radius, obj, subdiv );
    subdivide( pD, pE, pC, radius, obj, subdiv );
    subdivide( pD, pA, pE, radius, obj, subdiv );

    subdivide( pF, pA, pB, radius, obj, subdiv );
    subdivide( pF, pB, pC, radius, obj, subdiv );
    subdivide( pD, pF, pC, radius, obj, subdiv );
    subdivide( pD, pA, pF, radius, obj, subdiv );
}


