#ifndef CLIENT_SPRITERENDERINGSYSTEM_HPP_INCLUDED
#define CLIENT_SPRITERENDERINGSYSTEM_HPP_INCLUDED

#include <anax/System.hpp>
#include <Client/Window.hpp>

namespace Client
{
    class SpriteRenderingSystem : public anax::System<SpriteRenderingSystem>
    {
        public:
            SpriteRenderingSystem();

            void render(Window *window);
    };
}

#endif
