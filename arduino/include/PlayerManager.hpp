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
        int read(char *buffer, int size, bool &read, int player);
        void sendHello(int player = -1, bool output = false);
    private:
        std::vector<std::unique_ptr<Player> > m_players;
        const int m_playerCount;
        INIReader *m_config;
};
