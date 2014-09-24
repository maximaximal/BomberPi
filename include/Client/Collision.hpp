#ifndef CLIENT_COLLISION_HPP_INCLUDED
#define CLIENT_COLLISION_HPP_INCLUDED

#include <SDL2/SDL_rect.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <anax/Entity.hpp>

namespace Client
{
    class Collision
    {
        public:
            enum Type {
                EntityWithRect,
                EntityWithEntity
            };

            Collision(anax::Entity &a, anax::Entity &b);
            Collision(anax::Entity &a, const SDL_Rect &b);

            virtual ~Collision();

            anax::Entity& getA();
            anax::Entity& getB();

            glm::dvec2 getAPos();
            glm::dvec2 getBPos();

            SDL_Rect getARect();
            SDL_Rect getBRect();

            Type getType();

            glm::dvec2 getPenetrationVec();
        private:
            anax::Entity m_aEntity;
            anax::Entity m_bEntity;
            SDL_Rect *m_aRect = nullptr;
            SDL_Rect *m_bRect = nullptr;

            Collision::Type m_type;
    };
}

#endif // CLIENT_COLLISION_HPP_INCLUDED
