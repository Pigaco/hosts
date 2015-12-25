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
        Arduino(const char* serialPath, INIReader *config, Arduino::Mode mode);
        virtual ~Arduino();

        const char* serialPath();

        int send(char* buffer, int size);
        int receive(char* buffer, int size, bool &received);
    private:
        const char* m_serialPath;
        INIReader *m_config;
        int m_fd;
};
