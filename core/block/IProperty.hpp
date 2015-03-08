#ifndef IPROPERTY_HPP
#define IPROPERTY_HPP
//!
//! \file IProperty.hpp
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
#include <QStringList>
#include <QMapIterator>

//!
//! An interactive property provide elements to dynamically modify QObject property.
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class IProperty
{

public:
    
    //!
    //! Define the different type of property
    //!
    enum IPropertyType{
        IPTypeBool              ,
        IPTypeInt               ,
        IPTypeReal              ,
        IPTypeString            ,
        IPTypeEnum              ,
        IPTypeBlock             ,
        IPTypeSonBlock          ,
        IPTypeBrotherBlock      ,
        IPTypeRealList          ,
        IPTypeVector3D          ,
        IPTypeVector4D          ,
        IPTypeMatrix44          };

    //!
    //! Default constructor
    //!
    IProperty(const QString& name, IPropertyType t = IPTypeBool, bool w = false, QMap<QString, int> enu = QMap<QString, int>())
        : _name(name), _writable(w), _type(t), _enum(enu)
    { }
    
    //!
    //! Constructor for block type
    //!
    IProperty(const QString& name, IPropertyType t, QStringList cmp)
        : _writable(true), _type(t), _compat(cmp)
    { }

    // ========================================================================
    // => Interactive property name

    //!
    //! Name getter
    //!
    inline const char* name() const
    {
        return _name.toStdString().c_str();
    }
    inline const QString& strName() const
    {
        return _name;
    }
    
    // ========================================================================
    // => Interactive property name

    //!
    //! Writable flag getter
    //!
    inline bool isWritable() const
    {
        return _writable;
    }

    // ========================================================================
    // => Interactive property type
    
    //!
    //! Property type getter
    //!
    inline IPropertyType type() const
    {
        return _type;
    }

    // ========================================================================
    // => Interactive property complement
    
    //!
    //! Enum map getter
    //!
    inline const QMap<QString, int>& enumMap() const
    {
        return _enum;
    }
    
    //!
    //! Compat list getter
    //!
    inline const QStringList& compatList() const
    {
        return _compat;
    }

    //!
    //! To convert the enum a into a stringlist
    //!
    inline QStringList enumStringList() const
    {
        QStringList l;
        QMapIterator<QString, int> e(_enum);
        while(e.hasNext())
        {
            e.next(); 
            l << e.key();
        }
        return l;
    }

    //!
    //! Return the enum value for the given enum name
    //!
    inline int enumValue(QString name) const
    {
        return _enum[name];
    }

    //!
    //! Return the enum name of the enum value
    //!
    inline QString enumName(int value) const
    {
        return _enum.key(value); 
    }

protected:
    
    //! Name of the property
    //! To be able to use directly the setProperty function
    const QString               _name;
    
    //! Is writable
    //! True if the property is writable
    const bool                  _writable;

    //! Type
    //! Custom type for the interactive properties
    const IPropertyType         _type;

    //! If type is IPTypeEnum
    //! this is the map of the enum[name] = value
    const QMap<QString, int>    _enum;
    
    //! If type is IPTypeBlock, IPTypeSonBlock or IPTypeBrotherBlock
    //! This is the list of the accepted block types, empty means all type accepted
    const QStringList           _compat;

};

#endif // IPROPERTY_HPP
