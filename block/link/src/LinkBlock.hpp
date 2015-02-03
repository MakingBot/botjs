#ifndef LINKBLOCK_HPP
#define LINKBLOCK_HPP

#include <QMatrix4x4>
#include <BotBlock.hpp>

class JointBlock;

//!
//! Fixe transformation between 2 joints
//! The link between 2 motors of a robot arm for example
//!
class LinkBlock : public BotBlock
{
    Q_OBJECT
    Q_PROPERTY(QMatrix4x4 transform READ transform WRITE setTransform MEMBER _transform)
    
public:
    //!
    //! Default constructor
    //!
    explicit LinkBlock(const QString& name, QObject *parent = 0);

    //! FROM BotBlock
    virtual void init(QSharedPointer<BotEngine> js_engine);

    //! FROM BotBlock
    virtual float getBlockVersion() const { return 1.0; }

    //! FROM BotBlock
    virtual QString getBlockTypeName() const { return QString("link"); }

    //! FROM BotBlock
    virtual QString getBlockDescription() const
    {
        return QString("");
    }

    //!
    //! Transform matrix getter
    //!
    const QMatrix4x4& transform() const { return _transform; }
    
    //!
    //! Transform matrix setter
    //!
    void setTransform(const QMatrix4x4& matrix) { _transform = matrix; }
    
public slots:

protected:
    // rotation
    
    // translation
    

    // Transform matrix
    QMatrix4x4 _transform;
    
    //! Link end
    QWeakPointer<JointBlock> _endJoint;
    
    //! Link base
    QWeakPointer<JointBlock> _baseJoint;

};

#endif // LINKBLOCK_HPP
