#include <Client/WinChecker.hpp>

namespace Client
{
    WinChecker::WinChecker(PlayerManager *playerManager)
    {
		m_playerManager = playerManager;
    }
    WinChecker::~WinChecker()
    {

    }
    bool WinChecker::winDetected()
    {
        if(m_playerManager->getAlivePlayerCount() <= 1 && m_playerManager->getPlayerCount() > 1)
        {
            return true;
        }
        return false;
    }
    std::shared_ptr<Player> WinChecker::getWinner()
    {
		for(auto &player : m_playerManager->getPlayers())
        {
            if(!player.second->isDead())
            {
                return player.second;
            }
        }
        throw std::out_of_range("No alive player found!");
    }
}
