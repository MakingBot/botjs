#ifndef GLUB_HPP
#define GLUB_HPP

#define _USE_MATH_DEFINES
#include <math.h>
#include <QtCore/qmath.h>

#include <glu.h>
#include <QVector3D>
#include <QMatrix4x4>

#include <VertexBufferObject.hpp>

//! Buffer helper
#define GLUB_BUFFER_OFFSET(i) ((void*)(i*sizeof(GLuint)))



//!
//! Custom clone of glu functions
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class Glub
{

public:
/*
    static void Cuboid(
        qreal rx, qreal ry, qreal rz,
        QVector<QVector3D>& vertexArray, QVector<GLuint>& indiceArray, BufferParam& param);

    static void Sphere(
        qreal radius, GLuint slices,
        QVector<QVector3D>& vertexArray, QVector<GLuint>& indiceArray, BufferParam& param);

    //!
    //! Compute vertex and indice to draw a cylinder on axe Z
    //!
    static void Cylinder(
        qreal radius, qreal height, GLuint slices,
        QVector<QVector3D>& vertexArray, QVector<GLuint>& indiceArray, BufferParam& param);


    static void Cone(
        qreal radius, qreal height, GLuint slices,
        QVector<QVector3D>& vertexArray, QVector<GLuint>& indiceArray, BufferParam& param);

    static void Arrow(
        qreal radius, qreal height, GLuint slices,
        QVector<QVector3D>& vertexArray, QVector<GLuint>& indiceArray, BufferParam& param);
*/
};

#endif // GLUB_HPP
