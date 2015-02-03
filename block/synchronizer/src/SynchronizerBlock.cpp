#include <SynchronizerBlock.hpp>

//! Block properties
#define _BLOCK_PROPERTIES_  QVector<QString>()

/* ============================================================================
 *
 * */
EXPORT_BLOCK(SynchronizerBlock);

/* ============================================================================
 *
 * */
SynchronizerBlock::SynchronizerBlock(const QString& name, QObject *parent)
    : BotBlock(name, _BLOCK_PROPERTIES_, parent)
{

}
