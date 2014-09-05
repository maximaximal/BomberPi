#ifndef CLIENT_SPRITECOMPONENT_HPP
#define CLIENT_SPRITECOMPONENT_HPP

#include <anax/Component.hpp>
#include <Client/Texture.hpp>
#include <SDL2/SDL.h>

namespace Client
{
    class SpriteComponent : public anax::Component<SpriteComponent>
    {
        public:
			SpriteComponent();
			SpriteComponent(std::shared_ptr<Texture> texture);
			SpriteComponent(std::shared_ptr<Texture> texture, const SDL_Rect &srcRect);

            virtual ~SpriteComponent();

			void clear();

			std::shared_ptr<Texture> texture;
			SDL_Rect srcRect;
            double rotation = 0;
			SDL_RendererFlip rendererFlip;
    };
}

#endif
