#ifndef CLIENT_POWERUPCOLLISIONRESOLVER_HPP_INCLUDED
#define CLIENT_POWERUPCOLLISIONRESOLVER_HPP_INCLUDED

#include <Client/Collision.hpp>
#include <memory>

namespace Client
{
    namespace Resolver
    {
        void OnPowerupCollison(std::shared_ptr<Collision> collision);
    }
}

#endif
