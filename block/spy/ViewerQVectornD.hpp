#ifndef VIEWERQVECTORND_HPP
#define VIEWERQVECTORND_HPP
//!
//! \file ViewerQVectornD.hpp
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

#include <QVector2D>
#include <QVector3D>
#include <QVector4D>

#include <QLabel>
#include <QtGlobal>
#include <QDoubleSpinBox>

//!
//! To display and modify QVector2D, QVector3D or QVector4D 
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class ViewerQVectornD : public QWidget
{
    Q_OBJECT

public:

    explicit ViewerQVectornD(int n, QWidget* parent = 0);

    void setModel(const QVector2D& vec ) { if(_n == 2 ) { _vec2 = vec; updateValues(); } }
    void setModel(const QVector3D& vec ) { if(_n == 3 ) { _vec3 = vec; updateValues(); } }
    void setModel(const QVector4D& vec ) { if(_n == 4 ) { _vec4 = vec; updateValues(); } }

signals:

    void modelEdited(const QVector2D&);
    void modelEdited(const QVector3D&);
    void modelEdited(const QVector4D&);

public slots:

    void updateValues();

    void onValueChange(double d);

protected:

    //! Dimension of the widget
    int _n;

    //! Vectors data
    QVector2D _vec2;
    //! Vectors data
    QVector3D _vec3;
    //! Vectors data
    QVector4D _vec4;

    //! Box Labels
    QList<QSharedPointer<QLabel> > _labels;

    //! Widget boxes
    QList<QSharedPointer<QDoubleSpinBox> > _boxs;

};

#endif // VIEWERVECTOR_HPP
