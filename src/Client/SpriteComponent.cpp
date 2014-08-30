#include <Client/SpriteComponent.hpp>

namespace Client
{
    SpriteComponent::SpriteComponent()
    {
        clear();
    }
    SpriteComponent::SpriteComponent(std::shared_ptr<Texture> texture)
    {
        clear();
		this->texture = texture;
    }
    SpriteComponent::SpriteComponent(std::shared_ptr<Texture> texture, const SDL_Rect &srcRect)
    {
        clear();
        this->texture = texture;
        this->srcRect = srcRect;
    }

    SpriteComponent::~SpriteComponent()
    {

    }
    void SpriteComponent::clear()
    {
        srcRect.x = 0;
        srcRect.y = 0;
        srcRect.w = 0;
        srcRect.h = 0;
        rotation = 0;
        texture.reset();
    }
}
