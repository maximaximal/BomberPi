#pragma once

#include <string>
#include <map>

namespace PiH
{
    class Config
    {
        public:
            Config();
            virtual ~Config();

            void setupDefaultConfig();

            enum Variable
            {
                ZOOM,

                _COUNT
            };

            float getValueAsFloat(Config::Variable variable);
            int getValueAsInt(Config::Variable variable);
            const std::string &getValueAsString(Config::Variable variable);

            void setValueAsFloat(Config::Variable variable, float value);
            void setValueAsInt(Config::Variable variable, int value);
            void setValueAsString(Config::Variable variable, const std::string &value);
        private:
            std::map<Config::Variable, std::string> m_values;
	};
}
