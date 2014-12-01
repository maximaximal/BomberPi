#include <pihud/Particle.hpp>

namespace PiH
{
    Particle::Particle()
    {

    }
    Particle::~Particle()
    {

    }
    void Particle::setX(float x)
    {
        m_dstRect.x = x;
    }
    void Particle::setY(float y)
    {
        m_dstRect.y = y;
    }
    float Particle::getX()
    {
        return m_dstRect.x;
    }
    float Particle::getY()
    {
        return m_dstRect.y;
    }
    void Particle::setTextureRect(const IntRect &rect)
    {
        m_srcRect = rect;
    }
    void Particle::onUpdate(float frametime)
    {
        m_dstRect.x += velX;
        m_dstRect.y += velY;
    }
    void Particle::onRender(SDL_Renderer *renderer)
    {
        if(texture)
        {
            SDL_Rect srcRect = m_srcRect.toSDLRect();
            SDL_Rect dstRect = m_dstRect.toSDLRect();
            SDL_RenderCopyEx(renderer, texture->getSDLTexture(), &srcRect, &dstRect, rotation, nullptr, SDL_FLIP_NONE);
        }
    }
    const IntRect &Particle::getTextureRect()
    {
        return m_srcRect;
    }
}
