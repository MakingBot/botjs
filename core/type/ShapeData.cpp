//!
//! \file ShapeData.cpp
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

#include <QtMath>
#include <ShapeData.hpp>

/* ============================================================================
 *
 * */
void ShapeData::subdivide( QVector3D p1, QVector3D p2, QVector3D p3, qreal radius, int depth )
{
    if(depth <= 0)
    {
        const unsigned int vindex = _vertexArray.size();

        // Append indices
        _indiceArray << QVector<unsigned int>( { vindex + 0, vindex + 1, vindex + 2} );
        
        // Append vertices
        _vertexArray << p1 << p2 << p3;

        // Append normals
        _normalArray << p1.normalized() << p2.normalized() << p3.normalized();
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

        subdivide( p1 , p12, p31, radius, depth-1 );
        subdivide( p12, p2 , p23, radius, depth-1 );
        subdivide( p12, p23, p31, radius, depth-1 );
        subdivide( p31, p23, p3 , radius, depth-1 );
    }
}

/* ============================================================================
 *
 * */
void ShapeData::createSphere( qreal radius, unsigned int subdiv )
{
    // Compute initial points
    QVector3D pA(  radius,  0     ,  0     );
    QVector3D pB(  0     ,  radius,  0     );
    QVector3D pC( -radius,  0     ,  0     );
    QVector3D pD(  0     , -radius,  0     );

    QVector3D pE(  0     ,  0     ,  radius);
    QVector3D pF(  0     ,  0     , -radius);

    // sub
    subdivide( pE, pA, pB, radius, subdiv );
    subdivide( pE, pB, pC, radius, subdiv );
    subdivide( pD, pE, pC, radius, subdiv );
    subdivide( pD, pA, pE, radius, subdiv );

    subdivide( pF, pA, pB, radius, subdiv );
    subdivide( pF, pB, pC, radius, subdiv );
    subdivide( pD, pF, pC, radius, subdiv );
    subdivide( pD, pA, pF, radius, subdiv );
}

/* ============================================================================
 *
 * */
void ShapeData::createCylinder( qreal radius, qreal height, unsigned int slices )
{
    // Set buffer param
    const unsigned int vindex = _vertexArray.size();

    // Compute const
    const qreal height2 = height/2;
    const qreal step = (M_PI * 2) / slices;
    
    // Append center bot and top
    _vertexArray << QVector3D(0, 0, -height2); // bot 0
    _vertexArray << QVector3D(0, 0,  height2); // top 1
    
    // Append points of the bot circle
    for(unsigned int i=0 ; i<slices ; i++)
    {
        const qreal angle = step * i;
        const qreal sina  = qSin(angle); 
        const qreal cosa  = qCos(angle);
        
        _vertexArray << QVector3D( cosa*radius, sina*radius, -height2 );
    }

    // Append points of the top circle
    for(unsigned int i=0 ; i<slices ; i++)
    { 
        QVector3D topPoint(_vertexArray.at(vindex + 2 + i));
        topPoint.setZ(height2);
        _vertexArray << topPoint;
    }

    // Index for bot circle
    for(unsigned int i=0 ; i<slices ; i++)
    {
        unsigned int tmp = i+1;
        if( tmp >= slices ) { tmp -= slices; }

        const unsigned int p1 = vindex + 2 + tmp; // i + 1
        const unsigned int p2 = vindex + 2 + i;   // i

        _indiceArray << QVector<unsigned int>( {p1, p2, vindex+0} );
    }

    // Index for top circle
    for(unsigned int i=0 ; i<slices ; i++)
    {
        unsigned int tmp = i+1;
        if( tmp >= slices ) { tmp -= slices; }

        const unsigned int p1 = vindex + 2 + slices + tmp; // i + 1
        const unsigned int p2 = vindex + 2 + slices + i;   // i

        _indiceArray << QVector<unsigned int>( {p1, p2, vindex+1} );
    }

    // Index for body
    for(unsigned int i=0 ; i<slices ; i++)
    {
        unsigned int tmp = i+1;
        if( tmp >= slices ) { tmp -= slices; }

        const unsigned int p01 = vindex + 2 + tmp; // i + 1
        const unsigned int p02 = vindex + 2 + i;   // i

        const unsigned int p11 = vindex + 2 + slices + tmp; // i + 1
        const unsigned int p12 = vindex + 2 + slices + i;   // i

        _indiceArray << QVector<unsigned int>( {p12, p02, p01}  );
        _indiceArray << QVector<unsigned int>( {p12, p01, p11 } );
    }
}

/* ============================================================================
 *
 * */
void ShapeData::createCone( qreal radius, qreal height, unsigned int slices )
{
    // Set buffer param
    const unsigned int vindex = _vertexArray.size();

    // Compute const
    const qreal height2 = height / 2;
    const qreal step = (M_PI * 2) / slices;
    
    // Append center bot and top
    _vertexArray << QVector3D(0, 0, -height2); // bot 0
    _vertexArray << QVector3D(0, 0,  height2); // top 1
    
    // Append points of the bot circle
    for(unsigned int i=0 ; i<slices ; i++)
    {
        const qreal angle = step * i;
        const qreal sina  = qSin(angle);
        const qreal cosa  = qCos(angle);
        
        _vertexArray << QVector3D( cosa*radius, sina*radius, -height2 );
    }

    // Append points of the top circle
    for(unsigned int i=0 ; i<slices ; i++)
    { 
        QVector3D topPoint(_vertexArray.at(vindex + 2 + i));
        topPoint.setZ(height2);
        _vertexArray << topPoint;
    }

    // Index for bot circle
    for(unsigned int i=0 ; i<slices ; i++)
    {
        unsigned int tmp = i+1;
        if( tmp >= slices ) { tmp -= slices; }

        const unsigned int p1 = vindex + 2 + tmp; // i + 1
        const unsigned int p2 = vindex + 2 + i;   // i

        _indiceArray << QVector<unsigned int>( {p1, p2, vindex+0} );
    }

    // Index for body
    for(unsigned int i=0 ; i<slices ; i++)
    {
        unsigned int tmp = i+1;
        if( tmp >= slices ) { tmp -= slices; }

        const unsigned int p1 = vindex + 2 + tmp; // i + 1
        const unsigned int p2 = vindex + 2 + i;   // i

        _indiceArray << QVector<unsigned int>( {p1, p2, vindex+1} );
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

void ShapeData::createCuboid( qreal rx, qreal ry, qreal rz )
{
    // Set buffer param
    const unsigned int vindex = _vertexArray.size();

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

    // Append indices to compose faces

    // Front
    _indiceArray << QVector<unsigned int>( { vindex + CUBE_A, vindex + CUBE_C, vindex + CUBE_D } );
    _indiceArray << QVector<unsigned int>( { vindex + CUBE_A, vindex + CUBE_B, vindex + CUBE_C } );

    // Back
    _indiceArray << QVector<unsigned int>( { vindex + CUBE_E, vindex + CUBE_G, vindex + CUBE_H } );
    _indiceArray << QVector<unsigned int>( { vindex + CUBE_E, vindex + CUBE_F, vindex + CUBE_G } );

    // Top
    _indiceArray << QVector<unsigned int>( { vindex + CUBE_D, vindex + CUBE_H, vindex + CUBE_G } );
    _indiceArray << QVector<unsigned int>( { vindex + CUBE_D, vindex + CUBE_C, vindex + CUBE_H } );

    // Bottom
    _indiceArray << QVector<unsigned int>( { vindex + CUBE_F, vindex + CUBE_B, vindex + CUBE_A } );
    _indiceArray << QVector<unsigned int>( { vindex + CUBE_F, vindex + CUBE_E, vindex + CUBE_B } );

    // Left
    _indiceArray << QVector<unsigned int>( { vindex + CUBE_B, vindex + CUBE_H, vindex + CUBE_C } );
    _indiceArray << QVector<unsigned int>( { vindex + CUBE_B, vindex + CUBE_E, vindex + CUBE_H } );

    // Right
    _indiceArray << QVector<unsigned int>( { vindex + CUBE_F, vindex + CUBE_D, vindex + CUBE_G } );
    _indiceArray << QVector<unsigned int>( { vindex + CUBE_F, vindex + CUBE_A, vindex + CUBE_D } );
}
