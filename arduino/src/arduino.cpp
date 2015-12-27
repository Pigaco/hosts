#include <arduino.hpp>
#include <iostream>
#include <bitset>

//Low level sleep and file handling for speed.
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <errno.h>

#include <INIReader.h>

#include "../arduino_onboard/serial_protocol.h"

using std::cout;
using std::endl;

bool Arduino::debug = false;

Arduino *arduinos[16];
char buffer[32];

void handleSignal(Arduino *arduino)
{
    for(std::size_t i = 0; i < 32; ++i) {
        buffer[i] = 0;
    }

    bool received = false;

    arduino->receive(buffer, 32, received);

    if(received) {
        for(std::size_t i = 0; i < 32 && buffer[i] != 0; ++i) {
            arduino->handleSignal(static_cast<uint8_t>(buffer[i]));
        }
    }
}

Arduino::Arduino(const char* serialPath, INIReader *config, int playerID)
    : m_config(config)
{
    arduinos[playerID] = this;
    m_serialPath = serialPath;

    m_fd = open(serialPath, O_RDWR | O_NOCTTY | O_NDELAY);
    if(m_fd < 0) {
        cout << "[ARDUINO] Failed to connect to \"" << serialPath << "\", because handle is " << m_fd << "!" << endl
             << "[ARDUINO] Try configuring the serial path in \"host_arduino.ini\"." << endl;
        return;
    }

    cout << "[ARDUINO] Connected " << serialPath << " at " << m_fd << endl;
    cout << "[ARDUINO] Now waiting for the arduino to reboot..." << endl;



    cout << "[ARDUINO] The arduino should be up again; the device can be active!" << endl;

    // Configure the interrupt callback
    struct sigaction saio;

    switch(playerID) {
        case 0:
            saio.sa_handler = [](int status) {::handleSignal(arduinos[0]);};
            break;
        case 1:
            saio.sa_handler = [](int status) {::handleSignal(arduinos[1]);};
            break;
        case 2:
            saio.sa_handler = [](int status) {::handleSignal(arduinos[2]);};
            break;
        case 3:
            saio.sa_handler = [](int status) {::handleSignal(arduinos[3]);};
            break;
        case 4:
            saio.sa_handler = [](int status) {::handleSignal(arduinos[4]);};
            break;
        case 5:
            saio.sa_handler = [](int status) {::handleSignal(arduinos[5]);};
            break;
        case 6:
            saio.sa_handler = [](int status) {::handleSignal(arduinos[6]);};
            break;
        case 7:
            saio.sa_handler = [](int status) {::handleSignal(arduinos[7]);};
            break;
        case 8:
            saio.sa_handler = [](int status) {::handleSignal(arduinos[8]);};
            break;
        case 9:
            saio.sa_handler = [](int status) {::handleSignal(arduinos[9]);};
            break;
        case 10:
            saio.sa_handler = [](int status) {::handleSignal(arduinos[10]);};
            break;
        case 11:
            saio.sa_handler = [](int status) {::handleSignal(arduinos[11]);};
            break;
        case 12:
            saio.sa_handler = [](int status) {::handleSignal(arduinos[12]);};
            break;
        case 13:
            saio.sa_handler = [](int status) {::handleSignal(arduinos[13]);};
            break;
        case 14:
            saio.sa_handler = [](int status) {::handleSignal(arduinos[14]);};
            break;
        case 15:
            saio.sa_handler = [](int status) {::handleSignal(arduinos[15]);};
            break;
        default:
            saio.sa_handler = [](int status) {
                //No handler defined!
            };
            break;
    }

    saio.sa_flags = 0;
    saio.sa_restorer = NULL;
    sigaction(SIGIO, &saio, NULL);

    fcntl(m_fd, F_SETFL, FNDELAY);
    fcntl(m_fd, F_SETOWN, getpid());
    fcntl(m_fd, F_SETFL, O_ASYNC);

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

    cout << "[ARDUINO] Waiting for the hello packet to arrive." << endl;
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
    return m_serialPath.c_str();
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

void Arduino::handleSignal(uint8_t packet)
{
    if(debug) {
        cout << endl << "[ARDUINO] Packet from \"" << m_serialPath << "\": " << std::bitset<8>(packet) << endl;
    }

    if(packet & PACKET_TYPE_HELLO) {
        if(debug) {
            cout << endl << "[ARDUINO] Received hello packet from \"" << m_serialPath << "\"! Sending answer." << endl;
        }
        if(sendHello()) {
            //This arduino is ready!
            m_ready = true;
        }
    } else {
        if(m_singlePacketCallback) {
            m_singlePacketCallback(packet);
        }
    }
}
bool Arduino::isReady()
{
    return m_ready;
}
void Arduino::registerSinglePacketCallback(std::function<void (uint8_t)> callback)
{
    m_singlePacketCallback = callback;
}
