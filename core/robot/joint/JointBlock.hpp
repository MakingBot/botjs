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
#include <PhysicBlock.hpp>

class LinkBlock;

//!
//! Block that provides transformation between 2 links
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class JointBlock : public PhysicBlock
{
    Q_OBJECT

    Q_ENUMS(JointType)
    
    Q_PROPERTY(qreal value      READ value      WRITE setValue      MEMBER _value   )
    Q_PROPERTY(qreal min        READ minValue   WRITE setMinValue   MEMBER _minValue)
    Q_PROPERTY(qreal max        READ maxValue   WRITE setMaxValue   MEMBER _maxValue)
    
    Q_PROPERTY(JointType type     READ type     WRITE changeType    MEMBER _type    )
    Q_PROPERTY(QVector4D axe      READ axe                          MEMBER _axe     )

public:
    //! Type of available joint
    enum JointType { JointFixe, JointRevolute, JointPrismatic } ;
    
    //!
    //! Default constructor
    //!
    explicit JointBlock(const QString& name = QString("joint"), QObject *parent = 0)
        : PhysicBlock(name, parent)
    {
        // TYPE
        QMap<QString, int> type_enum;
        type_enum["Fixe"     ] = JointFixe     ;
        type_enum["Revolute" ] = JointRevolute ;
        type_enum["Prismatic"] = JointPrismatic;
        appendBlockIProperty("type" , IProperty(IProperty::IPTypeEnum, true, type_enum));


        // 
        updateJoint();
    }
    
    // ========================================================================
    // => BotBlock redefinition

    //! FROM BotBlock
    virtual float blockVersion() const { return 1.0; }

    //! FROM BotBlock
    virtual QString blockTypeName() const { return QString("joint"); }

    //! FROM BotBlock
    virtual int blockSonNb() const { return BotBlock::blockSonNb(); }

    //! FROM BotBlock
    virtual int getNumberOfConn() const
    {
        int conn = BotBlock::getBlockNumberOfConnections();
        if(_inlink) { conn++; }
        conn += _outlinks.size();
        return conn;
    }

    // ========================================================================
    // => Property value

    //! Current value getter
    qreal value() { return _value; }
    
    //! Current value setter
    void setValue(qreal val) { _value = val; }

    // ========================================================================
    // => Property min value
    
    //! Min value getter
    qreal minValue() { return _minValue; }
    
    //! Min value setter
    void setMinValue(qreal val) { _minValue = val; }

    // ========================================================================
    // => Property maw value

    //! Max value getter
    qreal maxValue() { return _maxValue; }

    //! Max value setter
    void setMaxValue(qreal val) { _maxValue = val; }

    //! Min Max value setter
    void setMinMaxValue(qreal min, qreal max) { _minValue = min; _maxValue = max; }

    // ========================================================================
    // => Property type

    //!
    void setTypeByName(const QString& type_name)
    {
        // Get properties
        const QMap<QString, IProperty>& properties = iProperties();

        // Find the goo value
        changeType( (JointType)properties["type"].enumValue(type_name) );
    }

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
                // VALUE
                removeBlockIProperty("value");
                // MIN
                removeBlockIProperty("min"  );
                // MAX
                removeBlockIProperty("max"  );
                // AXE
                removeBlockIProperty("axe"  );
                break;

            case JointPrismatic:
                // VALUE
                removeBlockIProperty("value");
                // MIN
                removeBlockIProperty("min"  );
                // MAX
                removeBlockIProperty("max"  );
                // AXE
                removeBlockIProperty("axe"  );
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
                // VALUE
                appendBlockIProperty("value", IProperty(IProperty::IPTypeReal, true));
                // MIN
                appendBlockIProperty("min"  , IProperty(IProperty::IPTypeReal, true));
                // MAX
                appendBlockIProperty("max"  , IProperty(IProperty::IPTypeReal, true));
                // AXE
                appendBlockIProperty("axe"  , IProperty(IProperty::IPTypeVector4D, false));
                break;

            case JointPrismatic:
                // VALUE
                appendBlockIProperty("value", IProperty(IProperty::IPTypeReal, true));
                // MIN
                appendBlockIProperty("min"  , IProperty(IProperty::IPTypeReal, true));
                // MAX
                appendBlockIProperty("max"  , IProperty(IProperty::IPTypeReal, true));
                // AXE
                appendBlockIProperty("axe"  , IProperty(IProperty::IPTypeVector4D, false));
                break;

            default: break;
        }

        // Alert
        emit blockiPropertyStructureChanged();
    }

    //! Axe getter
    const QVector4D& axe() const { return _axe; }

signals:

public slots:

    //! Update transform properties
    //!
    void updateJoint();

    //! Update axe
    //!
    void updateAxe();

    // ========================================================================
    // => BotBlock redefinition

    //! FROM BotBlock
    virtual bool connect(BotBlock* block, bool master=true);

    //! FROM BotBlock
    virtual void disconnect(BotBlock* block, bool master=true);

    //! FROM BotBlock
    virtual void disconnectAll();

    // ========================================================================
    // => PhysicBlock redefinition: updaters

    //! FROM PhysicBlock
    virtual void updatePhysicShapeData      ();
    //! FROM PhysicBlock
    virtual void updatePhysicPosition       ();
    //! FROM PhysicBlock
    virtual void updatePhysicTransform      ();
    //! FROM PhysicBlock
    virtual void updatePhysicPreTransform   ();
    //! FROM PhysicBlock
    virtual void updatePhysicPostTransform  ();
    //! FROM PhysicBlock
    virtual void updatePhysicSlaves         ();

protected:
    //! Current value
    qreal _value;

    //! Min value
    qreal _minValue;
    
    //! Max value
    qreal _maxValue;
    
    //! Joint type
    JointType _type;

    //! Joint axe (0,0,1,0) by default
    QVector4D  _axe;

    //! Connection object
    //! Link that provide initial transformation to the joint
    QWeakPointer<LinkBlock> _inlink;

    //! Connection object
    //! Links that are transformed by this joint (only 1 for revolute and prismatic)
    QList<QWeakPointer<LinkBlock> > _outlinks;
};

#endif // JOINTBLOCK_HPP
