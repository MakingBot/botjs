




#include <ComInterfaceBlock.hpp>

#include <ControllerBlock.hpp>


bool ComInterfaceBlock::connectionHook(QWeakPointer<BotBlock> weakblock, bool master)
{

    QWeakPointer<ControllerBlock> controller = qWeakPointerCast<ControllerBlock, BotBlock>(weakblock);
    if(controller)
    {
        return false;
    }

    // End
    return BotBlock::connectionHook(weakblock, master);
}

void ComInterfaceBlock::registerController(quint16 device, ControllerBlock* block)
{
    _controllers[device] = block->toSpecializedSharedPointer<ControllerBlock>();
}


