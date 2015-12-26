#pragma once

class INIReader;

class Arduino
{
    public:
        enum Mode {
            ReadWrite,
            ReadOnly,
            WriteOnly
        };
        Arduino(const char* serialPath, INIReader *config);
        virtual ~Arduino();

        const char* serialPath();

        int send(char* buffer, int size);
        int receive(char* buffer, int size, bool &received);

        bool sendHello();
    private:
        const char* m_serialPath;
        INIReader *m_config;
        int m_fd;
        const int m_timeout = 200000;
};
