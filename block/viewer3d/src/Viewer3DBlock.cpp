#include <Viewer3DBlock.hpp>

/* ============================================================================
 *
 * */
EXPORT_BLOCK(Viewer3DBlock)

/* ============================================================================
 *
 * */
Viewer3DBlock::Viewer3DBlock(const QString& name, QObject *parent)
    : BotBlock(name, parent), _visible(false), _bgColor(240,240,240)
{
    appendBlockIProperty("visible", IProperty(IProperty::IPTypeBool, true));
}

/* ============================================================================
 *
 * */
void Viewer3DBlock::blockInit(QSharedPointer<BotEngine> js_engine)
{
    BotBlock::blockInit(js_engine);
}

