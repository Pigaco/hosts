#pragma once

class INIReader;

class Arduino
{
    public:
        Arduino(const char* serialPath, INIReader *config, Mode mode);
        virtual ~Arduino();

        const char* serialPath();

        int send(char* buffer, int size);
        int receive(char* buffer, bool &received);

        enum Mode {
            ReadWrite,
            ReadOnly,
            WriteOnly
        }
    private:
        const char* m_serialPath;
        INIReader *m_config;
        int m_fd;
};
