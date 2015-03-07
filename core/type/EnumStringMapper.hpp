#ifndef ENUMSTRINGMAPPER_HPP
#define ENUMSTRINGMAPPER_HPP
//!
//! \file EnumStringMapper.hpp
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

#include <QMap>
#include <QPair>
#include <QString>

//!
//! Represents an enum value with an enum string
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class EnumPair : QPair<int, QString>
{
public:

    //!
    //! Default constructor
    //!
    EnumPair(int enum_value, const QString& enum_name)
        : QPair<int, QString>(enum_value, enum_name)
    { }

    int eValue() const
    {
        return first;
    }
    
    const QString& eName() const
    {
        return second;
    }
};

//!
//! To associate enums with strings
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class EnumStringMapper
{

public:

    //!
    //! Default constructor
    //!
    EnumStringMapper(int* enum_ref, std::initializer_list<EnumPair> enum_list)
        : _ref(enum_ref)
    {
        std::initializer_list<EnumPair>::iterator it;
        for(it=enum_list.begin() ; it!=enum_list.end() ; ++it)
        {
            _map[(*it).eValue()] = (*it).eName();
        }
    }

    //!
    //! Return the string value of the enum
    //!
    QString toString() const
    {
        return _map[*_ref];
    }

    //!
    //! Set the enum with the value of the name
    //!
    void fromString(const QString& name)
    {
        *_ref = _map.key(name); 
    }

protected:

    //! Ref
    //! Reference on the enum
    int* _ref;

    //! Map
    //! To keep the association enum/string
    QMap<int, QString> _map;

};

#endif // ENUMSTRINGMAPPER_HPP
