#ifndef BODYBLOCK_HPP
#define BODYBLOCK_HPP

#include <BotBlock.hpp>

class LinkBlock;
class JointBlock;

//!
//! Robot body, fixe block
//!
class BodyBlock : public BotBlock
{
    Q_OBJECT

public:
    //!
    //! Default constructor
    //!
    explicit BodyBlock(const QString& name = QString("body"), QObject *parent = 0);

    //! FROM BotBlock
    virtual void init(QSharedPointer<BotEngine> js_engine);

    //! FROM BotBlock
    virtual float getBlockVersion() const { return 1.0; }

    //! FROM BotBlock
    virtual QString getBlockTypeName() const { return QString("body"); }

    //! FROM BotBlock
    virtual BlockRole getBlockRole() const { return BlockData; }

    //! FROM BotBlock
    virtual QString getBlockDescription() const
    {
        return QString("");
    }

public slots:

protected:
    //! Joint base
    QWeakPointer<JointBlock> _base;

    //! Joints that can be connected to effector base joint
    QList<QWeakPointer<LinkBlock>> _connectors;
};

#endif // BODYBLOCK_HPP

