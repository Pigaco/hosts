#include <arduino.hpp>
#include <iostream>
#include <bitset>

//Low level sleep and file handling for speed.
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <errno.h>

#include <INIReader.h>

using std::cout;
using std::endl;

Arduino::Arduino(const char* serialPath, INIReader *config, Arduino::Mode mode)
    : m_serialPath(serialPath), m_config(config)
{
    if(mode == ReadWrite)
        m_fd = open(serialPath, O_RDWR | O_NOCTTY);
    else if(mode == ReadOnly)
        m_fd = open(serialPath, O_RDONLY | O_NOCTTY);
    else if(mode == WriteOnly)
        m_fd = open(serialPath, O_WRONLY | O_NOCTTY);

    if(m_fd < 0) {
        cout << "[ARDUINO] Failed to connect to \"" << serialPath << "\", because handle is " << m_fd << "!" << endl 
            << "[ARDUINO] Try configuring the serial path in \"host_arduino.ini\"." << endl;
        return;
    }

    cout << "[ARDUINO] Connected " << serialPath << " at " << m_fd << endl;
    cout << "[ARDUINO] Now waiting for the arduino to reboot..." << endl;
    cout << "[ARDUINO] The arduino should be up again; the device can be active!" << endl;

    /* get current serial port settings */
    termios toptions;

    if(tcgetattr(m_fd, &toptions) != 0) {
        perror("System Error (tcgetattr)");
    }
    cfmakeraw(&toptions);
    /* 8 bits, no parity, no stop bits */
    toptions.c_cflag |= (CS8 | CLOCAL | CREAD | B115200);
    toptions.c_iflag = 0;
    toptions.c_iflag &= (IXON | IXOFF | INLCR);
    toptions.c_oflag = 0;
    toptions.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON | IEXTEN | ISIG);
    toptions.c_cc[VMIN]  = 1;
    toptions.c_cc[VTIME]  = 0;
    /* commit the serial port settings */
    if(tcsetattr(m_fd, TCSANOW, &toptions) != 0) {
        perror("System Error (tcsetattr)");
    }

    cout << "[ARDUINO] Waiting for hello..." << endl;

    char *buffer = new char[3];
    bool read;
    int count = receive(buffer, 3, read);
    if(buffer[0] == 0)
    {
        cout << "[ARDUINO] Hello packet answer received successfully (" << count << "). Arduino on \"" << serialPath << "\" functioning!" << endl;
    } else 
    {
        cout << "[ARDUINO] Didn't receive hello packet answer (" << count << ") from " << serialPath << "\". This is an error!" << endl;
    }
    cout << "[ARDUINO] Answer received: " << std::bitset<8>(buffer[0]) << endl;
    delete[] buffer;
}
Arduino::~Arduino()
{
    //Close the file again.
    close(m_fd);
}

const char* Arduino::serialPath()
{
    return m_serialPath;
}

int Arduino::send(char* buffer, int size)
{
    if(m_fd > 0) {
        return write(m_fd, buffer, size);
    }
    return 0;
}
int Arduino::receive(char* buffer, int size, bool &received)
{
    if(m_fd > 0) {
        int rec = read(m_fd, buffer, size);
        if(rec > 0) {
            received = true;
        } else {
            received = false;
        }
        return rec;
    }
    return 0;
}
