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

#include <QSerialPort>
#include <QSerialPortInfo>

#include <INIReader.h>

#include "../arduino_onboard/serial_protocol.h"

using std::cout;
using std::endl;

bool Arduino::debug = false;
char readCache;

Arduino::Arduino(const char* serialPath, INIReader *config, int playerID)
    : m_config(config), m_serialPath(serialPath)
{
    cout << "[ARDUINO] Trying to connect to " << serialPath << endl;
    QSerialPortInfo info(QString::fromUtf8(serialPath));

    m_serialPort = new QSerialPort(info);
    m_serialPort->setPortName(QString::fromUtf8(serialPath));

    if(m_serialPort->open(QIODevice::ReadWrite))
    {
        cout << "[ARDUINO] Serial connection opened successfully." << endl;
    }
    else 
    {
        cout << "[ARDUINO] Serial connection could not be opened! Ending initialization of " << m_serialPort->portName().toStdString() << endl;
        cout << "[ARDUINO] Error: " << m_serialPort->errorString().toStdString() << endl;
        return;
    }

    QObject::connect(m_serialPort, &QSerialPort::readyRead,
            [=](){
                char c;

                while(m_serialPort->getChar(&c))
                {
                    handleSignal(static_cast<uint8_t>(c));
                }
            });

    if(!m_serialPort->setBaudRate(QSerialPort::Baud9600, QSerialPort::Input))
        cout << "[ARDUINO] Error: " << m_serialPort->errorString().toStdString() << endl;
    if(!m_serialPort->setBaudRate(QSerialPort::Baud9600, QSerialPort::Output))
        cout << "[ARDUINO] Error: " << m_serialPort->errorString().toStdString() << endl;
    if(!m_serialPort->setParity(QSerialPort::NoParity))
        cout << "[ARDUINO] Error: " << m_serialPort->errorString().toStdString() << endl;
    if(!m_serialPort->setStopBits(QSerialPort::OneStop))
        cout << "[ARDUINO] Error: " << m_serialPort->errorString().toStdString() << endl;
    if(!m_serialPort->setDataBits(QSerialPort::Data8))
        cout << "[ARDUINO] Error: " << m_serialPort->errorString().toStdString() << endl;
    if(!m_serialPort->setFlowControl(QSerialPort::NoFlowControl))
        cout << "[ARDUINO] Error: " << m_serialPort->errorString().toStdString() << endl;
    if(!m_serialPort->setRequestToSend(false))
        cout << "[ARDUINO] Error: " << m_serialPort->errorString().toStdString() << endl;
    if(!m_serialPort->setDataTerminalReady(false))
        cout << "[ARDUINO] Error: " << m_serialPort->errorString().toStdString() << endl;

    m_serialPort->flush();
}
Arduino::~Arduino()
{
    if(m_serialPort != nullptr)
    {
        delete m_serialPort;
    }
}

const char* Arduino::serialPath()
{
    return m_serialPath.c_str();
}

int Arduino::send(char* buffer, int size)
{
    return m_serialPort->write(buffer, size);
}
int Arduino::receive(char* buffer, int size, bool &received)
{

}
bool Arduino::sendHello()
{
    char helloPacket = 2;

    if(m_serialPort->putChar(helloPacket))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Arduino::handleSignal(uint8_t packet)
{
    if(debug) {
        cout << endl << "[ARDUINO] Packet from \"" << m_serialPath << "\": " << std::bitset<8>(packet) << endl;
    }

    if(packet == 2) {
        if(debug) {
            cout << endl << "[ARDUINO] Received hello packet from \"" << m_serialPath << "\"! Sending answer." << endl;
        }
        if(!m_ready) {
            sendHello();
            m_ready = true;
        }
    } else if(m_ready) {
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
