#include <Client/AnimationSystem.hpp>

#include <Client/AnimationComponent.hpp>
#include <Client/SpriteComponent.hpp>

namespace Client
{
    AnimationSystem::AnimationSystem()
    {

    }
    AnimationSystem::~AnimationSystem()
    {

    }
    void AnimationSystem::update(float frametime)
    {
        for(auto &entity : getEntities())
        {
            auto &animation = entity.getComponent<AnimationComponent>();
            auto &sprite = entity.getComponent<SpriteComponent>();

            animation.seconds += frametime;

            if(animation.animation)
            {
				if(animation.animation->getStepDuration() <= animation.seconds)
                {
                    animation.seconds = 0;
                    if(animation.currentStep < animation.animation->getStepCount() - 1)
                        ++animation.currentStep;
                    else
                    {
                        if(animation.killAfterFinish)
                        {
                            entity.kill();
                        }
                        else
                        {
                            animation.currentStep = 0;
                            animation.finished = true;
                        }
                    }
                }
                sprite.srcRect = animation.animation->getStep(animation.currentStep);
            }
        }
    }
}
