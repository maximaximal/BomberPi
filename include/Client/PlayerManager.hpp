#ifndef CLIENT_PLAYERMANAGER_HPP_INCLUDED
#define CLIENT_PLAYERMANAGER_HPP_INCLUDED

#include <memory>
#include <string>
#include <map>
#include <Client/Player.hpp>

namespace Client
{
    class PlayerManager
    {
        public:
            typedef std::map<std::string, std::shared_ptr<Player> > PlayerMap;

            PlayerManager();
            virtual ~PlayerManager();

            std::shared_ptr<Player> get(const std::string &name);
            void set(std::shared_ptr<Player> player, const std::string &name);

            std::shared_ptr<Player> operator[](const std::string &index) {return get(index);}

            PlayerMap& getPlayers();

            void update(float frametime);
        private:
            std::map<std::string, std::shared_ptr<Player> > m_players;
    };
}

#endif
