#ifndef GAMEEVENTHANDLER_HPP_INCLUDED
#define GAMEEVENTHANDLER_HPP_INCLUDED

#include <map>
#include <sigc++/sigc++.h>

/**
 * @brief The GameEventHandler class sends events based on the current state of the game.
 *
 * The event types are fired when they are true (every frame). The exceptions are listed below.
 */
class GameEventHandler
{
    public:
        enum Type {
            DIR_UP,
            DIR_DOWN,
            DIR_LEFT,
            DIR_RIGHT,

            /**
              * @brief Fired only once! (= 1 Frame)
              *
              * This happens when the action button was pressed.
              */
            ACTION,

            _COUNT
        };
        typedef sigc::signal<void, Type, float> GameEventSignal;

        void sendEvent(Type eventType, float frametime);
		GameEventSignal getSignal(const Type &type);
    protected:
        virtual void onGameEvent(Type eventType, float frameTime);
    private:
        std::map<Type, GameEventSignal> m_signals;
};

#endif
