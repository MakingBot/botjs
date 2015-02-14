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
    VertexBufferObject();

    //!
    //! Subdivide triangle of the sphere approximation 
    //!
    void subdivide( QVector3D p1, QVector3D p2, QVector3D p3, qreal radius, ObjBufferConfig& obj, int depth );

    //!
    //! Function to generate a sphere
    //!
    void createSphere( qreal radius, GLuint slices, ObjBufferConfig& obj );


protected:

    //! Array to store vertices that will be rendered
    QVector<QVector3D>          _vertexArray;

    //! Arrays to store vertices indices
    QVector<GLuint>             _indiceArray;

    //! Vertex buffer
    QGLBuffer                   _vertexBuffer;

    //! Indice buffer
    QGLBuffer                   _indiceBuffer;

};


#endif // VERTEXBUFFEROBJECT_HPP
