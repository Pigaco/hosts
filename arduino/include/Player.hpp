#pragma once

#include <memory>
#include <arduino.hpp>

class Player
{
    public:
        Player(std::unique_ptr<Arduino> arduino);
        ~Player();

        void send(char *buffer, int size);
    private:
        std::unique_ptr<Arduino> m_arduino;
};
