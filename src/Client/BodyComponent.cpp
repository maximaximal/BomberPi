#include <Client/BodyComponent.hpp>

namespace Client
{
    BodyComponent::BodyComponent()
    {

    }
    BodyComponent::BodyComponent(float x, float y, float w, float h)
    {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
    }
    BodyComponent::~BodyComponent()
    {

    }
}
