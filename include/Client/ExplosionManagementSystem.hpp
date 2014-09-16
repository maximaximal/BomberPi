#ifndef CLIENT_EXPLOSIONMANAGEMENTSYSTEM_HPP_INCLUDED
#define CLIENT_EXPLOSIONMANAGEMENTSYSTEM_HPP_INCLUDED

#include <anax/System.hpp>
#include <Client/TextureManager.hpp>

namespace Client
{
    class ExplosionManagementSystem : public anax::System<ExplosionManagementSystem>
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
