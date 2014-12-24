#include <Client/Collision.hpp>
#include <Client/PositionComponent.hpp>
#include <Client/BodyComponent.hpp>
#include <easylogging++.h>

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>

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
    Collision::Side Collision::getSide()
    {
        //Check if the side is already cached, else, compute the side.
        if(m_sideCache != NOT_CACHED)
        {
            return m_sideCache;
        }
        SDL_Rect aRect = getARect();
        SDL_Rect bRect = getBRect();

        //Calculation Variables
		glm::dvec2 Q(bRect.x + bRect.w / 2, bRect.y + bRect.h / 2);
		glm::dvec2 M(aRect.x + aRect.w / 2, aRect.y + aRect.h / 2);

        glm::dvec2 n(1, 0);

        //calculate the angles of the vectors to the x-vector n ( 10 | 0 ).
        float a = glm::orientedAngle(n, glm::normalize(Q - M));

        Side side = NOT_CACHED;

        // > -45° && < 45°
		if(a >= -0.7853981634 && a < 0.7853981634)
        {
            side = LEFT;
        }
        // < 45° && > 135°
        if(0.7853981634 <= a && a < 2.3561944902)
        {
            side = TOP;
        }
        // 135° < && 180° < || -180° < a && < -135°
        if((2.3561944902 <= a && a <= 3.1415926536) || (-3.1415926536 <= a && a < -2.3561944902))
        {
            side = RIGHT;
        }
        // -135° < && < -45°
        if(-2.3561944902 <= a && a < -0.7853981634)
        {
            side = BOTTOM;
        }

        m_sideCache = side;
        if(side != NOT_CACHED)
            return side;

        LOG(WARNING) << "The side of the collision could not be computed! Angle: " << a;
        return Side::LEFT;
    }
    glm::dvec2 Collision::getPenetrationVec()
    {
        glm::dvec2 penetrationVec;

        SDL_Rect a, b;
		a = getARect();
        b = getBRect();

		switch(getSide())
        {
            case LEFT:
                penetrationVec.x = (b.x) - (a.x + a.w);
                break;
            case TOP:
                penetrationVec.y = (b.y) - (a.y + a.h);
                break;
            case RIGHT:
                penetrationVec.x = (b.x + b.w) - a.x;
                break;
            case BOTTOM:
                penetrationVec.y = (b.y + b.h) - a.y;
                break;

            default:
                penetrationVec.x = 0;
                penetrationVec.y = 0;
                break;
        }

        return penetrationVec;
    }
    bool Collision::isObstructed(float amount)
    {
        SDL_Rect a = getARect();
        SDL_Rect b = getBRect();

        float obstructed = 0;

		switch(getSide())
        {
            case LEFT:
                obstructed = (b.x) - (a.x + a.w);
                break;
            case TOP:
                obstructed = (b.y) - (a.y + a.h);
                break;
            case RIGHT:
                obstructed = (b.x + b.w) - a.x;
                break;
            case BOTTOM:
                obstructed = (b.y + b.h) - a.y;
                break;

            default:
                obstructed = 0;
                break;
        }
		if(std::abs(obstructed) > amount)
        {
            return true;
        }
        return false;
    }
}
