#ifndef GLUB_HPP
#define GLUB_HPP

#define _USE_MATH_DEFINES
#include <math.h>
#include <QtCore/qmath.h>

#include <glu.h>
#include <QVector3D>
#include <QMatrix4x4>

//! Buffer helper
#define GLUB_BUFFER_OFFSET(i) ((void*)(i))

//!
//! Provide parameter structure to draw a previous stored vbo object
//!
class BufferParam
{
public:
    BufferParam(GLuint i=0, GLuint nb=1) : index(i), nbElement(nb) { }
    GLuint index;
    GLuint nbElement;
};

//!
//! Custom clone of glu functions
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class Glub
{

public:

    //!
    //! Compute vertex and indice to draw a cylinder on axe Z
    //!
    void Cylinder(
        qreal radius, qreal height, GLuint slices,
        QVector<QVector3D>& vertexArray, QVector<GLuint>& indiceArray, BufferParam& param);

};

#endif // GLUB_HPP
