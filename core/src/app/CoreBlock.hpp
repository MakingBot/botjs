#ifndef COREBLOCK_HPP
#define COREBLOCK_HPP

#include <BotBlock.hpp>

//!
//! This block is the top parent of all blocks
//!
class CoreBlock : public BotBlock
{
    Q_OBJECT

public:
    //!
    //! Default constructor
    //!
    explicit CoreBlock(const QString& name = QString("core"), QObject* parent = 0);
    
    //! FROM BotBlock
    virtual void blockInit(QSharedPointer<BotEngine> js_engine);

    //! FROM BotBlock
    virtual float getBlockVersion() const { return 1.0; }

    //! FROM BotBlock
    virtual BlockRole getBlockRole() const { return BotBlock::BlockCore; }

    //! FROM BotBlock
    virtual QString getBlockTypeName() const { return QString("core"); }

public slots:
    //! FROM BotBlock
    virtual void create(const QString& btypename, const QString& varname);
};

#endif // COREBLOCK_HPP
