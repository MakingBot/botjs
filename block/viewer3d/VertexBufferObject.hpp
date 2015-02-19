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

#include <iostream>

#include <QGLBuffer>
#include <ShapeData.hpp>

class Viewer;

//!
//! Provide parameter that define a vbo sector
//!
class VboSector
{
public:
    //! Default constructor
    VboSector(unsigned int index = 0, unsigned int size = 0) : iindex(index), isize(size) { }

    //! Index of the first object indice in the VBO 
    unsigned int iindex;

    //! Number of indice to compose the object
    unsigned int isize;
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

        // Bind vertex buffer
        _normalBuffer.bind();
        glNormalPointer(GL_FLOAT, 0, NULL);
        _normalBuffer.release();

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
        _indiceArray.clear();
        _vertexArray.clear();
        _normalArray.clear();
    }

    //!
    //! Write array data in buffers
    //!
    void write()
    {
        // Write indice data in indice buffer
        _indiceBuffer.bind();
        _indiceBuffer.write(0, _indiceArray.constData(), _indiceArray.size()  * sizeof(GLuint));
        _indiceBuffer.release();

        // Write vertex data in vertex buffer
        _vertexBuffer.bind();
        _vertexBuffer.write(0, _vertexArray.constData(), _vertexArray.size() * sizeof(QVector3D));
        _vertexBuffer.release();

        _normalBuffer.bind();
        _normalBuffer.write(0, _normalArray.constData(), _normalArray.size() * sizeof(QVector3D));
        _normalBuffer.release();        
    }





    VboSector append(const ShapeData& data)
    {
        // Get sector indices before merge arrays
        const unsigned int vertex_array_size = _vertexArray.size();
        VboSector sector(_indiceArray.size(), data.indiceArray().size());
        
        // Append arrays
        _indiceArray << data.indiceArray();
        _vertexArray << data.vertexArray();
        _normalArray << data.normalArray();

        // Adjust indice in the vbo
        for( unsigned int i=sector.iindex ; i<sector.isize ; i++ )
        {
            _indiceArray[i] += vertex_array_size;
        }

        std::cout << sector.iindex << "   " << sector.isize << " == " << _indiceArray.size() <<  std::endl;


        // Return the sector
        return sector;
    }



protected:

    //! Reference on the viewer
    Viewer&                     _viewer;

    //! Arrays to store vertices indices
    QVector<GLuint>             _indiceArray;

    //! Array to store vertices that will be rendered
    QVector<QVector3D>          _vertexArray;

    //! Arrays to store normal vectors
    QVector<QVector3D>          _normalArray;

    //! Indice buffer
    QGLBuffer                   _indiceBuffer;

    //! Vertex buffer
    QGLBuffer                   _vertexBuffer;

    //! Normal buffer
    QGLBuffer                   _normalBuffer;

    //! Maximum size of the vertex buffer 
    unsigned int                _vertexBufferMaxSize;

    //! Maximum size of the indice buffer
    unsigned int                _indiceBufferMaxSize;
    
};


#endif // VERTEXBUFFEROBJECT_HPP
