#pragma once

#include <stdint.h>
#include <string>
#include <functional>

class INIReader;

class Arduino
{
    public:
        typedef void (*interrupt_handler_func)(int);

        enum Mode {
            ReadWrite,
            ReadOnly,
            WriteOnly
        };
        Arduino(const char* serialPath, INIReader *config, int playerID);
        virtual ~Arduino();

        const char* serialPath();

        int send(char* buffer, int size);
        int receive(char* buffer, int size, bool &received);

        bool sendHello();
        void handleSignal(uint8_t packet);
        bool isReady();

        static bool debug;

        void registerSinglePacketCallback(std::function<void(uint8_t)> callback);
    private:
        std::string m_serialPath;
        INIReader *m_config;
        int m_fd;
        const int m_timeout = 200000;
        bool m_ready = false;

        std::function<void(uint8_t)> m_singlePacketCallback;
};
