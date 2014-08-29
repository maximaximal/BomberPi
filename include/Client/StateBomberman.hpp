#ifndef CLIENT_STATEBOMBERMAN_HPP_INCLUDED
#define CLIENT_STATEBOMBERMAN_HPP_INCLUDED

#include <State.hpp>
#include <Client/Window.hpp>
#include <Client/BombermanMap.hpp>
#include <anax/World.hpp>

namespace Client
{
   	class StateBomberman : public State
    {
         public:
            StateBomberman();
            virtual ~StateBomberman();

            void init();

            virtual void render(std::shared_ptr<Window> window);
        private:
            std::shared_ptr<BombermanMap> m_map;

			std::shared_ptr<anax::World> m_world;
    };
}

#endif
