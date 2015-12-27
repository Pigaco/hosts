#include <buttons.hpp>
#include <PlayerManager.hpp>

namespace Buttons
{
    void setCallbackFunc(void *callback)
    {
        playerMgr->setCallbackFunc(callback);
    }
}
