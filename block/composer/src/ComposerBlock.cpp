#include <ComposerBlock.hpp>

//! Block interactive properties
#define _BLOCK_I_PROPERTIES_ {"visible"} 

/* ============================================================================
 *
 * */
EXPORT_BLOCK(ComposerBlock);

/* ============================================================================
 *
 * */
ComposerBlock::ComposerBlock(const QString& name, QObject *parent)
    : BotBlock(name, QStringList(_BLOCK_I_PROPERTIES_), parent)
{

}

/* ============================================================================
 *
 * */
void ComposerBlock::init(QSharedPointer<BotEngine> js_engine)
{   
    BotBlock::init(js_engine);
}

/* ============================================================================
 *
 * */
void ComposerBlock::connect(BotBlock* block)
{

}
