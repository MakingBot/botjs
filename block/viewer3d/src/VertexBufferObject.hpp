#ifndef VERTEXBUFFEROBJECT_HPP
#define VERTEXBUFFEROBJECT_HPP
//!
//! \file VertexBufferObject.hpp
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

#include <QGLBuffer>
#include <QVector3D>

class Viewer;

//!
//! Provide parameter structure to draw a previous stored vbo object
//!
class ObjBufferConfig
{
public:
    //! Default constructor
    ObjBufferConfig() : iindex(0), isize(0), vindex(0), vsize(0) { }

    //! Index of the first object indice in the VBO 
    unsigned int iindex;

    //! Number of indice to compose the object
    unsigned int isize;

    //! Index of the first object vertex in the VBO 
    unsigned int vindex;

    //! Number of vertice to compose the object
    unsigned int vsize;
};

//!
//! Contain VBO configuration
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class VertexBufferObject
{

public:
    //!
    //! Default constructor
    //!
    VertexBufferObject(Viewer& viewer);

    //!
    //! Bind buffers
    //!
    void bind()
    {
        // Bind vertex buffer
        _vertexBuffer.bind();
        glVertexPointer(3, GL_FLOAT, 0, NULL);
        _vertexBuffer.release();

        // Bind indice buffer
        _indiceBuffer.bind();
    }

    //!
    //! Release buffers
    //!
    void release()
    {
        // Release indice buffer
        _indiceBuffer.release();
    }

    //!
    //! Reset array
    //!
    void reset()
    {
        

        _vertexArray.clear();
        _indiceArray.clear();
    }

    //!
    //! Write array data in buffers
    //!
    void write()
    {
        // Write vertex data in vertex buffer
        _vertexBuffer.bind();
        _vertexBuffer.write(0, _vertexArray.constData(), _vertexArray.size() * sizeof(QVector3D));
        _vertexBuffer.release();

        // Write indice data in indice buffer
        _indiceBuffer.bind();
        _indiceBuffer.write(0, _indiceArray.constData(), _indiceArray.size()  * sizeof(GLuint));
        _indiceBuffer.release();
    }

    //!
    //! Initialize object
    //!
    void ini(ObjBufferConfig& obj);

    //!
    //! Subdivide triangle of the sphere approximation 
    //!
    void subdivide( QVector3D p1, QVector3D p2, QVector3D p3, qreal radius, ObjBufferConfig& obj, int depth );

    //!
    //! Function to generate a sphere
    //!
    void createSphere( qreal radius, GLuint subdiv, ObjBufferConfig& obj );

    //!
    //! Function to generate a cylinder
    //!
    void createCylinder( qreal radius, qreal height, GLuint slices, ObjBufferConfig& obj );

    //!
    //! Function to generate a cone
    //!
    void createCone( qreal radius, qreal height, GLuint slices, ObjBufferConfig& obj );

    //!
    //! Function to generate a cuboid
    //!
    void createCuboid( qreal rx, qreal ry, qreal rz, ObjBufferConfig& obj );

    //!
    //! Function to generate an arrow
    //!
    void createArrow( qreal radius, qreal height, GLuint slices, ObjBufferConfig& obj );


    void createBase( ObjBufferConfig& obj );

    //!
    //! Function to translation vertex of an object
    //!
    void translate( QVector3D translation, ObjBufferConfig& obj );

    //!
    //! Function to rotate vertex of an object
    //!
    void rotate( QVector3D axe, qreal angle, ObjBufferConfig& obj );

protected:

    //! Reference on the viewer
    Viewer&                     _viewer;

    //! Array to store vertices that will be rendered
    QVector<QVector3D>          _vertexArray;

    //! Arrays to store vertices indices
    QVector<GLuint>             _indiceArray;

    //! Vertex buffer
    QGLBuffer                   _vertexBuffer;

    //! Indice buffer
    QGLBuffer                   _indiceBuffer;

    //! Maximum size of the vertex buffer 
    unsigned int                _vertexBufferMaxSize;

    //! Maximum size of the indice buffer
    unsigned int                _indiceBufferMaxSize;
    
};


#endif // VERTEXBUFFEROBJECT_HPP
