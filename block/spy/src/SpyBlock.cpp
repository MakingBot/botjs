#include <SpyBlock.hpp>

/* ============================================================================
 *
 * */
EXPORT_BLOCK(SpyBlock);

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
    if(!block)        { /* TODO std::cerr << "-- BotBlock::connectBlock => null ptr"                    << std::endl;*/ return false; }
    if(block == this) { /* TODO std::cerr << "-- BotBlock::connectBlock => unable to connect to itself" << std::endl;*/ return false; }

    // This block ask for a connection
    if(master)
    {
        // Ask for connection back
        if(! block->connect(this, false))
        {
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
