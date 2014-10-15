#include <Client/PlayerManager.hpp>
#include <easylogging++.h>

namespace Client
{
    PlayerManager::PlayerManager()
    {

    }
    PlayerManager::~PlayerManager()
    {

    }
    std::shared_ptr<Player> PlayerManager::get(const std::string &name)
    {
		if(m_players.count(name) > 0)
        {
            return m_players[name];
        }
        else
        {
            throw std::out_of_range("The player you requested is not listed in the player manager!");
        }
    }
    void PlayerManager::set(std::shared_ptr<Player> player, const std::string &name)
    {
        m_players[name] = player;
    }

    std::vector<glm::ivec2> PlayerManager::getPlayerPositions(int coordinateDivider)
    {
        std::vector<glm::ivec2> positions;
        for(auto &player : m_players)
        {
            positions.push_back(player.second->getPosition() / coordinateDivider);
        }
        return positions;
    }
    PlayerManager::PlayerMap &PlayerManager::getPlayers()
    {
        return m_players;
    }
    int PlayerManager::getPlayerCount()
    {
        return m_players.size();
    }
    int PlayerManager::getAlivePlayerCount()
    {
        int alivePlayers = getPlayerCount();
        for(auto &player : m_players)
        {
            if(player.second)
            {
				if(player.second->isDead())
					--alivePlayers;
            }
        }
        return alivePlayers;
    }

    void PlayerManager::resetPlayers()
    {
        for(auto &player : m_players)
        {
            player.second->reset();
        }
    }
    void PlayerManager::update(float frametime)
    {
        for(auto &player : m_players)
        {
            if(player.second)
            {
				player.second->update(frametime);
            }
            else
            {
                m_players.erase(player.first);
            }
        }
    }
}
