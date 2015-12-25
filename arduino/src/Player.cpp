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
