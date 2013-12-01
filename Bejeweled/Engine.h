#ifndef __Bejeweled_Engine_h__
#define __Bejeweled_Engine_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <SDL.h>
#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Timer.h"

namespace bejeweled {

using std::string;

/**
 * The game engine - loads and unloads SDL and is sole responsible for the screen surface.
 * Orchestrates the game displaying the Game Scene (objects that derive from GameObject) on the screen.
 * These object, in turn, can also contain additional game objects.
 */
class Engine {
public:
    static const int GAME_FPS;
    static const string WINDOW_TITLE;
    static const string ICON_IMG;

    /// Ctor - initializes SDL, sets title and icon (if using Windows), and the game screen surface
    Engine();

    /// Dtor - Unloads SDL and frees the game screen
    ~Engine();

    /// Main run function - runs the game loop itself
     void run();

private:
    /// Disallow assignment and copy ctor
    Engine(const Engine&);
    Engine& operator=(const Engine&);

    ResourceManager m_resManager;

    SDL_Surface* m_gameIcon;
    SDL_Surface* m_screen;
    Timer m_fpsTimer;

    /// The current object/state to be displayed on the screen. (introduction screen/game screen/main menu)
    /// This object can further orchestrate his own objects on the screen.
    GameObject* m_curScene;
};

}

#endif //__Bejeweled_Engine_h__
