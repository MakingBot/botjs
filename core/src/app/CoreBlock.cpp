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
void CoreBlock::create(const QString& btypename, const QString& varname)
{
    // Check if the name already exist 
    if(BotBlock::JsEngine.go().property(varname).toVariant().isValid())
    {
        // Log
        beglog() << "Create block #" << btypename << "# failure: this name is already used" << endlog();
        return;
    }

    // Create block from the JsEngine
    QSharedPointer<BotBlock> block = BotBlock::JsEngine.createBlock(btypename, varname);

    // Set this as the block parent
    block->setBlockFather(this);
    
    // Add block to this son
    this->appendSon(block);

    // Make the block accessible from js
    BotBlock::JsEngine.go().setProperty(varname.toStdString().c_str(), BotBlock::JsEngine.engine()->newQObject(block.data()));

    // Log
    beglog() << "Create block #" << block->getBlockName() << "#" << endlog();
}


