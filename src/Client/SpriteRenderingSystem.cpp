#include <Client/SpriteRenderingSystem.hpp>
#include <easylogging++.h>
#include <SDL2/SDL.h>

#include <Client/SpriteComponent.hpp>
#include <Client/PositionComponent.hpp>

namespace Client
{
    SpriteRenderingSystem::SpriteRenderingSystem()
    	: Base(anax::ComponentFilter().requires<SpriteComponent, PositionComponent>())
    {

    }
    void SpriteRenderingSystem::render(Window *window, const glm::ivec2 &offset)
    {
        SDL_Rect dstRect;
        dstRect.x = 0;
        dstRect.y = 0;
        dstRect.w = 0;
        dstRect.h = 0;
		for(anax::Entity &entity : getEntities())
        {
           	auto pos = entity.getComponent<PositionComponent>();
            auto sprite = entity.getComponent<SpriteComponent>();

            if(sprite.texture)
            {
				dstRect.x = pos.pos.x + offset.x;
				dstRect.y = pos.pos.y + offset.y;
				dstRect.w = sprite.srcRect.w;
				dstRect.h = sprite.srcRect.h;

				SDL_RenderCopyEx(window->getSDLRenderer(),
								 sprite.texture->getSDLTexture(),
								 &sprite.srcRect,
								 &dstRect,
								 sprite.rotation,
								 nullptr,
								 sprite.rendererFlip);
            }
        }
    }

}
