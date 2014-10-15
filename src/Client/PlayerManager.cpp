#include <Client/PlayerManager.hpp>

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

    void PlayerManager::update(float frametime)
    {
        for(auto &player : m_players)
        {
            player.second->update(frametime);
        }
    }
}
