#include <Client/AnimationComponent.hpp>

namespace Client
{

    AnimationComponent::AnimationComponent()
    {
        clear();
    }

    AnimationComponent::~AnimationComponent()
    {
     	clear();
    }
    void AnimationComponent::clear()
    {
        animation.reset();
        seconds = 0;
        currentStep = 0;
    }
    bool AnimationComponent::animationFinished()
    {
		if(animation)
        {
            if(animation->getTotalDuration() > seconds)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
}
