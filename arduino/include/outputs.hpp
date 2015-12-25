#pragma once

class INIReader;
class PlayerManager;

#include <INIReader.h>
#include <arduino.hpp>

namespace Outputs
{
    static INIReader *config;
    static PlayerManager *playerMgr;

    int implementsOutputs();
    int getOutputCount();
    int getOutputType(int outputID);
    int getOutputPos(int outputID);

    const char* getOutputName(int outputID);
    const char* getOutputDescription(int outputID);

    int getIntOutputRangeMin(int outputID);
    int getIntOutputRangeMax(int outputID);

    int setIntOutput(int outputID, int value);
}
