#ifndef SHAPEDATA_HPP
#define SHAPEDATA_HPP
//!
//! \file ShapeData.hpp
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

#include <QVector>
#include <QVector3D>

//!
//! This class provide array to store 3D shape data
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class ShapeData
{

public:
    //!
    //! Default constructor
    //!
    ShapeData() { };

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
    //! Merge 2 shape data
    //!
    void merge(const ShapeData& data)
    {

    }

    // ========================================================================
    // => Basic array getter

    //!
    //! Indice array getter
    //!
    const QVector<unsigned int>&    indiceArray() const { return _indiceArray; }

    //!
    //! Vertex array getter
    //!
    const QVector<QVector3D>&       vertexArray() const { return _vertexArray; }

    //!
    //! Normal array getter
    //!
    const QVector<QVector3D>&       normalArray() const { return _normalArray; }

    // ========================================================================
    // => Functions to transform shapes

    //!
    //! Function to translation vertex of an object
    //!
    void translate( QVector3D translation );

    //!
    //! Function to rotate vertex of an object
    //!
    void rotate( QVector3D axe, qreal angle );

    // ========================================================================
    // => Functions to generate shapes

    //!
    //! Subdivide triangle of the sphere approximation 
    //!
    void subdivide      ( QVector3D p1, QVector3D p2, QVector3D p3, qreal radius, int depth );

    //!
    //! Function to generate a sphere
    //!
    void createSphere   ( qreal radius, unsigned int subdiv );

    //!
    //! Function to generate a cylinder
    //!
    // void createCylinder ( qreal radius, qreal height, GLuint slices );

    //!
    //! Function to generate a cone
    //!
    // void createCone     ( qreal radius, qreal height, GLuint slices );

    //!
    //! Function to generate a cuboid
    //!
    // void createCuboid   ( qreal rx, qreal ry, qreal rz );

    //!
    //! Function to generate an arrow
    //!
    // void createArrow    ( qreal radius, qreal height, GLuint slices );


    // void createBase     ( );

protected:

    //! Arrays to store vertices indices
    QVector<unsigned int>       _indiceArray;

    //! Array to store vertices that will be rendered
    QVector<QVector3D>          _vertexArray;

    //! Arrays to store normal vectors
    QVector<QVector3D>          _normalArray;

};



#endif // SHAPEDATA_HPP