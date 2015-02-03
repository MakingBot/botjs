#include <Glub.hpp>






/* ============================================================================
 *
 * */
void Glub::Cylinder(
    qreal radius, qreal height, GLuint slices,
    QVector<QVector3D>& vertexArray, QVector<GLuint>& indiceArray, BufferParam& param)
{
    // Set buffer param
    const GLuint index = param.index;
    param.size = 2 + 5 * slices;
    
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
        indiceArray << QVector<GLuint>( {2+i+1, 2+i, 0} );
    }

    // Index for top circle
    for(GLuint i=0 ; i<slices ; i++)
    { 
        indiceArray << QVector<GLuint>( {2+slices+i, 2+slices+i+1, 1} );
    }

    // Index for around
    for(GLuint i=0 ; i<slices ; i++)
    {
        indiceArray << QVector<GLuint>( {2+slices+i, 2+i, 2+i+1} );
        indiceArray << QVector<GLuint>( {2+slices+i, 2+i+1, 2+slices+i+1 } );
    }
}
