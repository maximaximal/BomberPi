#include <Client/Collision.hpp>
#include <Client/PositionComponent.hpp>
#include <Client/BodyComponent.hpp>
#include <easylogging++.h>

namespace Client
{
    Collision::Collision(anax::Entity &a, anax::Entity &b)
    {
        m_aEntity = a;
        m_bEntity = b;

        m_type = Type::EntityWithEntity;
    }

    Collision::Collision(anax::Entity &a, const SDL_Rect &b)
    {
        m_aEntity = a;
        m_bRect = new SDL_Rect;
        m_bRect->x = b.x;
        m_bRect->y = b.y;
        m_bRect->w = b.w;
        m_bRect->h = b.h;
        m_type = Type::EntityWithRect;
    }
    Collision::~Collision()
    {
		if(m_aRect != nullptr)
            delete m_aRect;
        if(m_bRect != nullptr)
            delete m_bRect;
    }
    anax::Entity &Collision::getA()
    {
        return m_aEntity;
    }
    anax::Entity &Collision::getB()
    {
        return m_bEntity;
    }
    glm::dvec2 Collision::getAPos()
    {
        if(m_aRect != nullptr)
        {
            return glm::dvec2(m_aRect->x, m_aRect->y);
        }
        glm::dvec2 pos(0, 0);
        if(m_aEntity.hasComponent<BodyComponent>())
        {
            auto &body = m_aEntity.getComponent<BodyComponent>();
            pos.x += body.x;
            pos.y += body.y;
        }
        if(m_aEntity.hasComponent<PositionComponent>())
        {
            auto &posComponent = m_aEntity.getComponent<PositionComponent>();
            pos.x += posComponent.pos.x;
            pos.y += posComponent.pos.y;
            LOG(INFO) << "HAS POS: " << posComponent.pos.x << "x" << posComponent.pos.y;
        }
        return pos;
    }
    glm::dvec2 Collision::getBPos()
    {
        if(m_bRect != nullptr)
        {
            return glm::dvec2(m_bRect->x, m_bRect->y);
        }
        glm::dvec2 pos(0, 0);
        if(m_bEntity.hasComponent<BodyComponent>())
        {
            auto &body = m_bEntity.getComponent<BodyComponent>();
            pos.x += body.x;
            pos.y += body.y;
        }
        if(m_bEntity.hasComponent<PositionComponent>())
        {
            auto &posComponent = m_bEntity.getComponent<PositionComponent>();
            pos.x = posComponent.pos.x;
            pos.y = posComponent.pos.y;
        }
        return pos;
    }
    SDL_Rect Collision::getARect()
    {
        if(m_aRect != nullptr)
        {
            return *m_aRect;
        }
        SDL_Rect rect;
        glm::dvec2 pos = getAPos();
        rect.x = pos.x;
        rect.y = pos.y;
        if(m_aEntity.hasComponent<BodyComponent>())
        {
            auto &body = m_aEntity.getComponent<BodyComponent>();
            rect.w = body.w;
            rect.h = body.h;
        }
        return rect;
    }
    SDL_Rect Collision::getBRect()
    {
        if(m_bRect != nullptr)
        {
            return *m_bRect;
        }
        SDL_Rect rect;
        glm::dvec2 pos = getBPos();
        rect.x = pos.x;
        rect.y = pos.y;
        if(m_bEntity.hasComponent<BodyComponent>())
        {
            auto &body = m_bEntity.getComponent<BodyComponent>();
            rect.w = body.w;
            rect.h = body.h;
        }
        return rect;
    }
    Collision::Type Collision::getType()
    {
        return m_type;
    }

    glm::dvec2 Collision::getPenetrationVec()
    {
        glm::dvec2 penetrationVec;

        SDL_Rect a, b;
		a = getARect();
        b = getBRect();

		if(a.x > b.x + b.w / 2)
            penetrationVec.x = a.x - (b.x + b.w);
        else
            penetrationVec.x = (a.x + a.w) - b.x;
        if(a.y + a.h > b.y && a.y < b.y + b.h)
            penetrationVec.x = a.y - (b.y + b.h);
        else
            penetrationVec.y = (a.y + a.h) - b.y;


        LOG(INFO) << "Penetration: " << penetrationVec.x << "x" << penetrationVec.y;
        LOG(INFO) << "RectA: " << a.x << "x" << a.y << "x" << a.w << "x" << a.h;
        LOG(INFO) << "RectB: " << b.x << "x" << b.y << "x" << b.w << "x" << b.h;

        return penetrationVec;
    }
}
