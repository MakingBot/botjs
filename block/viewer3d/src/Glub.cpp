#include <Glub.hpp>


#include <iostream>

#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define H 7



/* ============================================================================
 * Y                        Y
 *
 * D ----- C        H ----- G
 *
 * 
 * A ----- B  X  X  E ----- F
 *
 * Front Z to us Back Z to the screen
 * *
void Glub::Cuboid(
    qreal rx, qreal ry, qreal rz,
    QVector<QVector3D>& vertexArray, QVector<GLuint>& indiceArray, BufferParam& param)
{
    // Set buffer param
    const GLuint vindex = vertexArray.size();

    // Compute const
    const qreal rx2 = rx / 2;
    const qreal ry2 = ry / 2;
    const qreal rz2 = rz / 2;


    // Append 8 points
    vertexArray << QVector3D( -rx2, -ry2,  rz2 ); // A
    vertexArray << QVector3D(  rx2, -ry2,  rz2 ); // B
    vertexArray << QVector3D(  rx2,  ry2,  rz2 ); // C
    vertexArray << QVector3D( -rx2,  ry2,  rz2 ); // D

    vertexArray << QVector3D(  rx2, -ry2, -rz2 ); // E
    vertexArray << QVector3D( -rx2, -ry2, -rz2 ); // F
    vertexArray << QVector3D( -rx2,  ry2, -rz2 ); // G
    vertexArray << QVector3D(  rx2,  ry2, -rz2 ); // H

    // Append indices to compose faces
    // Front
    indiceArray << QVector<GLuint>( { vindex + A, vindex + C, vindex + D} );
    indiceArray << QVector<GLuint>( { vindex + A, vindex + B, vindex + C} );
    param.size += 2 * 3;

    // Back
    indiceArray << QVector<GLuint>( { vindex + E, vindex + G, vindex + H} );
    indiceArray << QVector<GLuint>( { vindex + E, vindex + F, vindex + G} );
    param.size += 2 * 3;

    // Top
    indiceArray << QVector<GLuint>( { vindex + D, vindex + H, vindex + G} );
    indiceArray << QVector<GLuint>( { vindex + D, vindex + C, vindex + H} );
    param.size += 2 * 3;

    // Bottom
    indiceArray << QVector<GLuint>( { vindex + F, vindex + B, vindex + A} );
    indiceArray << QVector<GLuint>( { vindex + F, vindex + E, vindex + B} );
    param.size += 2 * 3;

    // Left
    indiceArray << QVector<GLuint>( { vindex + B, vindex + H, vindex + C} );
    indiceArray << QVector<GLuint>( { vindex + B, vindex + E, vindex + H} );
    param.size += 2 * 3;

    // Right
    indiceArray << QVector<GLuint>( { vindex + F, vindex + D, vindex + G} );
    indiceArray << QVector<GLuint>( { vindex + F, vindex + A, vindex + D} );
    param.size += 2 * 3;
}




/* ============================================================================
 *
 * *
void subdivide( QVector3D p1, QVector3D p2, QVector3D p3, qreal radius,
    QVector<QVector3D>& vertexArray, QVector<GLuint>& indiceArray, BufferParam& param,
    int depth)
{

    if(depth <= 0)
    {
        const GLuint vindex = vertexArray.size();

        // Append indices
        indiceArray << QVector<GLuint>( { vindex + 0, vindex + 1, vindex + 2} );
        
        // Append vertices
        vertexArray << p1 << p2 << p3;

        // Adjust the number of vertex to render
        param.size += 3;
    }
    else
    {
        auto moy = [](float n1, float n2) {  return (n1+n2)/2;  };

        QVector3D p12( moy(p1.x(), p2.x()), moy(p1.y(), p2.y()), moy(p1.z(), p2.z()) );
        p12 = p12.normalized() * radius;
        QVector3D p23( moy(p3.x(), p2.x()), moy(p3.y(), p2.y()), moy(p3.z(), p2.z()) );
        p23 = p23.normalized() * radius;
        QVector3D p31( moy(p1.x(), p3.x()), moy(p1.y(), p3.y()), moy(p1.z(), p3.z()) );
        p31 = p31.normalized() * radius;

        subdivide( p1 , p12, p31, radius, vertexArray, indiceArray, param, depth-1);
        subdivide( p12, p2 , p23, radius, vertexArray, indiceArray, param, depth-1);
        subdivide( p12, p23, p31, radius, vertexArray, indiceArray, param, depth-1);
        subdivide( p31, p23, p3 , radius, vertexArray, indiceArray, param, depth-1);
    }
}


/* ============================================================================
 *
 * *
void Glub::Sphere(
    const qreal radius, const GLuint slices,
    QVector<QVector3D>& vertexArray, QVector<GLuint>& indiceArray, BufferParam& param)
{
    // Compute initial points
    QVector3D pA(  radius,  0     ,  0     );
    QVector3D pB(  0     ,  radius,  0     );
    QVector3D pC( -radius,  0     ,  0     );
    QVector3D pD(  0     , -radius,  0     );

    QVector3D pE(  0     ,  0     ,  radius);
    QVector3D pF(  0     ,  0     , -radius);

    // sub
    subdivide( pE, pA, pB, radius, vertexArray, indiceArray, param, slices);
    subdivide( pE, pB, pC, radius, vertexArray, indiceArray, param, slices);
    subdivide( pD, pE, pC, radius, vertexArray, indiceArray, param, slices);
    subdivide( pD, pA, pE, radius, vertexArray, indiceArray, param, slices);

    subdivide( pF, pA, pB, radius, vertexArray, indiceArray, param, slices);
    subdivide( pF, pB, pC, radius, vertexArray, indiceArray, param, slices);
    subdivide( pD, pF, pC, radius, vertexArray, indiceArray, param, slices);
    subdivide( pD, pA, pF, radius, vertexArray, indiceArray, param, slices);
}

/* ============================================================================
 *
 * *
void Glub::Cylinder(
    qreal radius, qreal height, GLuint slices,
    QVector<QVector3D>& vertexArray, QVector<GLuint>& indiceArray, BufferParam& param)
{
    // Set buffer param
    const GLuint vindex = vertexArray.size();

    // Compute number of indice to append
    param.size += 4 * slices;   // nb triangles for top, bot circle and body
    param.size *= 3;            // 3 points per triangles

    // Compute const
    const qreal height2 = height/2;
    const qreal step = (M_PI * 2) / slices;
    
    // Append center bot and top
    vertexArray << QVector3D(0, 0, -height2); // bot 0
    vertexArray << QVector3D(0, 0,  height2); // top 1
    
    // Append points of the bot circle
    for(GLuint i=0 ; i<slices ; i++)
    {
        const qreal angle = step * i;
        const qreal sina  = qSin(angle); 
        const qreal cosa  = qCos(angle);
        
        vertexArray << QVector3D( cosa*radius, sina*radius, -height2 );
    }
    
    // Append points of the top circle
    for(GLuint i=0 ; i<slices ; i++)
    { 
        QVector3D topPoint(vertexArray.at(vindex + 2 + i));
        topPoint.setZ(height2);
        vertexArray << topPoint;
    }

    // Index for bot circle
    for(GLuint i=0 ; i<slices ; i++)
    {
        GLuint tmp = i+1;
        if( tmp >= slices ) { tmp -= slices; }

        const GLuint p1 = vindex + 2 + tmp; // i + 1
        const GLuint p2 = vindex + 2 + i;   // i

        indiceArray << QVector<GLuint>( {p1, p2, 0} );
    }

    // Index for top circle
    for(GLuint i=0 ; i<slices ; i++)
    {
        GLuint tmp = i+1;
        if( tmp >= slices ) { tmp -= slices; }

        const GLuint p1 = vindex + 2 + slices + tmp; // i + 1
        const GLuint p2 = vindex + 2 + slices + i;   // i

        indiceArray << QVector<GLuint>( {p1, p2, 1} );
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

        indiceArray << QVector<GLuint>( {p12, p02, p01}  );
        indiceArray << QVector<GLuint>( {p12, p01, p11 } );
    }
}




/* ============================================================================
 *
 * *
void Glub::Cone(
    qreal radius, qreal height, GLuint slices,
    QVector<QVector3D>& vertexArray, QVector<GLuint>& indiceArray, BufferParam& param)
{
    // Set buffer param
    const GLuint vindex = vertexArray.size();

    // Compute number of indice to append
    param.size += 2 * slices;   // nb triangles for top, bot circle and body
    param.size *= 3;            // 3 points per triangles

    // Compute const
    const qreal height2 = height / 2;
    const qreal step = (M_PI * 2) / slices;
    
    // Append center bot and top
    vertexArray << QVector3D(0, 0, -height2); // bot 0
    vertexArray << QVector3D(0, 0,  height2); // top 1
    
    // Append points of the bot circle
    for(GLuint i=0 ; i<slices ; i++)
    {
        const qreal angle = step * i;
        const qreal sina  = qSin(angle);
        const qreal cosa  = qCos(angle);
        
        vertexArray << QVector3D( cosa*radius, sina*radius, -height2 );
    }

    // Append points of the top circle
    for(GLuint i=0 ; i<slices ; i++)
    { 
        QVector3D topPoint(vertexArray.at(vindex + 2 + i));
        topPoint.setZ(height2);
        vertexArray << topPoint;
    }

    // Index for bot circle
    for(GLuint i=0 ; i<slices ; i++)
    {
        GLuint tmp = i+1;
        if( tmp >= slices ) { tmp -= slices; }

        const GLuint p1 = vindex + 2 + tmp; // i + 1
        const GLuint p2 = vindex + 2 + i;   // i

        indiceArray << QVector<GLuint>( {p1, p2, 0} );
    }

    // Index for body
    for(GLuint i=0 ; i<slices ; i++)
    {
        GLuint tmp = i+1;
        if( tmp >= slices ) { tmp -= slices; }

        const GLuint p1 = vindex + 2 + tmp; // i + 1
        const GLuint p2 = vindex + 2 + i;   // i

        indiceArray << QVector<GLuint>( {p1, p2, 1} );
    }

    return ;
}




/* ============================================================================
 *
 * *
void Glub::Translate( QVector3D translation, BufferParam& objparam,
    QVector<QVector3D>& vertexArray, QVector<GLuint>& indiceArray
    )
{

}


/* ============================================================================
 *
 * *
void Glub::Arrow(
    qreal radius, qreal height, GLuint slices,
    QVector<QVector3D>& vertexArray, QVector<GLuint>& indiceArray, BufferParam& param)
{
    param.index = 0;
    param.size  = 0;

    Cylinder( radius, height, slices, vertexArray, indiceArray, param );


    Cone    ( radius, height, slices, vertexArray, indiceArray, param );

}


// */
