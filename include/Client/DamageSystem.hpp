#ifndef CLIENT_DAMAGESYSTEM_HPP_INCLUDED
#define CLIENT_DAMAGESYSTEM_HPP_INCLUDED

#include <anax/System.hpp>
#include <Client/Collision.hpp>

namespace Client 
{
    class DamageSystem : public anax::System<DamageSystem>
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
