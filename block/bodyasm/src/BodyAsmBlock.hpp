#ifndef BODYASMBLOCK_HPP
#define BODYASMBLOCK_HPP

#include <BotBlock.hpp>

//! Block interactive properties
#define BODYASMBLOCK_BLOCK_I_PROPERTIES_ { } 

//!
//! A body assembly
//!
class BodyAsmBlock : public BotBlock
{
    Q_OBJECT

public:


    //!
    //! Default constructor
    //!
    explicit BodyAsmBlock(const QString& name = QString("bodyasm"), QObject *parent = 0)
        : BotBlock(name, QStringList(BODYASMBLOCK_BLOCK_I_PROPERTIES_), parent)
    { }

    //! FROM BotBlock
    virtual void init(QSharedPointer<BotEngine> js_engine)
    {
        BotBlock::init(js_engine);
    }

    //! FROM BotBlock
    virtual float getBlockVersion() const { return 1.0; }

    //! FROM BotBlock
    virtual QString getBlockTypeName() const { return QString("bodyasm"); }

    //! FROM BotBlock
    virtual BlockRole getBlockRole() const { return BlockData; }

    //! FROM BotBlock
    virtual QString getBlockDescription() const
    {
        return QString("");
    }

public slots:
    //! FROM BotBlock
    virtual void connect(BotBlock* block)
    {

    }

protected:

    // enum { AsmTree, AsmChain }
    
    // tree: 1 BeginJoint - N EndJoint
    // chain: 1 beginJoint - 1 End joint

};

#endif // BODYASMBLOCK_HPP

