#pragma once

#include <arduino.hpp>

namespace Buttons
{
    INIReader *config;
    Arduino *buttonArduino;

    int getButtonState(int playerID, int buttonID);
}
