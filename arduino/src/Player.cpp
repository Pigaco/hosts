#include <Player.hpp>
#include "../arduino_onboard/serial_protocol.h"
#include <iostream>

using std::cout;
using std::endl;

Player::Player(std::unique_ptr<Arduino> arduino, int playerID)
    : m_playerID(playerID)
{
    m_callbackFunc = nullptr;
    using namespace std::placeholders;

    m_arduino = std::move(arduino);
    m_arduino->registerSinglePacketCallback(std::bind(&Player::arduinoCallback, this, _1));
}
Player::~Player()
{

}
void Player::setCallbackFunc(host_input_callback_func callback)
{
    m_callbackFunc = callback;
}
void Player::send(char *buffer, int size)
{
    m_arduino->send(buffer, size);
}
int Player::read(char *buffer, int size, bool &read)
{
    return m_arduino->receive(buffer, size, read);
}
bool Player::sendHello()
{
    return m_arduino->sendHello();
}
void Player::printReady()
{
    if(m_arduino->isReady()) {
        cout << "[PLAYER] ID: " << m_playerID << " is ready!" << endl;
    } else {
        cout << "[PLAYER] ID: " << m_playerID << " is NOT ready!" << endl;
    }
}
void Player::arduinoCallback(uint8_t packet)
{
    if(m_callbackFunc != nullptr)
    {
        if(packet & PACKET_TYPE_BUTTON) {
            int buttonID = packet >> 4;
            int state = 0;
            if(packet & BUTTON_STATE_ON) {
                state = 1;
            }

            //Call the callback function from the piga system.
            m_callbackFunc(buttonID, m_playerID, state);

            if(Arduino::debug) {
                cout << endl << "[ARDUINO] Button packet (" << buttonID << ":" << state << ")" << endl;
            }
        }
    }
}
