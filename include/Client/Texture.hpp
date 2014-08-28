#ifndef CLIENT_TEXTURE_HPP_INCLUDED
#define CLIENT_TEXTURE_HPP_INCLUDED

#include <string>
#include <memory>
#include <SDL2/SDL.h>
#include <Client/Window.hpp>

namespace Client
{
    /**
     * @brief The Texture class describes a texture in the BomberPi engine.
     *
     * Textures contain the internal SDL_Texture object, which can be accessed through the
     * getSDLTexture() function.
     */
    class Texture
    {
        public:
            Texture(std::shared_ptr<Window> window);
            virtual ~Texture();

            int load(const std::string &path);
            void destroy();

           	const std::string& getPath();

            SDL_Texture* getSDLTexture();
        private:
            SDL_Texture *m_texture = nullptr;
            std::shared_ptr<Window> m_window;
            std::string m_path;
    };
}

#endif
