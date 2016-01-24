#include <Client/ExplosionManagementSystem.hpp>

namespace Client
{
    ExplosionManagementSystem::ExplosionManagementSystem(TextureManager *textureManager)
    {
       	m_textureManager = textureManager;
    }
    ExplosionManagementSystem::~ExplosionManagementSystem()
    {

    }
    void ExplosionManagementSystem::update(float frameTime)
    {
        for(auto &entity : getEntities())
        {
			auto &pos = entity.getComponent<PositionComponent>();
            auto &animation = entity.getComponent<AnimationComponent>();
            if(animation.killAfterFinish)
            {
                if(animation.finished)
                {
                }
            }
        }
    }
}
