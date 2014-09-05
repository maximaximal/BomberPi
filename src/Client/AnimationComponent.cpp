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
}
