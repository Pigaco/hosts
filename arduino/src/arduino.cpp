#include <arduino.hpp>
#include <iostream>

//Low level sleep and file handling for speed.
#include <unistd.h>
#include <fcntl.h>

#include <INIReader.h>

using std::cout;
using std::endl;

Arduino::Arduino(const char* serialPath, INIReader *config, Mode mode)
    : m_serialPath(serialPath), m_config(config)
{
    if(mode == ReadWrite)
        m_fd = open(serialPath, O_RWDR | O_BINARY);
    else if(mode == ReadOnly)
        m_fd = open(serialPath, O_RDONLY | O_BINARY);
    else if(mode == WriteOnly)
        m_fd = open(serialPath, O_WRONLY | O_BINARY);

    cout << "[ARDUINO] Connected " << serialPath << " at " << m_fd << endl;
    cout << "[ARDUINO] Now waiting for the arduino to reboot..." << endl;
    usleep(3500000);
    cout << "[ARDUINO] The arduino should be up again; the device can be active!";

    /* get current serial port settings */
    tcgetattr(fd, &toptions);
    /* set 9600 baud both ways */
    cfsetispeed(&toptions, B9600);
    cfsetospeed(&toptions, B9600);
    /* 8 bits, no parity, no stop bits */
    toptions.c_cflag &= ~PARENB;
    toptions.c_cflag &= ~CSTOPB;
    toptions.c_cflag &= ~CSIZE;
    toptions.c_cflag |= CS8;
    /* Canonical mode */
    toptions.c_lflag |= ICANON;
    /* commit the serial port settings */
    tcsetattr(fd, TCSANOW, &toptions);
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
    return write(m_fd, buffer, size);
}
int Arduino::receive(char* buffer, bool &received)
{

}
