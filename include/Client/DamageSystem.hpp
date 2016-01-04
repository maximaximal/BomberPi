#ifndef CLIENT_DAMAGESYSTEM_HPP_INCLUDED
#define CLIENT_DAMAGESYSTEM_HPP_INCLUDED

#include <anax/System.hpp>
#include <Client/Collision.hpp>

#include <Client/BodyComponent.hpp>
#include <Client/DamageDealerComponent.hpp>
#include <Client/PositionComponent.hpp>

namespace Client 
{
    class DamageSystem : public anax::System<anax::Requires<BodyComponent, PositionComponent, DamageDealerComponent>>
    {
        public:
            DamageSystem();
            virtual ~DamageSystem();

            void update(float frametime);
            void onDamageDealerCollision(std::shared_ptr<Collision> collision);
        protected:
            virtual void onEntityAdded(anax::Entity &e);
            virtual void onEntityRemoved(anax::Entity &e);
        private:
            float m_lastFrametime = 0;
    };
}

#endif
