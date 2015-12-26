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

Arduino::Arduino(const char* serialPath, INIReader *config)
    : m_serialPath(serialPath), m_config(config)
{
    m_fd = open(serialPath, O_RDWR | O_NOCTTY);

    if(m_fd < 0) {
        cout << "[ARDUINO] Failed to connect to \"" << serialPath << "\", because handle is " << m_fd << "!" << endl
            << "[ARDUINO] Try configuring the serial path in \"host_arduino.ini\"." << endl;
        return;
    }

    cout << "[ARDUINO] Connected " << serialPath << " at " << m_fd << endl;
    cout << "[ARDUINO] Now waiting for the arduino to reboot..." << endl;



    cout << "[ARDUINO] The arduino should be up again; the device can be active!" << endl;

    /* get current serial port settings */
    struct termios toptions;

    if(tcgetattr(m_fd, &toptions) != 0) {
        perror("System Error (tcgetattr)");
    }

    cfsetispeed(&toptions, B9600);
    cfsetospeed(&toptions, B9600);

    /* 8 bits, no parity, no stop bits */
    toptions.c_cflag &= ~PARENB;
    toptions.c_cflag &= ~CSTOPB;
    toptions.c_cflag &= ~CSIZE;
    toptions.c_cflag |= CS8;
    toptions.c_cflag &= ~CRTSCTS;
    toptions.c_cflag |= CREAD | CLOCAL;
    toptions.c_iflag &= ~(IXON | IXOFF | IXANY);
    toptions.c_lflag &= ~(ECHO | ECHOE | ICANON | ISIG);
    toptions.c_oflag &= ~OPOST;
    toptions.c_cc[VMIN]  = 0;
    toptions.c_cc[VTIME]  = 0;
    /* commit the serial port settings */
    if(tcsetattr(m_fd, TCSANOW, &toptions) != 0) {
        perror("System Error (tcsetattr)");
    }

    cout << "[ARDUINO] Testing sending a hello packet. (" << std::bitset<8>(2) << ")" << endl;
    if(sendHello()) {
        cout << "[ARDUINO] Hello successfully sent!" << endl;
    } else {
        cout << "[ARDUINO] Failed sending a hello packet!" << endl;
    }

    cout << "[ARDUINO] Waiting for hello..." << endl;

    char *buffer = new char[1];
    bool read;
    int count = receive(buffer, 1, read);
    if(buffer[0] == 2 && read)
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
    if(m_fd > 0)
    {
        //Close the file again.
        close(m_fd);
    }
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
    if(m_fd <= 0) {
        received = false;
        return -1;
    }

    char input[1];
    int n = 0, timeout = 0, i;

    for(i = 0; i < size; ++i) {
        n = read(m_fd, input, 1);
        if(n == -1) {
            //Read error!
            received = false;
            return -1;
        } else if(n == 0) {
            usleep(1000);
            timeout += 1000;
            if(timeout > m_timeout) {
                received = false;
                return -1;
            }
            continue;
        }
        buffer[i] = input[0];
    }
    received = true;

    if(buffer[0] == 0) {
        //No empty packages exist in this protocol!
        received = false;
        i = 0;
    }

    return i;
}
bool Arduino::sendHello()
{
    if(m_fd > 0) {
        uint8_t helloMsg = 2; //2 means 00000010, which is the packet type of hello.
        if(write(m_fd, &helloMsg, 1) != 1) {
            return false;
        } else {
            return true;
        }
    }
    return false;
}
