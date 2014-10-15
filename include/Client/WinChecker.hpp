#ifndef CLIENT_WINCHECKER_HPP
#define CLIENT_WINCHECKER_HPP

#include <Client/Player.hpp>
#include <Client/PlayerManager.hpp>

namespace Client
{
    class WinChecker
    {
        public:
            WinChecker(PlayerManager *playerManager);
            virtual ~WinChecker();

            bool winDetected();
            std::shared_ptr<Player> getWinner();
        private:
            PlayerManager *m_playerManager;
    };
}

#endif
