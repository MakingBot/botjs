#include <SpyBlock.hpp>

/* ============================================================================
 *
 * */
EXPORT_BLOCK(SpyBlock)

/* ============================================================================
 *
 * */
SpyBlock::SpyBlock(const QString& name, QObject *parent)
    : BotBlock(name, parent)
{
    appendBlockIProperty("visible", IProperty(IProperty::IPTypeBool, true));
}

/* ============================================================================
 *
 * */
bool SpyBlock::connect(BotBlock* block, bool master)
{
    // Basic checks
    if(!block)        { beglog() << "Connection to null block failure" << endlog(); return false; }
    if(block == this) { beglog() << "Connection to itself refused"     << endlog(); return false; }


    // This block ask for a connection
    if(master)
    {
        // Ask for connection back
        if(! block->connect(this, false))
        {
            // Log and return
            beglog() << "Connection to " << block->getBlockFathersChain() << " failure: connection return refused" << endlog();
            return false;
        }

        // TODO Disconnect old
        if(_spiedBlock)
        {

        }

        // Check widget creation
        createWidgetIfRequired();

        // Track the new spied block
        _spiedBlock = block->getBlockWeakFromThis();

        // Alert the view
        emit spiedBlockChanged();

        // Log and return
        beglog() << "Connection to #" << block->getBlockFathersChain() << "#" << endlog();
        return true;
    }
    // Other block ask for a connection
    else
    {
        // If an other spy ask for a connection accept it
        SpyBlock* spy = qobject_cast<SpyBlock*>(block);
        if(spy)
        {
            // Use main connect function
            return BotBlock::connect(block, master);            
        }

        // Log and return
        beglog() << "Connection from #" << block->getBlockFathersChain() << "# refused: it is not a spy block" << endlog();
        return false;
    }
}

/* ============================================================================
 *
 * */
void SpyBlock::blockInit(QSharedPointer<BotEngine> js_engine)
{
    BotBlock::blockInit(js_engine);
}
