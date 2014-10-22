#include <Client/Config.hpp>

namespace Client
{
    Config::Config()
    {

    }
    Config::~Config()
    {

    }
    void Config::loadFromFile(const std::string &file)
    {

    }
    int Config::getIntValue(Config::Value id)
    {
        return m_ints[id];
    }
    float Config::getFloatValue(Config::Value id)
    {
        return m_floats[id];
    }
    const std::string &Config::getStringValue(Config::Value id)
    {
        return m_strings[id];
    }
    bool Config::getBooleanValue(Config::Value id)
    {
        return m_bools[id];
    }
    void Config::setIntValue(Config::Value id, int value)
    {
        m_ints[id] = value;
    }
    void Config::setFloatValue(Config::Value id, float value)
    {
        m_floats[id] = value;
    }
    void Config::setStringValue(Config::Value id, const std::string &value)
    {
        m_strings[id] = value;
    }
    void Config::setBooleanValue(bool value, Config::Value id)
    {
        m_bools[id] = value;
    }
}
