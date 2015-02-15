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

#include <Viewer.hpp>

#define BUFFER_PI 3.141592653589793

/* ============================================================================
 *
 * */
VertexBufferObject::VertexBufferObject(Viewer& viewer)
    : _viewer       (viewer) 
    , _vertexBuffer (QGLBuffer::VertexBuffer)
    , _indiceBuffer (QGLBuffer::IndexBuffer )
{

    _viewer.makeCurrent();

    _vertexBuffer.create();
    _vertexBuffer.bind();
    _vertexBuffer.setUsagePattern(QGLBuffer::DynamicDraw);
    _vertexBuffer.allocate(300000 * sizeof(QVector3D));
    _vertexBuffer.release();

    _indiceBuffer.create();
    _indiceBuffer.bind();
    _indiceBuffer.setUsagePattern(QGLBuffer::DynamicDraw);
    _indiceBuffer.allocate(300000 * sizeof(GLuint    ));
    _indiceBuffer.release();

    _viewer.doneCurrent();

}

/* ============================================================================
 *
 * */
void VertexBufferObject::ini(ObjBufferConfig& obj)
{
    obj.iindex = _indiceArray.size();
    obj.isize  = 0;
    obj.vindex = _vertexArray.size();
    obj.vsize  = 0;
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
        obj.vsize += 3;
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

/* ============================================================================
 *
 * */
void VertexBufferObject::createCylinder( qreal radius, qreal height, GLuint slices, ObjBufferConfig& obj )
{
    // Set buffer param
    const GLuint vindex = _vertexArray.size();

    // Compute number of indice to append
    obj.isize += 4 * slices;   // nb triangles for top, bot circle and body
    obj.isize *= 3;            // 3 points per triangles

    obj.vsize += 2*slices + 2;

    // Compute const
    const qreal height2 = height/2;
    const qreal step = (M_PI * 2) / slices;
    
    // Append center bot and top
    _vertexArray << QVector3D(0, 0, -height2); // bot 0
    _vertexArray << QVector3D(0, 0,  height2); // top 1
    
    // Append points of the bot circle
    for(GLuint i=0 ; i<slices ; i++)
    {
        const qreal angle = step * i;
        const qreal sina  = qSin(angle); 
        const qreal cosa  = qCos(angle);
        
        _vertexArray << QVector3D( cosa*radius, sina*radius, -height2 );
    }

    // Append points of the top circle
    for(GLuint i=0 ; i<slices ; i++)
    { 
        QVector3D topPoint(_vertexArray.at(vindex + 2 + i));
        topPoint.setZ(height2);
        _vertexArray << topPoint;
    }

    // Index for bot circle
    for(GLuint i=0 ; i<slices ; i++)
    {
        GLuint tmp = i+1;
        if( tmp >= slices ) { tmp -= slices; }

        const GLuint p1 = vindex + 2 + tmp; // i + 1
        const GLuint p2 = vindex + 2 + i;   // i

        _indiceArray << QVector<GLuint>( {p1, p2, vindex+0} );
    }

    // Index for top circle
    for(GLuint i=0 ; i<slices ; i++)
    {
        GLuint tmp = i+1;
        if( tmp >= slices ) { tmp -= slices; }

        const GLuint p1 = vindex + 2 + slices + tmp; // i + 1
        const GLuint p2 = vindex + 2 + slices + i;   // i

        _indiceArray << QVector<GLuint>( {p1, p2, vindex+1} );
    }

    // Index for body
    for(GLuint i=0 ; i<slices ; i++)
    {
        GLuint tmp = i+1;
        if( tmp >= slices ) { tmp -= slices; }

        const GLuint p01 = vindex + 2 + tmp; // i + 1
        const GLuint p02 = vindex + 2 + i;   // i

        const GLuint p11 = vindex + 2 + slices + tmp; // i + 1
        const GLuint p12 = vindex + 2 + slices + i;   // i

        _indiceArray << QVector<GLuint>( {p12, p02, p01}  );
        _indiceArray << QVector<GLuint>( {p12, p01, p11 } );
    }
}

/* ============================================================================
 *
 * */
void VertexBufferObject::createCone( qreal radius, qreal height, GLuint slices, ObjBufferConfig& obj )
{
    // Set buffer param
    const GLuint vindex = _vertexArray.size();

    // Compute number of indice to append
    obj.isize += 2 * slices;   // nb triangles for top, bot circle and body
    obj.isize *= 3;            // 3 points per triangles

    obj.vsize += slices + 2;

    // Compute const
    const qreal height2 = height / 2;
    const qreal step = (M_PI * 2) / slices;
    
    // Append center bot and top
    _vertexArray << QVector3D(0, 0, -height2); // bot 0
    _vertexArray << QVector3D(0, 0,  height2); // top 1
    
    // Append points of the bot circle
    for(GLuint i=0 ; i<slices ; i++)
    {
        const qreal angle = step * i;
        const qreal sina  = qSin(angle);
        const qreal cosa  = qCos(angle);
        
        _vertexArray << QVector3D( cosa*radius, sina*radius, -height2 );
    }

    // Append points of the top circle
    for(GLuint i=0 ; i<slices ; i++)
    { 
        QVector3D topPoint(_vertexArray.at(vindex + 2 + i));
        topPoint.setZ(height2);
        _vertexArray << topPoint;
    }

    // Index for bot circle
    for(GLuint i=0 ; i<slices ; i++)
    {
        GLuint tmp = i+1;
        if( tmp >= slices ) { tmp -= slices; }

        const GLuint p1 = vindex + 2 + tmp; // i + 1
        const GLuint p2 = vindex + 2 + i;   // i

        _indiceArray << QVector<GLuint>( {p1, p2, vindex+0} );
    }

    // Index for body
    for(GLuint i=0 ; i<slices ; i++)
    {
        GLuint tmp = i+1;
        if( tmp >= slices ) { tmp -= slices; }

        const GLuint p1 = vindex + 2 + tmp; // i + 1
        const GLuint p2 = vindex + 2 + i;   // i

        _indiceArray << QVector<GLuint>( {p1, p2, vindex+1} );
    }
}


/* ============================================================================
 * Y                        Y
 *
 * D ----- C        H ----- G
 *
 * 
 * A ----- B  X  X  E ----- F
 *
 * Front Z to us Back Z to the screen
 * */

#define CUBE_A 0
#define CUBE_B 1
#define CUBE_C 2
#define CUBE_D 3
#define CUBE_E 4
#define CUBE_F 5
#define CUBE_G 6
#define CUBE_H 7

void VertexBufferObject::createCuboid( qreal rx, qreal ry, qreal rz, ObjBufferConfig& obj )
{
    // Set buffer param
    const GLuint vindex = _vertexArray.size();

    // Compute const
    const qreal rx2 = rx / 2;
    const qreal ry2 = ry / 2;
    const qreal rz2 = rz / 2;

    // Append 8 points
    _vertexArray << QVector3D( -rx2, -ry2,  rz2 ); // A
    _vertexArray << QVector3D(  rx2, -ry2,  rz2 ); // B
    _vertexArray << QVector3D(  rx2,  ry2,  rz2 ); // C
    _vertexArray << QVector3D( -rx2,  ry2,  rz2 ); // D

    _vertexArray << QVector3D(  rx2, -ry2, -rz2 ); // E
    _vertexArray << QVector3D( -rx2, -ry2, -rz2 ); // F
    _vertexArray << QVector3D( -rx2,  ry2, -rz2 ); // G
    _vertexArray << QVector3D(  rx2,  ry2, -rz2 ); // H

    obj.vsize += 8;

    // Append indices to compose faces

    // Front
    _indiceArray << QVector<GLuint>( { vindex + CUBE_A, vindex + CUBE_C, vindex + CUBE_D} );
    _indiceArray << QVector<GLuint>( { vindex + CUBE_A, vindex + CUBE_B, vindex + CUBE_C} );
    obj.isize += 2 * 3;

    // Back
    _indiceArray << QVector<GLuint>( { vindex + CUBE_E, vindex + CUBE_G, vindex + CUBE_H} );
    _indiceArray << QVector<GLuint>( { vindex + CUBE_E, vindex + CUBE_F, vindex + CUBE_G} );
    obj.isize += 2 * 3;

    // Top
    _indiceArray << QVector<GLuint>( { vindex + CUBE_D, vindex + CUBE_H, vindex + CUBE_G} );
    _indiceArray << QVector<GLuint>( { vindex + CUBE_D, vindex + CUBE_C, vindex + CUBE_H} );
    obj.isize += 2 * 3;

    // Bottom
    _indiceArray << QVector<GLuint>( { vindex + CUBE_F, vindex + CUBE_B, vindex + CUBE_A} );
    _indiceArray << QVector<GLuint>( { vindex + CUBE_F, vindex + CUBE_E, vindex + CUBE_B} );
    obj.isize += 2 * 3;

    // Left
    _indiceArray << QVector<GLuint>( { vindex + CUBE_B, vindex + CUBE_H, vindex + CUBE_C} );
    _indiceArray << QVector<GLuint>( { vindex + CUBE_B, vindex + CUBE_E, vindex + CUBE_H} );
    obj.isize += 2 * 3;

    // Right
    _indiceArray << QVector<GLuint>( { vindex + CUBE_F, vindex + CUBE_D, vindex + CUBE_G} );
    _indiceArray << QVector<GLuint>( { vindex + CUBE_F, vindex + CUBE_A, vindex + CUBE_D} );
    obj.isize += 2 * 3;
}

/* ============================================================================
 *
 * */
void VertexBufferObject::createArrow( qreal radius, qreal height, GLuint slices, ObjBufferConfig& obj )
{
    const qreal r_cylinder = radius * (3.0f/4.0f);
    const qreal h_cylinder = height * (4.0f/5.0f);
    const qreal h_cone     = height - h_cylinder;

    createCylinder( r_cylinder, h_cylinder, slices, obj );
    translate     ( QVector3D(0, 0, -(h_cylinder/2)-(h_cone/2) ), obj );
    createCone( radius, h_cone, slices, obj );
    translate     ( QVector3D(0, 0, +(h_cylinder)+(h_cone/2) ), obj );
}

/* ============================================================================
 *
 * */
void VertexBufferObject::createBase( ObjBufferConfig& obj )
{
    qreal radius = 0.25;
    qreal height = 3;
    GLuint slices= 10;


    // Y
    createArrow( radius, height, slices, obj );

    //rotate( QVector3D(1,0,0), -(BUFFER_PI/2), obj );

    // X
    //createArrow( radius, height, slices, obj );

    // rotate( QVector3D(0,1,0), BUFFER_PI/2, obj );

    // // Z
    // createArrow( radius, height, slices, obj );

}


/* ============================================================================
 *
 * */
void VertexBufferObject::translate( QVector3D translation, ObjBufferConfig& obj )
{
    for(unsigned int v=obj.vindex ; v<obj.vsize ; v++)
    {
        _vertexArray[v] += translation;
    }
}

/* ============================================================================
 *
 * */
void VertexBufferObject::rotate( QVector3D axe, qreal angle, ObjBufferConfig& obj )
{
    const qreal a   = axe.x() ;
    const qreal b   = axe.y() ;
    const qreal c   = axe.z() ;

    const qreal cosa = qCos(angle) ;
    const qreal sina = qSin(angle) ;
    
    QMatrix4x4 rotation(
        (a*a) + (1-a*a) * cosa
    ,   (a*b) * (1-cosa) - c * sina
    ,   (a*c) * (1-cosa) - b * sina
    ,   (0)

    ,   (a*b) * (1-cosa) + c * sina
    ,   (b*b) + (1-b*b) * cosa
    ,   (b*c) * (1-cosa) - a * sina
    ,   (0)

    ,   (a*c) * (1-cosa) - b * sina
    ,   (b*c) * (1-cosa) + a * sina
    ,   (c*c) + (1-c*c) * cosa 
    ,   (0)

    ,   (0)
    ,   (0) 
    ,   (0) 
    ,   (1)
    );

    for(unsigned int v=obj.vindex ; v<obj.vsize ; v++)
    {
        QVector4D vec4 = _vertexArray[v].toVector4D();
        QVector4D res  = rotation * vec4;
        _vertexArray[v]= res.toVector3D();   
    }
}
