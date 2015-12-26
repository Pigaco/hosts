#pragma once

#include <memory>
#include <arduino.hpp>

class Player
{
    public:
        Player(std::unique_ptr<Arduino> arduino);
        ~Player();

        void send(char *buffer, int size);
        int read(char *buffer, int size, bool &read);
        bool sendHello();
    private:
        std::unique_ptr<Arduino> m_arduino;
};
