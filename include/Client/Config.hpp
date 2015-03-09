#ifndef CLIENT_CONFIG_HPP_INCLUDED
#define CLIENT_CONFIG_HPP_INCLUDED

#include <string>
#include <map>

namespace Client
{
	class Config
    {
        public:
            enum Value
            {
                WINDOW_SIZE_X,
                WINDOW_SIZE_Y,
                FULLSCREEN,
                POWERUP_DROP_CHANCE,
                BOMB_PLACE_COOLDOWN,
                STANDARD_FONT,

                _COUNT
            };

            Config();
            virtual ~Config();

            void loadFromFile(const std::string &file);
            void setDefaultValues();

            int getIntValue(Value id);
            float getFloatValue(Value id);
            const std::string& getStringValue(Value id);
            bool getBooleanValue(Value id);

            void setIntValue(Value id, int value);
            void setFloatValue(Value id, float value);
            void setStringValue(Value id, const std::string &value);
            void setBooleanValue(Value id, bool value);
        private:
            std::map<Value, int> m_ints;
            std::map<Value, float> m_floats;
            std::map<Value, std::string> m_strings;
            std::map<Value, bool> m_bools;
    };
}

#endif
