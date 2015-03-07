#ifndef TYPE_HPP
#define TYPE_HPP
//!
//! \file Type.hpp
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

#include <QObject>

#include <QSize>
#include <QPoint>

#include <QVector2D>
#include <QVector3D>
#include <QVector4D>

//!
//! This class provide interface to create C++ type from javascript
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class Type : public QObject
{
    Q_OBJECT

public:

    Type(QObject* parent = 0) : QObject(parent) { }

public slots:

    //!
    //! To generate a vector2D from a JavaScript list
    //!
    QVector2D vector2D(QList<qreal> list)
    {
        switch(list.size())
        {
            case 0:  return QVector2D();
            case 1:  return QVector2D(list.at(0), 0         );
            default: return QVector2D(list.at(0), list.at(1));
        }
    }

    //!
    //! To generate a vector3D from a JavaScript list
    //!
    QVector3D vector3D(QList<qreal> list)
    {
        switch(list.size())
        {
            case 0:  return QVector3D();
            case 1:  return QVector3D(list.at(0), 0         , 0);
            case 2:  return QVector3D(list.at(0), list.at(1), 0);
            default: return QVector3D(list.at(0), list.at(1), list.at(2));
        }
    }

    //!
    //! To generate a vector4D from a JavaScript list
    //!
    QVector4D vector4D(QList<qreal> list)
    {
        switch(list.size())
        {
            case 0:  return QVector4D();
            case 1:  return QVector4D(list.at(0), 0         , 0         , 0);
            case 2:  return QVector4D(list.at(0), list.at(1), 0         , 0);
            case 3:  return QVector4D(list.at(0), list.at(1), list.at(2), 0);
            default: return QVector4D(list.at(0), list.at(1), list.at(2), list.at(3));
        }
    }

    //!
    //! To generate a size from a JavaScript list 
    //!
    QSize size(QList<qreal> list)
    {
        switch(list.size())
        {
            case 0:  return QSize(0         , 0         );
            case 1:  return QSize(list.at(0), 0         );
            default: return QSize(list.at(0), list.at(1));
        }
    }

    //!
    //! To generate a point from a JavaScript list 
    //!
    QPoint point(QList<qreal> list)
    {
        switch(list.size())
        {
            case 0:  return QPoint(0         , 0         );
            case 1:  return QPoint(list.at(0), 0         );
            default: return QPoint(list.at(0), list.at(1));
        }
    }

};


#endif // TYPE_HPP
