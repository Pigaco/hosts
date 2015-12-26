#include <iostream>
#include <PlayerManager.hpp>
#include <INIReader.h>

using std::cout;
using std::endl;

PlayerManager::PlayerManager(const int playerCount, INIReader *config)
    : m_playerCount(playerCount), m_config(config) 
{
    for(std::size_t i = 0; i < playerCount; ++i)
    {
        std::unique_ptr<Arduino> arduino(new Arduino(config->Get(("Player" + std::to_string(i)).c_str(), 
                        "SerialInterface",
                        ("/dev/ttyUSB" + std::to_string(i)).c_str()).c_str(), 
                    config));
        std::unique_ptr<Player> player(new Player(std::move(arduino)));

        m_players.push_back(std::move(player));
    }
}
PlayerManager::~PlayerManager()
{

}

void PlayerManager::send(char *buffer, int size, int player)
{
    if(player == -1)
    {
        for(std::size_t i = 0; i < m_playerCount; ++i)
        {
            m_players[i]->send(buffer, size);
        }
    }
    else
    {
        if(player < m_playerCount && player >= 0)
        {
            m_players[player]->send(buffer, size);
        }
    }
}
int PlayerManager::read(char *buffer, int size, bool &read, int player)
{
    if(player < m_playerCount && player >= 0)
    {
        return m_players[player]->read(buffer, size, read);
    }
}
void PlayerManager::sendHello(int player, bool output)
{
    bool success = false;
    if(player == -1)
    {
        for(std::size_t i = 0; i < m_playerCount; ++i)
        {
            success = m_players[i]->sendHello();
            if(output) {
                cout << "[Hello] Player " << i << " - Success: " << success << endl;
            }
        }
    }
    else
    {
        if(player < m_playerCount && player >= 0)
        {
            success = m_players[player]->sendHello();
            if(output) {
                cout << "[Hello] Player " << player << " - Success: " << success << endl;
            }
        }
    }
}
