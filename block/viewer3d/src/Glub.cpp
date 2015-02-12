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
 * */
void Glub::Cuboid(
    qreal rx, qreal ry, qreal rz,
    QVector<QVector3D>& vertexArray, QVector<GLuint>& indiceArray, BufferParam& param)
{
    // Set buffer param
    const GLuint index = param.index;

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
    indiceArray << QVector<GLuint>( { index + A, index + C, index + D} );
    indiceArray << QVector<GLuint>( { index + A, index + B, index + C} );
    param.size += 2 * 3;

    // Back
    indiceArray << QVector<GLuint>( { index + E, index + G, index + H} );
    indiceArray << QVector<GLuint>( { index + E, index + F, index + G} );
    param.size += 2 * 3;

    // Top
    indiceArray << QVector<GLuint>( { index + D, index + H, index + G} );
    indiceArray << QVector<GLuint>( { index + D, index + C, index + H} );
    param.size += 2 * 3;

    // Bottom
    indiceArray << QVector<GLuint>( { index + F, index + B, index + A} );
    indiceArray << QVector<GLuint>( { index + F, index + E, index + B} );
    param.size += 2 * 3;

    // Left
    indiceArray << QVector<GLuint>( { index + B, index + H, index + C} );
    indiceArray << QVector<GLuint>( { index + B, index + E, index + H} );
    param.size += 2 * 3;

    // Right
    indiceArray << QVector<GLuint>( { index + F, index + D, index + G} );
    indiceArray << QVector<GLuint>( { index + F, index + A, index + D} );
    param.size += 2 * 3;
}

/* ============================================================================
 *
 * */
void Glub::Sphere(
    qreal radius, GLuint slices,
    QVector<QVector3D>& vertexArray, QVector<GLuint>& indiceArray, BufferParam& param)
{
    // Set buffer param
    const GLuint index = param.index;


    // Compute const
    const qreal step = (M_PI * 2) / slices;

    // Compute slices
    for(GLuint i=0 ; i<slices ; i++)
    {
        const qreal tetaxy = step * i;
        for(GLuint j=0 ; j<slices ; j++)
        {
            const qreal tetaxz = step * i;

            // Compute coordonates
            const qreal x = radius * qCos(tetaxz) * qSin(tetaxy);
            const qreal y = radius * qSin(tetaxz);  
            const qreal z = radius * qCos(tetaxz) * qCos(tetaxy);

            vertexArray << QVector3D(x, y, z);
        }
    }


    auto indexfunc = [slices](GLuint i, GLuint j) {
            return ( i*slices + j );
        };


        std::cout << indexfunc(1,0)  << std::endl;


    for(GLuint i=0 ; i<slices ; i++)
    {
    
        for(GLuint j=0 ; j<slices ; j++)
        {

            indiceArray << QVector<GLuint>( { indexfunc(i, j), indexfunc(i, j+1), indexfunc(i+1, j+1) } );

            indiceArray << QVector<GLuint>( { indexfunc(i+1, j), indexfunc(i, j), indexfunc(i+1, j+1) } );

            param.size += 6;

        }
    }


}

/* ============================================================================
 *
 * */
void Glub::Cylinder(
    qreal radius, qreal height, GLuint slices,
    QVector<QVector3D>& vertexArray, QVector<GLuint>& indiceArray, BufferParam& param)
{
    // Set buffer param
    const GLuint index  = param.index;
    const GLuint vindex = vertexArray.size();

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

        const GLuint p1 = index + 2 + tmp; // i + 1
        const GLuint p2 = index + 2 + i;   // i

        indiceArray << QVector<GLuint>( {p1, p2, 0} );
    }

    // Index for top circle
    for(GLuint i=0 ; i<slices ; i++)
    {
        GLuint tmp = i+1;
        if( tmp >= slices ) { tmp -= slices; }

        const GLuint p1 = index + 2 + slices + tmp; // i + 1
        const GLuint p2 = index + 2 + slices + i;   // i

        indiceArray << QVector<GLuint>( {p1, p2, 1} );
    }

    // Index for body
    for(GLuint i=0 ; i<slices ; i++)
    {
        GLuint tmp = i+1;
        if( tmp >= slices ) { tmp -= slices; }

        const GLuint p01 = index + 2 + tmp; // i + 1
        const GLuint p02 = index + 2 + i;   // i

        const GLuint p11 = index + 2 + slices + tmp; // i + 1
        const GLuint p12 = index + 2 + slices + i;   // i

        indiceArray << QVector<GLuint>( {p12, p02, p01}  );
        indiceArray << QVector<GLuint>( {p12, p01, p11 } );
    }
}




/* ============================================================================
 *
 * */
void Glub::Cone(
    qreal radius, qreal height, GLuint slices,
    QVector<QVector3D>& vertexArray, QVector<GLuint>& indiceArray, BufferParam& param)
{
    // Set buffer param
    const GLuint index  = param.index;
    const GLuint vindex = vertexArray.size();

   
    param.size += 2 * slices;   // nb triangles for top, bot circle and body
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
    
        std::cout << " truc 1 ::: " << vertexArray.size() << std::endl;


    // Append points of the top circle
    for(GLuint i=0 ; i<slices ; i++)
    { 
        QVector3D topPoint(vertexArray.at(vindex + 2 + i));
        topPoint.setZ(height2);
        vertexArray << topPoint;
    }


        std::cout << " truc 2" << std::endl;


    // Index for bot circle
    for(GLuint i=0 ; i<slices ; i++)
    {
        GLuint tmp = i+1;
        if( tmp >= slices ) { tmp -= slices; }

        const GLuint p1 = index + 2 + tmp; // i + 1
        const GLuint p2 = index + 2 + i;   // i

        indiceArray << QVector<GLuint>( {p1, p2, 0} );
    }

        std::cout << " truc3 " << std::endl;

    // Index for body
    for(GLuint i=0 ; i<slices ; i++)
    {
        GLuint tmp = i+1;
        if( tmp >= slices ) { tmp -= slices; }

        const GLuint p1 = index + 2 + tmp; // i + 1
        const GLuint p2 = index + 2 + i;   // i

        indiceArray << QVector<GLuint>( {p1, p2, 1} );
    }


        std::cout << " truc 4" << std::endl;

}




/* ============================================================================
 *
 * */
void Glub::Arrow(
    qreal radius, qreal height, GLuint slices,
    QVector<QVector3D>& vertexArray, QVector<GLuint>& indiceArray, BufferParam& param)
{
    param.index = 0;
    param.size  = 0;

    Cylinder( radius, height, slices, vertexArray, indiceArray, param );

    std::cout << param.index << " - " << param.size << std::endl;

    param.index = param.size-1;

    Cone    ( radius, height, slices, vertexArray, indiceArray, param );


    std::cout << param.index << " - " << param.size << std::endl;

    param.index = 0;

    std::cout << param.index << " - " << param.size << std::endl;


}