#include <InputMap.hpp>




InputMap::InputMap()
{

}

InputMap::InputMap(const InputMap &inputMap)
{
    for(auto &mapping : inputMap.getMaps())
    {
        m_maps[mapping.first] = mapping.second;
    }
}

InputMap::~InputMap()
{

}

void InputMap::clear()
{
    m_maps.clear();
}

void InputMap::set(const SDL_Scancode &key, const PlayerInputEnum &input)
{
    m_maps[key] = input;
}

const PlayerInputEnum &InputMap::get(SDL_Scancode key)
{
    return m_maps[key];
}

const std::map<SDL_Scancode, PlayerInputEnum> &InputMap::getMaps() const
{
    return m_maps;
}
