#include <Client/AnimationComponent.hpp>

namespace Client
{

    AnimationComponent::AnimationComponent()
    {
        clear();
    }

    AnimationComponent::AnimationComponent(std::shared_ptr<Animation> animation, bool killAfterFinish)
    {
        clear();
        this->animation = animation;
        this->killAfterFinish = killAfterFinish;
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
        killAfterFinish = false;
        finished = false;
    }
}
