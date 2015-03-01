




#include <ComInterfaceBlock.hpp>

#include <ControllerBlock.hpp>


bool ComInterfaceBlock::connectionHook(QWeakPointer<BotBlock> weakblock, bool master)
{


    QSharedPointer<ControllerBlock> controller = qWeakPointerCast<ControllerBlock, BotBlock>(weakblock).toStrongRef();
    if(controller)
    {
        _controllers[ controller->device() ] = controller.toWeakRef();   
        return true;
    }

    // End
    return BotBlock::connectionHook(weakblock, master);
}



