#ifndef CLIENT_TEXTUREMANAGER_HPP_INCLUDED
#define CLIENT_TEXTUREMANAGER_HPP_INCLUDED

#include <memory>
#include <map>
#include <Client/Window.hpp>
#include <Client/Texture.hpp>

namespace Client
{
    class TextureManager
    {
        public:
            TextureManager(std::shared_ptr<Window> window);
            virtual ~TextureManager();

            void clear();
            void destroy();

            bool has(const std::string &path);

            std::shared_ptr<Texture> get(const std::string &path);
			std::shared_ptr<Texture> operator[](std::string index);
        private:
            std::map<std::string, std::weak_ptr<Texture>> m_textures;

            std::shared_ptr<Window> m_window;
    };

}

#endif
