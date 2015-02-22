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
    , _indiceBuffer (QGLBuffer::IndexBuffer )
    , _vertexBuffer (QGLBuffer::VertexBuffer)
    , _normalBuffer (QGLBuffer::VertexBuffer)
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


    _normalBuffer.create();
    _normalBuffer.bind();
    _normalBuffer.setUsagePattern(QGLBuffer::DynamicDraw);
    _normalBuffer.allocate(300000 * sizeof(QVector3D    ));
    _normalBuffer.release();



    _viewer.doneCurrent();

}







/* ============================================================================
 *
 * *
void VertexBufferObject::translate( QVector3D translation, ObjBufferConfig& obj )
{
    for(unsigned int v=obj.vindex ; v<obj.vsize ; v++)
    {
        _vertexArray[v] += translation;
    }
}
*/
/* ============================================================================
 *
 * *
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
//*/
