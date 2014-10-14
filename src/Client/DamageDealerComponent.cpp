#include <Client/DamageDealerComponent.hpp>

namespace Client
{
    DamageDealerComponent::DamageDealerComponent()
    {
		this->damage = 0;
    }
    DamageDealerComponent::DamageDealerComponent(int damage)
    {
    	this->damage = damage;
    }
    DamageDealerComponent::~DamageDealerComponent()
    {

    }
}
