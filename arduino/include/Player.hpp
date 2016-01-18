#pragma once

#include <memory>
#include <arduino.hpp>
#include "../host_defines.h"

class Player
{
    public:
        Player(std::unique_ptr<Arduino> arduino, int playerID);
        ~Player();

        // Host-Communication with the piga library
        void setCallbackFunc(host_input_callback_func callback);

        // High-Level Communication


        // Low-Level Arduino Communication
        void send(char *buffer, int size);
        int read(char *buffer, int size, bool &read);
        bool sendHello();
        void printReady();

        void arduinoCallback(uint8_t packet);
    private:
        std::unique_ptr<Arduino> m_arduino;
        host_input_callback_func m_callback;
        int m_playerID;
        host_input_callback_func m_callbackFunc;
};
