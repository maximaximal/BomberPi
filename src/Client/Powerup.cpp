#include <Client/Powerup.hpp>

namespace Client
{
    Powerup::Powerup(const Powerup &powerup)
    {
        m_additionalBombs = powerup.getAdditionalBombs();
        m_additionalCorners = powerup.getAdditionalCorners();
        m_additionalTiles = powerup.getAdditionalTiles();
        m_speedMultiplicatorBonus = powerup.getSpeedMultiplicatorBonus();
    }
    Powerup::Powerup(Powerup::Predefined definition)
    {
        switch(definition)
        {
            case NOT_DEFINED:
                //The powerup was not defined!
                break;
            case _COUNT:
                //This should not be the case.
                break;
            case ADDITIONAL_BOMB:
                m_additionalBombs = 1;
                break;
            case ADDITIONAL_CORNER:
                m_additionalCorners = 1;
                break;
            case ADDITIONAL_TILE:
                m_additionalTiles = 1;
                break;
            case SPEED_MULTIPLICATOR_BONUS:
                m_speedMultiplicatorBonus = 0.25;
                break;
        }
    }
    Powerup::~Powerup()
    {

    }
    void Powerup::reset()
    {
        m_additionalBombs = 0;
        m_additionalCorners = 0;
        m_additionalTiles = 0;
        m_speedMultiplicatorBonus = 0;
    }
    float Powerup::getSpeedMultiplicatorBonus() const
    {
        return m_speedMultiplicatorBonus;
    }
    int Powerup::getAdditionalCorners() const
    {
        return m_additionalCorners;
    }
    int Powerup::getAdditionalTiles() const
    {
        return m_additionalTiles;
    }
    short Powerup::getAdditionalBombs() const
    {
        return m_additionalBombs;
    }
    SDL_Rect Powerup::getRect() const
    {
        SDL_Rect rect;
        rect.x = 0;
        rect.y = 0;
        rect.w = 32;
        rect.h = 32;
        switch(getDefinition())
        {
            case NOT_DEFINED:
                rect.y = 128;
                break;
            case _COUNT:
                //This should not be the case.
                break;
            case ADDITIONAL_BOMB:
                rect.y = 0;
                break;
            case ADDITIONAL_CORNER:
                rect.y = 96;
                break;
            case ADDITIONAL_TILE:
                rect.y = 64;
                break;
            case SPEED_MULTIPLICATOR_BONUS:
                rect.y = 32;
                break;
        }
        return rect;
    }
    Powerup::Predefined Powerup::getDefinition() const
    {
        if(m_additionalBombs > 0)
            return ADDITIONAL_BOMB;
        if(m_additionalCorners > 0)
            return ADDITIONAL_CORNER;
        if(m_additionalTiles > 0)
            return ADDITIONAL_TILE;
        if(m_speedMultiplicatorBonus > 0)
            return SPEED_MULTIPLICATOR_BONUS;

        return NOT_DEFINED;
    }
    const Powerup Powerup::operator+(const Powerup &r)
    {
        Powerup tmp(*this);
        tmp += r;
        return tmp;
    }
    const Powerup &Powerup::operator+=(const Powerup &r)
    {
        m_additionalBombs += r.getAdditionalBombs();
        m_additionalCorners += r.getAdditionalCorners();
        m_additionalTiles += r.getAdditionalTiles();
        m_speedMultiplicatorBonus += r.getSpeedMultiplicatorBonus();
        return *this;
    }
}
