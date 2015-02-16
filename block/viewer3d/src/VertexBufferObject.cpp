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
// void VertexBufferObject::createArrow( qreal radius, qreal height, GLuint slices, ObjBufferConfig& obj )
// {
//     const qreal r_cylinder = radius * (3.0f/4.0f);
//     const qreal h_cylinder = height * (4.0f/5.0f);
//     const qreal h_cone     = height - h_cylinder;

//     createCylinder( r_cylinder, h_cylinder, slices, obj );
//     translate     ( QVector3D(0, 0, -(h_cylinder/2)-(h_cone/2) ), obj );
//     createCone( radius, h_cone, slices, obj );
//     translate     ( QVector3D(0, 0, +(h_cylinder)+(h_cone/2) ), obj );
// }

/* ============================================================================
 *
 * */
void VertexBufferObject::createBase( ObjBufferConfig& obj )
{
    qreal radius = 0.25;
    qreal height = 3;
    GLuint slices= 10;


    // Y
    //createArrow( radius, height, slices, obj );

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
