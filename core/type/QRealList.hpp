#ifndef QREALLIST_HPP
#define QREALLIST_HPP
//!
//! \file QRealList.hpp
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

#include <QList>
#include <QtGlobal>
#include <QVector3D>

#include <iostream>
#include <initializer_list>

//!
//! List of reals
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class QRealList : public QList<qreal>
{

public:
    //! Default constructor
    QRealList()
        : QList<qreal>()
    { }

    //! Constructor from vector 3D
    QRealList(const QVector3D& vector)
        : QList<qreal>({vector.x(),vector.y(),vector.z()})
    { }

    //! Constructor from copy
    QRealList(const QList<qreal>& other)
        : QList<qreal>(other)
    { }

    //! Constructor from initializer list
    QRealList(std::initializer_list<qreal> args)
        : QList<qreal>(args)
    { }

    //! Convert the list to a vector 3D
    QVector3D toVector3D()
    {
        switch(size())
        {
            case 0:  return QVector3D();
            case 1:  return QVector3D(at(0), 0    , 0);
            case 2:  return QVector3D(at(0), at(1), 0);
            case 3:  return QVector3D(at(0), at(1), at(2));
            default: return QVector3D(at(0), at(1), at(2));
        }
    }

protected:

};

#endif // QREALLIST_HPP
