#include <Client/StateBomberman.hpp>
#include <easylogging++.h>

namespace Client
{

    StateBomberman::StateBomberman()
    {

    }
    StateBomberman::~StateBomberman()
    {
		LOG(INFO) << "StateBomberman deleted.";
    }

    void StateBomberman::init()
    {
        LOG(INFO) << "Initializing StateBomberman.";

        LOG(INFO) << "StateBomberman initialized.";
    }

    void StateBomberman::render(std::shared_ptr<Window> window)
    {

    }
}
