#pragma once

#include <pihud/Config.hpp>

namespace PiH
{
    Config *GlobalConfig = nullptr;

    void initialize(Config *config)
    {
		if(GlobalConfig == nullptr)
        {
            GlobalConfig = config;
        }
    }
    void exit()
    {
        if(GlobalConfig != nullptr)
        {
            delete GlobalConfig;
        }
    }
}
