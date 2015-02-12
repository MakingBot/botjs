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
 * */
void Glub::Sphere(
    qreal radius, GLuint slices,
    QVector<QVector3D>& vertexArray, QVector<GLuint>& indiceArray, BufferParam& param)
{
    // Set buffer param
    const GLuint index = param.index;

    // Compute const
    const qreal stepxz = (M_PI * 2) /  slices    ; // Angle on 360 deg
    const qreal stepxy = (M_PI    ) / (slices/2) ; // Angle on 180 deg

    std::cout << stepxz << std::endl;
    std::cout << stepxy << std::endl;

    // Compute slices
    for(GLuint i=0 ; i<slices ; i++)
    {
        const qreal tetaxz = stepxz * i;

        for(GLuint j=0 ; j<slices/2 ; j++)
        {
            const qreal tetaxy = stepxy * i;

            // Compute coordonates
            const qreal x = radius * qCos(tetaxy) * qSin(tetaxz);
            const qreal y = radius * qSin(tetaxy);  
            const qreal z = radius * qCos(tetaxy) * qCos(tetaxz);

            QVector3D point(x, y, z);

            vertexArray << point;

            std::cout << point.x() << " - " << point.y() << " - " << point.z() << " - " << std::endl;
        }
    }

    // Index function
    auto indexfunc = [slices](GLuint i, GLuint j) { return ( i * (slices/2) + j ); };


    indiceArray << QVector<GLuint>( { indexfunc(0, 0), indexfunc(0, 0), indexfunc(0, 0) } );
    param.size += 3;

    // // 
    // for(GLuint i=0 ; i<slices ; i++)
    // {    
    //     for(GLuint j=0 ; j<slices/2 ; j++)
    //     {

    //         indiceArray << QVector<GLuint>( { indexfunc(i, j), indexfunc(i, j+1), indexfunc(i+1, j+1) } );

    //         //indiceArray << QVector<GLuint>( { indexfunc(i+1, j), indexfunc(i, j), indexfunc(i+1, j+1) } );

    //         param.size += 6;

    //     }
    // }


}

/* ============================================================================
 *
 * */
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
 * */
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
 * */
void Glub::Arrow(
    qreal radius, qreal height, GLuint slices,
    QVector<QVector3D>& vertexArray, QVector<GLuint>& indiceArray, BufferParam& param)
{
    param.index = 0;
    param.size  = 0;

    Cylinder( radius, height, slices, vertexArray, indiceArray, param );


    Cone    ( radius, height, slices, vertexArray, indiceArray, param );

}