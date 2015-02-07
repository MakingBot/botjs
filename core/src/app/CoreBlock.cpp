#include <QApplication>
#include <CoreBlock.hpp>

/* ============================================================================
 *
 * */
CoreBlock::CoreBlock(const QString& name, QObject *parent)
    : BotBlock(name, parent)
{ }

/* ============================================================================
 *
 * */
void CoreBlock::blockInit()
{
    BotBlock::blockInit();
    if( ! QMetaType::isRegistered(QMetaType::type("CoreBlock*")) ) { qRegisterMetaType<CoreBlock*>("CoreBlock*"); }
}

/* ============================================================================
 *
 * */
BotBlock* CoreBlock::create(const QString& btypename, const QString& varname)
{
    // Block creation
    BotBlock* block = BotBlock::create(btypename, varname);

    // Make the block accessible from js
    BotBlock::JsEngine.go().setProperty(varname.toStdString().c_str(), BotBlock::JsEngine.engine()->newQObject(block));
    
    return block;
}


