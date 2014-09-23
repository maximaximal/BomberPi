#include <Client/CollisionSystem.hpp>

#include <Client/BodyComponent.hpp>
#include <Client/PositionComponent.hpp>

namespace Client
{
    CollisionSystem::CollisionSystem(BombermanMap *bombermanMap)
    {
        m_map = bombermanMap;
    }
    CollisionSystem::~CollisionSystem()
    {

    }
    void CollisionSystem::update(float frametime)
    {
        //The 2 rectangles have their positions assigned to the
        //coordinate root to simplify collision detection.

        SDL_Rect rectA;
        SDL_Rect rectB;
        for(auto &entityA : getEntities())
        {
            auto &posA = entityA.getComponent<PositionComponent>();
            auto &bodyA = entityA.getComponent<BodyComponent>();

            rectA.x = posA.pos.x + bodyA.x; //LEFT
            rectA.y = posA.pos.y + bodyA.y; //TOP
            rectA.w = bodyA.w + rectA.x;    //RIGHT
            rectA.h = bodyA.h + rectA.y;    //BOTTOM

            for(auto &entityB : getEntities())
            {
                if(entityA.getId() != entityB.getId())
                {
                    //Only check for collision if the IDs are not equal.
                    auto &posB = entityB.getComponent<PositionComponent>();
                    auto &bodyB = entityB.getComponent<BodyComponent>();

                    rectB.x = posB.pos.x + bodyB.x;
                    rectB.y = posB.pos.y + bodyB.y;
                    rectB.w = bodyB.w + rectA.x;
                    rectB.h = bodyB.h + rectA.y;

                    //Check for collisions.
                    if(rectB.x > rectA.w
                            || rectB.w < rectA.x
                            || rectB.y > rectB.h
                            || rectB.h < rectA.y)
                    {
                        //Collision detected!
                        std::shared_ptr<Collision> event = std::make_shared<Collision>(entityA, entityB);
                        bodyA.collisionSignal(event);
                    }
                }
            }
        }
    }
}
