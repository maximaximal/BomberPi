#include <Client/ExplosionManagementSystem.hpp>

#include <Client/AnimationComponent.hpp>
#include <Client/PositionComponent.hpp>

namespace Client
{
    ExplosionManagementSystem::ExplosionManagementSystem(TextureManager *textureManager)
    	: Base(anax::ComponentFilter().requires<AnimationComponent, PositionComponent>())
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

            if(animation.animationFinished())
            {
                entity.kill();
            }
        }
    }
}
