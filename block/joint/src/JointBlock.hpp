#ifndef JOINTBLOCK_HPP
#define JOINTBLOCK_HPP
//!
//! \file JointBlock.hpp
//!
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

#include <QMatrix4x4>
#include <BotBlock.hpp>

class LinkBlock;

//!
//! Block that provides transformation between 2 links
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class JointBlock : public BotBlock
{
    Q_OBJECT
    Q_ENUMS(JointType)
    
    Q_PROPERTY(qreal value      READ value      WRITE setValue      MEMBER _value   )
    Q_PROPERTY(qreal min        READ minValue   WRITE setMinValue   MEMBER _minValue)
    Q_PROPERTY(qreal max        READ maxValue   WRITE setMaxValue   MEMBER _maxValue)
    
    Q_PROPERTY(JointType type     READ type     WRITE changeType    MEMBER _type    )
    Q_PROPERTY(QVector3D axe      READ axe                          MEMBER _axe     )
    Q_PROPERTY(QVector4D position READ pos                          MEMBER _pos     )

public:
    //! Type of available joint
    enum JointType { JointFixe, JointRevolute, JointPrismatic } ;
    
    //!
    //! Default constructor
    //!
    explicit JointBlock(const QString& name = QString("joint"), QObject *parent = 0)
        : BotBlock(name, parent)
    {
        // TYPE
        QMap<QString, int> type_enum;
        type_enum["Fixe"     ] = JointFixe     ;
        type_enum["Revolute" ] = JointRevolute ;
        type_enum["Prismatic"] = JointPrismatic;
        appendBlockIProperty("type" , IProperty(IProperty::IPTypeEnum, true, type_enum));
        // VALUE
        appendBlockIProperty("value", IProperty(IProperty::IPTypeReal, true));
        appendBlockIProperty("min"  , IProperty(IProperty::IPTypeReal, true));
        appendBlockIProperty("max"  , IProperty(IProperty::IPTypeReal, true));

        appendBlockIProperty("axe"     , IProperty(IProperty::IPTypeVector3D, false));
        appendBlockIProperty("position", IProperty(IProperty::IPTypeVector3D, false));
    }
    
    //! FROM BotBlock
    virtual float getBlockVersion() const { return 1.0; }

    //! FROM BotBlock
    virtual BlockRole getBlockRole() const { return BotBlock::BlockData; }
    
    //! FROM BotBlock
    virtual QString getBlockTypeName() const { return QString("joint"); }

    //! FROM BotBlock
    virtual int getBlockNumberOfSons() const { return BotBlock::getBlockNumberOfSons(); }

    //! FROM BotBlock
    virtual int getNumberOfConn() const
    {
        int conn = BotBlock::getBlockNumberOfConnections();
        if(_baseLink) { conn++; }
        conn += _outputLinks.size();
        return conn;
    }

    //! Current value getter
    qreal value() { return _value; }
    
    //! Current value setter
    void setValue(qreal val) { _value = val; }
    
    //! Min value getter
    qreal minValue() { return _minValue; }
    
    //! Min value setter
    void setMinValue(qreal val) { _minValue = val; }
    
    //! Max value getter
    qreal maxValue() { return _maxValue; }

    //! Max value setter
    void setMaxValue(qreal val) { _maxValue = val; }

    //! Min Max value setter
    void setMinMaxValue(qreal min, qreal max) { _minValue = min; _maxValue = max; }

    //! Joint type getter
    JointType type() { return _type; }
    
    //! Joint type setter
    void changeType(JointType type)
    {
        // Remove old properties
        switch(_type)
        {
            case JointFixe:
                break;

            case JointRevolute:
                // Value
                //removeInteractiveProperty("value");
                break;

            case JointPrismatic:

                break;

            default: break;
        }

        // Add new ones
        _type = type;
        switch(_type)
        {
            case JointFixe:
                break;

            case JointRevolute:
                // Value
                //appendInteractiveProperty("value", { true, IPTypeReal, {} });
                break;

            case JointPrismatic:

                break;

            default: break;
        }

        // Alert
        //emit propertyStructureChanged();
    }

    //! Axe getter
    const QVector3D& axe() const { return _axe; }

    //! Pos getter
    const QVector4D& pos() const { return _pos; }

    //! Result transform matrix getter
    const QMatrix4x4& transform() const { return _tranform; }

public slots:

    //! Update transform properties
    void updateTransform();
    
protected:
    //! Current value
    qreal _value;

    //! Min value
    qreal _minValue;
    
    //! Max value
    qreal _maxValue;
    
    //! Joint type
    JointType _type;

    //! Joint axe (0,0,1) by default
    QVector3D _axe;

    //! Joint pos (0,0,0) by default
    QVector4D _pos;

    //! Result transform matrix
    QMatrix4x4 _tranform;

    //! Connection object
    //! Link that provide initial transformation to the joint
    QWeakPointer<LinkBlock> _baseLink;

    //! Connection object
    //! Links that are transformed by this joint (only 1 for revolute and prismatic)
    QList<QWeakPointer<LinkBlock> > _outputLinks;
};

#endif // JOINTBLOCK_HPP
