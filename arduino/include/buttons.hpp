#pragma once

class INIReader;
class PlayerManager;

#include <arduino.hpp>
#include "../host_defines.h"

namespace Buttons
{
    static INIReader *config;
    static PlayerManager* playerMgr;

    void setCallbackFunc(host_input_callback_func callback);
}
