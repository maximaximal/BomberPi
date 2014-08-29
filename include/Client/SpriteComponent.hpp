#ifndef CLIENT_SPRITECOMPONENT_HPP
#define CLIENT_SPRITECOMPONENT_HPP

#include <anax/Component.hpp>
#include <Client/Texture.hpp>

namespace Client
{
    struct SpriteComponent : anax::Component<SpriteComponent>
    {
		SpriteComponent();
		SpriteComponent(std::shared_ptr<Texture> texture);
		SpriteComponent(std::shared_ptr<Texture> texture, const SDL_Rect &srcRect);

        void clear();

        std::shared_ptr<Texture> texture;
        SDL_Rect srcRect;
    };
}

#endif
