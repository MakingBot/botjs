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
//! Contain VBO configuration
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class VertexBufferObject
{

public:



protected:

    //! Array to store all vertex that will be rendered
    QVector<QVector3D>          _vertexArray;

    //! Arrays to store vertex indices
    QVector<GLuint>             _indiceArray;

    //! Vertex buffer
    QGLBuffer                   _vertexBuffer;

    //! Indice buffer
    QGLBuffer                   _indiceBuffer;

};


#endif // VERTEXBUFFEROBJECT_HPP
