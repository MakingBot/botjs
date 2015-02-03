#ifndef JOINTBLOCK_HPP
#define JOINTBLOCK_HPP

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
    
    Q_PROPERTY(JointType type   READ type       WRITE changeType    MEMBER _type    )
    Q_PROPERTY(QVector3D axe    READ axe                            MEMBER _axe     )
    
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
    }

    //! FROM BotBlock
    virtual void blockInit(QSharedPointer<BotEngine> js_engine)
    {
        BotBlock::blockInit(js_engine);
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

    //! Result transform matrix getter
    const QMatrix4x4& transform() const { return _tranform; }

protected:
    //! Current value
    qreal _value;

    //! Min value
    qreal _minValue;
    
    //! Max value
    qreal _maxValue;
    
    //! Joint type
    JointType _type;

    //! Updated joint axe (0,1,0) by default
    QVector3D _axe;

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
