#pragma once

#include <vector>
#include <memory>
#include <pihud/Widget.hpp>

namespace PiH
{
    /**
     * @brief The Particle class represents a single particle.
     *
     * These particles are not intended for heavy usage, as they should contain
     * graphics and only be on the GUI level.
     *
     * Particles can have trailing particles too. They mostly are derived from the parent particle
     * and have the same texture, but are a little bit different in behavior.
     */
    class Particle
    {
        public:
            Particle();
            ~Particle();

            float velX = 5;
            float velY = 5;

            float drag = 5;

            float rotation = 0;
            float rotationSpeed = 10;

            IntRect textureRect;

            void onUpdate(float frametime);
            void onRender(SDL_Renderer *renderer);
        private:
            std::vector<std::unique_ptr<Particle> > m_trailingParticles;
    };
}
