#ifndef INPUTMAP_HPP_INCLUDED
#define INPUTMAP_HPP_INCLUDED

#include <map>
#include <SDL2/SDL.h>
#include <PlayerInput.hpp>

/**
 * @brief The InputMap class maps SDL_Scancodes to the Player Inputs (PlayerInputEnum).
 */
class InputMap
{
    public:
        InputMap();
        InputMap(const InputMap &inputMap);
        virtual ~InputMap();

        void clear();

        void set(const SDL_Scancode &key, const PlayerInputEnum &input);
        const PlayerInputEnum& get(SDL_Scancode key);

       	const std::map<SDL_Scancode, PlayerInputEnum>& getMaps() const;
    private:
 		std::map<SDL_Scancode, PlayerInputEnum> m_maps;
};

#endif
