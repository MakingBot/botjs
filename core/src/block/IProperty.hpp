#ifndef IPROPERTY_HPP
#define IPROPERTY_HPP

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
    
    //! Define the different type of property
    enum IPropertyType{ IPTypeBool      , IPTypeInt     , IPTypeReal        ,
                        IPTypeString    , IPTypeEnum    ,
                        IPTypeBlock     , IPTypeSonBlock, IPTypeBrotherBlock,
                        IPTypeVector3D  , IPTypeMatrix44
    };

    //!
    //! Default constructor
    //!
    IProperty(IPropertyType t = IPTypeBool, bool w = false, QMap<QString, int> enu = QMap<QString, int>())
        : _writable(w), _type(t), _enum(enu)
    { }
    
    //!
    //! Constructor for block type
    //!
    IProperty(IPropertyType t, QStringList cmp)
        : _writable(true), _type(t), _compat(cmp)
    { }

    //!
    //! Copy constructor
    //!
    IProperty(const IProperty& p)
    {
        copy(p);
    }
    
    //! Writable flag getter
    inline bool isWritable() const { return _writable; }
    
    //! Property type getter
    inline IPropertyType type() const { return _type; }

    //! Enum map getter
    inline const QMap<QString, int>& enumMap() const { return _enum; }
    
    //! Compat list getter
    inline const QStringList& compatList() const { return _compat; }

    //! To convert the enum a into a stringlist
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

    //! Return the enum value for the given enum name
    inline int enumValue(QString name) const
    {
        return _enum[name];
    }
    
    //! Return the enum name of the enum value
    inline QString enumName(int value) const
    {
        return _enum.key(value); 
    }

    //! Copy function
    inline void copy(const IProperty& property)
    {
        _writable   = property.isWritable();
        _type       = property.type();
        _enum       = property.enumMap();
        _compat     = property.compatList();
    }

    //! Copy operator
    inline void operator=(const IProperty& p){ copy(p); }

protected:
    
    //! True if the property is writable
    bool _writable;

    //! Custom type for the interactive properties
    IPropertyType _type;

    //! If type is IPTypeEnum
    //! this is the map of the enum[name] = value
    QMap<QString, int> _enum;
    
    //! If type is IPTypeBlock, IPTypeSonBlock or IPTypeBrotherBlock
    //! This is the list of the accepted block types, empty means all type accepted
    QStringList _compat;

};

#endif // IPROPERTY_HPP
