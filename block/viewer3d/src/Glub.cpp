#include <Glub.hpp>


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
    param.size  = 0;

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
    vertexArray << QVector3D(  rx2,  ry2, -rz2 ); // G
    vertexArray << QVector3D( -rx2,  ry2, -rz2 ); // H

    // Append indices to compose faces
    // Front
    indiceArray << QVector<GLuint>( { A, C, D} );
    indiceArray << QVector<GLuint>( { A, B, C} );
    param.size += 2;

    // Back
    indiceArray << QVector<GLuint>( { E, G, H} );
    indiceArray << QVector<GLuint>( { E, F, G} );
    param.size += 2;

    // Top
    indiceArray << QVector<GLuint>( { D, H, G} );
    indiceArray << QVector<GLuint>( { D, C, D} );
    param.size += 2;

    // Bottom
    indiceArray << QVector<GLuint>( { F, B, A} );
    indiceArray << QVector<GLuint>( { F, E, B} );
    param.size += 2;

    // Left
    indiceArray << QVector<GLuint>( { B, H, C} );
    indiceArray << QVector<GLuint>( { B, E, H} );
    param.size += 2;

    // Right
    indiceArray << QVector<GLuint>( { F, D, G} );
    indiceArray << QVector<GLuint>( { F, A, D} );
    param.size += 2;
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

    param.size  = 0;

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
            const qreal x = radius * qCos(tetaxz) * qCos(tetaxy);
            const qreal y = radius * qCos(tetaxz) * qSin(tetaxy);
            const qreal z = radius * qSin(tetaxz);

            vertexArray << QVector3D(x, y, z);
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
    const GLuint index = param.index;

    param.size  = 0;
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
        QVector3D topPoint(vertexArray.at(index + 2 + i));
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

