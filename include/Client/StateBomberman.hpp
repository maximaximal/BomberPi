#ifndef CLIENT_STATEBOMBERMAN_HPP_INCLUDED
#define CLIENT_STATEBOMBERMAN_HPP_INCLUDED

#include <State.hpp>
#include <Client/Window.hpp>

namespace Client
{
   	class StateBomberman : public State
    {
         public:
            StateBomberman();
            virtual ~StateBomberman();

            void init();

            void render(std::shared_ptr<Window> window);
        private:
    };
}

#endif
