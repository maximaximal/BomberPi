#ifndef CLIENT_SPRITERENDERINGSYSTEM_HPP_INCLUDED
#define CLIENT_SPRITERENDERINGSYSTEM_HPP_INCLUDED

#include <anax/System.hpp>
#include <Client/Window.hpp>

#include <Client/SpriteComponent.hpp>
#include <Client/PositionComponent.hpp>

namespace Client
{
    class SpriteRenderingSystem : public anax::System<anax::Requires<SpriteComponent, PositionComponent>>
    {
        public:
            SpriteRenderingSystem();

            void render(Window *window, const glm::ivec2 &offset);
    };
}

#endif
