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
            enum Side {
                LEFT,
                TOP,
                RIGHT,
                BOTTOM,
                NONE,

                NOT_CACHED
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
            Side getSide();

            glm::dvec2 getPenetrationVec();

            bool isObstructed(float amount);
        private:
            struct VectorRect {
                    glm::dvec2 v1;
                    glm::dvec2 v2;
                    glm::dvec2 v3;
                    glm::dvec2 v4;
            };

            anax::Entity m_aEntity;
            anax::Entity m_bEntity;
            SDL_Rect *m_aRect = nullptr;
            SDL_Rect *m_bRect = nullptr;

            Collision::Type m_type;
            Collision::Side m_sideCache = NOT_CACHED;
    };
}

#endif // CLIENT_COLLISION_HPP_INCLUDED
