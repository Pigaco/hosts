#pragma once

class INIReader;
class PlayerManager;

#include <arduino.hpp>

namespace Buttons
{
    static INIReader *config;
    static PlayerManager* playerMgr;

    int getButtonState(int playerID, int buttonID);
    void setCallbackFunc(void (*inputHappened)(int, int, int));
}
