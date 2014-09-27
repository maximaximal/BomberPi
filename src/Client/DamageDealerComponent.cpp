#include <Client/DamageDealerComponent.hpp>

namespace Client
{
    DamageDealerComponent::DamageDealerComponent()
    {
		this->damagePerSecond = 0;
    }
    DamageDealerComponent::DamageDealerComponent(int damagePerSecond)
    {
    	this->damagePerSecond = damagePerSecond;
    }
    DamageDealerComponent::~DamageDealerComponent()
    {

    }
}
