#include "../../host.h"

#include <iostream>

/*
 * This library creates an interface for the included arduino
 * program and the piga library. 
 */

#include <buttons.hpp>
#include <outputs.hpp>
#include <arduino.hpp>

using std::cout;
using std::endl

INIReader *reader = nullptr;

int init(int playerCount)
{
    //Load the config file.
    reader = new INIReader("host_arduino.ini");

    if(reader.ParseError() < 0)
    {
        cout << "[HOST][ARDUINO] Cannot load \"host_arduino.ini\"!" << endl;
    } else {
        Buttons::config = reader;
        Outputs::config = reader;
    }

    Buttons::buttonArduino = new Arduino(reader.Get("Buttons", "SerialPath", "/dev/ttyUSB0").c_str(), reader);
    Outputs::outputArduino = new Arduino(reader.Get("Buttons", "SerialPath", "/dev/ttyUSB1").c_str(), reader);

    return HOST_RETURNCODE_USEFIXEDFUNCTION;
}
int destroy()
{
    delete Buttons::buttonArduino;
    Buttons::buttonArduino = nullptr;

    delete Outputs::outputArduino;
    Outputs::outputArduino = nullptr;

    delete reader;
    reader = nullptr;
    Buttons::config = nullptr;
    Outputs::config = nullptr;
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
    return Outputs::getOutputType(int outputID);
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
