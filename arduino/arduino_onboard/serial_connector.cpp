#include "Arduino.h"
#include "serial_connector.h"
#include "led.h"

//Input packet defines
#include "serial_protocol.h"

/*
 * LED packet format
 * =================
 * FIRST PACKET:  IIIIILTT
 * SECOND PACKET: PPPPPPPP
 *
 * All characters stand for one bit.
 *
 * I: The LED-ID. Only 0-5 are used in this implementation.
 * L: long packet. Has to be 1
 * T: type of the packet. Has to be PACKET_TYPE_LED.
 * P: new power of the LED. 
 */

SerialConnector::SerialConnector(const int baudRate)
    : m_baudRate(baudRate)
{

}
SerialConnector::~SerialConnector()
{
    
}

void SerialConnector::setup()
{
    Serial.begin(m_baudRate);
    sendHello();
    flush();
}
void SerialConnector::flush()
{
    Serial.flush();
}
void SerialConnector::loop()
{
    while(Serial.available() > 0)
    {
        delay(1);

        //Read the new byte into the internal buffer. 
        Serial.readBytes(&m_serialInput[2], 1);

        if(m_serialInput[0] & PACKET_LENGTH_MULTIPLE)
        {
            m_serialInput[1] = m_serialInput[2];

            handleLongPacket();

            m_serialInput[0] = 0;
            m_serialInput[1] = 0;
        }
        else
        {
            m_serialInput[0] = m_serialInput[2];

            if(!(m_serialInput[0] & PACKET_LENGTH_MULTIPLE))
            {
                handleShortPacket();
            }
        }
    }
}
void SerialConnector::sendHello()
{
    byte hello = 2;
    Serial.write(hello);
}
void SerialConnector::handleHello(byte packet)
{
    //Turn off the status LED -> Everything OK
    digitalWrite(13, LOW);
}
void SerialConnector::handleLongPacket()
{
    if(m_serialInput[0] & PACKET_TYPE_LED)
    {
        //This packet controls a LED!
        uint8_t ledID = m_serialInput[0] >> 3;
        leds[ledID]->setPwr(m_serialInput[1]);
    }
}
void SerialConnector::handleShortPacket()
{
    if(m_serialInput[0] & PACKET_TYPE_HELLO)
    {
        //This was a hello packet! We need to send a hello packet back.
        handleHello(m_serialInput[0]);
    }
    m_serialInput[0] = 0;
}

void SerialConnector::sendInput(uint8_t button, bool state)
{
    byte packet = 0;

    if(state) 
    {
        packet = BUTTON_STATE_ON | PACKET_TYPE_BUTTON | PACKET_LENGTH_SINGLE; 
    }
    else
    {
        packet = BUTTON_STATE_OFF | PACKET_TYPE_BUTTON | PACKET_LENGTH_SINGLE; 
    }

    switch(button)
    {
        case 0:
            packet |= BUTTON_ID_0;
            break;
        case 1:
            packet |= BUTTON_ID_1;
            break;
        case 2:
            packet |= BUTTON_ID_2;
            break;
        case 3:
            packet |= BUTTON_ID_3;
            break;
        case 4:
            packet |= BUTTON_ID_4;
            break;
        case 5:
            packet |= BUTTON_ID_5;
            break;
        case 6:
            packet |= BUTTON_ID_6;
            break;
        case 7:
            packet |= BUTTON_ID_7;
            break;
        case 8:
            packet |= BUTTON_ID_8;
            break;
        case 9:
            packet |= BUTTON_ID_9;
            break;
        case 10:
            packet |= BUTTON_ID_10;
            break;
        case 11:
            packet |= BUTTON_ID_11;
            break;
        case 12:
            packet |= BUTTON_ID_12;
            break;
        case 13:
            packet |= BUTTON_ID_13;
            break;
        case 14:
            packet |= BUTTON_ID_14;
            break;
        case 15:
            packet |= BUTTON_ID_15;
            break;
    }

    //Send the packet!
    Serial.write(packet);
}
