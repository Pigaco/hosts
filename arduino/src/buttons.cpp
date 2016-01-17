#include <buttons.hpp>
#include <PlayerManager.hpp>
#include "../../host_defines.h"
#include <main.hpp>

namespace Buttons
{
    void setCallbackFunc(host_input_callback_func callback)
    {
        getPlayerMgr()->setCallbackFunc(callback);
    }
}
