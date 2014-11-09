#ifndef CLIENT_POWERUP_HPP_INCLUDED
#define CLIENT_POWERUP_HPP_INCLUDED

#include <SDL2/SDL_rect.h>

namespace Client
{
    class Powerup
    {
        public:
            enum Predefined {
                ADDITIONAL_BOMB,
                ADDITIONAL_CORNER,
                ADDITIONAL_TILE,
                SPEED_MULTIPLICATOR_BONUS,

                _COUNT,
                NOT_DEFINED
            };

            Powerup(const Powerup &powerup);
            Powerup(Predefined definition = NOT_DEFINED);
            virtual ~Powerup();
            void reset();

            float getSpeedMultiplicatorBonus() const;
            int getAdditionalCorners() const;
            int getAdditionalTiles() const;
            short getAdditionalBombs() const;

            SDL_Rect getRect() const;
            Predefined getDefinition() const;

            //Operators.

            const Powerup operator+(const Powerup &r);
            const Powerup& operator+=(const Powerup &r);
        protected:
            float m_speedMultiplicatorBonus = 0;
            int m_additionalCorners = 0;
            int m_additionalTiles = 0;
            short m_additionalBombs = 0;
    };
}

#endif
