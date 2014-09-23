#include <Client/Collision.hpp>
#include <Client/PositionComponent.hpp>
#include <Client/BodyComponent.hpp>

namespace Client
{
    Collision::Collision(anax::Entity &a, anax::Entity &b)
    {
        m_a = a;
        m_b = b;
    }
    Collision::~Collision()
    {

    }
    anax::Entity &Collision::getA()
    {
        return m_a;
    }
    anax::Entity &Collision::getB()
    {
        return m_b;
    }
    glm::dvec2 Collision::getAPos()
    {
        glm::dvec2 pos(0, 0), bodyPos(0, 0);
        if(m_a.hasComponent<BodyComponent>())
        {
            auto &body = m_a.getComponent<BodyComponent>();
            bodyPos.x = body.x;
            bodyPos.y = body.y;
        }
        if(m_a.hasComponent<PositionComponent>())
        {
            auto &posComponent = m_a.getComponent<PositionComponent>();
            pos.x = posComponent.pos.x;
            pos.y = posComponent.pos.y;
        }
        return pos + bodyPos;
    }
    glm::dvec2 Collision::getBPos()
    {
        glm::dvec2 pos(0, 0), bodyPos(0, 0);
        if(m_b.hasComponent<BodyComponent>())
        {
            auto &body = m_b.getComponent<BodyComponent>();
            bodyPos.x = body.x;
            bodyPos.y = body.y;
        }
        if(m_b.hasComponent<PositionComponent>())
        {
            auto &posComponent = m_b.getComponent<PositionComponent>();
            pos.x = posComponent.pos.x;
            pos.y = posComponent.pos.y;
        }
        return pos + bodyPos;
    }
}
