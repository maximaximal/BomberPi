#include <Client/PositionComponent.hpp>

namespace Client
{

    PositionComponent::PositionComponent()
    {
        pos.x = 0;
        pos.y = 0;
    }

    PositionComponent::PositionComponent(glm::dvec2 pos)
    {
        this->pos = pos;
    }

    PositionComponent::PositionComponent(glm::ivec2 pos)
    {
        this->pos = pos;
    }

    PositionComponent::PositionComponent(float x, float y)
    {
        pos.x = x;
        pos.y = y;
    }

    PositionComponent::~PositionComponent()
    {

    }

    float PositionComponent::getXF()
    {
        return static_cast<float>(pos.x);
    }

    float PositionComponent::getYF()
    {
        return static_cast<float>(pos.y);
    }

    int PositionComponent::getXI()
    {
        return static_cast<int>(pos.x);
    }

    int PositionComponent::getYI()
    {
        return static_cast<int>(pos.y);
    }

}
