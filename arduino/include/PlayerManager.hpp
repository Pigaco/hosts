#pragma once

#include <vector>
#include <memory>

#include <Player.hpp>

class INIReader;

class PlayerManager
{
    public:
        PlayerManager(const int playerCount, INIReader *config);
        ~PlayerManager();

        void send(char *buffer, int size, int player = -1);
    private:
        std::vector<std::unique_ptr<Player> > m_players;
        const int m_playerCount;
        INIReader *m_config;
};
