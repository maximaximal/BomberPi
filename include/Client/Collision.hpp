#ifndef CLIENT_COLLISION_HPP_INCLUDED
#define CLIENT_COLLISION_HPP_INCLUDED

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <anax/Entity.hpp>

namespace Client
{
    class Collision
    {
        public:
            Collision(anax::Entity &a, anax::Entity &b);
            virtual ~Collision();

            anax::Entity& getA();
            anax::Entity& getB();

            glm::dvec2 getAPos();
            glm::dvec2 getBPos();
        private:
            anax::Entity m_a;
            anax::Entity m_b;
    };
}

#endif // CLIENT_COLLISION_HPP_INCLUDED
