#include <Player.hpp>

Player::Player(std::unique_ptr<Arduino> arduino)
{
    m_arduino = std::move(arduino);
}
Player::~Player()
{

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
