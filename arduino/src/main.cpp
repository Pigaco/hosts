#include "../../host.h"

#include <iostream>

/*
 * This library creates an interface for the included arduino
 * program and the piga library. 
 */

#include <buttons.hpp>
#include <outputs.hpp>
#include <arduino.hpp>
#include <INIReader.h>
#include <main.hpp>
#include <PlayerManager.hpp>

using std::cout;
using std::endl;

INIReader *reader = nullptr;
PlayerManager *playerMgr = nullptr;

int init(int playerCount)
{
    //Load the config file.
    reader = new INIReader("host_arduino.ini");

    if(reader->ParseError() < 0)
    {
        cout << "[HOST][ARDUINO] Cannot load \"host_arduino.ini\"!" << endl;
        cout << "[HOST][ARDUINO] Using default configs. This could lead to errors with this host!" << endl;
    }
        playerMgr = new PlayerManager(playerCount, reader);

        Buttons::playerMgr = playerMgr;
        Outputs::playerMgr = playerMgr;

        Buttons::config = reader;
        Outputs::config = reader;

    return HOST_RETURNCODE_USEFIXEDFUNCTION;
}
PlayerManager* getPlayerMgr()
{
    return playerMgr;
}

int destroy()
{
    delete playerMgr;
    delete reader;
}

const char* getName()
{
    return "Arduino - USB Virtual Serial Connection (2 Arduino IN/OUT)";
}
const char* getDescription()
{
    return "This host uses 2 arduinos (connected over USB) to receive inputs from one of them and send outputs to the other one.\nThis was made for the original PiGaCo console layout.\nVersion: 0.1";
}
const char* getAuthor()
{
    return "Max Heisinger";
}

void setCallbackFunc(void (*inputHappened)(int, int, int))
{
    Buttons::setCallbackFunc(inputHappened);
}
int implementsOutputs()
{
    return Outputs::implementsOutputs();
}
int getOutputCount()
{
    return Outputs::getOutputCount();
}
int getOutputType(int outputID)
{
    return Outputs::getOutputType(outputID);
}
int getOutputPos(int outputID)
{
    return Outputs::getOutputPos(outputID);
}
const char* getOutputName(int outputID)
{
    return Outputs::getOutputName(outputID);
}
const char* getOutputDescription(int outputID)
{
    return Outputs::getOutputDescription(outputID);
}

int getIntOutputRangeMin(int outputID)
{
    return Outputs::getIntOutputRangeMin(outputID);
}
int getIntOutputRangeMax(int outputID)
{
    return Outputs::getIntOutputRangeMax(outputID);
}

int setIntOutput(int outputID, int value)
{
    return Outputs::setIntOutput(outputID, value);
}
