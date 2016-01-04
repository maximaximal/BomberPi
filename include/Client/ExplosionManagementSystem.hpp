#ifndef CLIENT_EXPLOSIONMANAGEMENTSYSTEM_HPP_INCLUDED
#define CLIENT_EXPLOSIONMANAGEMENTSYSTEM_HPP_INCLUDED

#include <anax/System.hpp>
#include <Client/TextureManager.hpp>

#include <Client/AnimationComponent.hpp>
#include <Client/PositionComponent.hpp>

namespace Client
{
    class ExplosionManagementSystem : public anax::System<anax::Requires<AnimationComponent, PositionComponent>>
    {
    	public:
            ExplosionManagementSystem(TextureManager *textureManager);
            virtual ~ExplosionManagementSystem();

            void update(float frameTime);
        private:
            TextureManager *m_textureManager;
    };
}

#endif
