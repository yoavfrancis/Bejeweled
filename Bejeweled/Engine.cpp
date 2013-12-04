#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Engine.h"
#include "GameObject.h"
#include "SurfaceProxy.h"
#include "GameException.h"
#include "GameScene.h"
#include "Point.h"

namespace bejeweled {

const int Engine::GAME_FPS = 10;
const string Engine::WINDOW_TITLE = "Bejeweled";
const string Engine::ICON_IMG = "resources\\icon.ico";

Engine::Engine() : m_gameIcon(NULL), m_screen(NULL), m_curScene(NULL) {
    /// Initialize SDL subsystems.
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) ||  !IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) || TTF_Init()) {
        throw GameException();
    }
    
    // Detect the size of the background image
    // Must manually load icon, before calling to SDL_SetVideoMode. (Only under Windows)
    Point backgroundDimensions = SurfaceProxy::getImageDimensions(GameScene::BACKGROUND_IMG);
    m_gameIcon = m_resManager.loadSimpleImage(ICON_IMG);
    #if defined(_WIN64) || defined(_WIN32)
    SDL_WM_SetIcon(m_gameIcon, NULL);
    SDL_WM_SetCaption(WINDOW_TITLE.c_str(),NULL);
    #endif

    // Software rendering as this is a simple game. Can use hardware+doublebuf instead.
    m_screen = SDL_SetVideoMode(backgroundDimensions.first, backgroundDimensions.second, 32,  SDL_SWSURFACE);
    if(!m_screen) {
        throw GameException();
    }

    // Allow playing ogg audio files.
    if(!Mix_Init(MIX_INIT_OGG)) {
        throw GameException();
    }

    // Initialize SDL_mixer
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        throw GameException();
    }

    m_fpsTimer.start();
}

Engine::~Engine() {
    delete m_curScene;
    SDL_FreeSurface(m_screen);
    Mix_Quit();
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}

void Engine::run() {
    // Set current scene to the game scene (we only have one scene in this game)
    m_curScene = new GameScene(0, 0, m_screen);
    if(!m_curScene) {
        throw GameException();
    }

    SDL_Event event;

    // Note - Since we only have one scene (that is, one game state) - this "game over" check will do. 
    // If we had multiple game states, such as introduction screen, main menu, etc., we could adapt the State pattern.
    while(!static_cast<GameScene*>(m_curScene)->isGameover()) {
        m_fpsTimer.start();
        
        /// Engine handles exit events, and calls the handle method of the current scene.
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
            case SDL_QUIT:
                return;
            case SDL_KEYDOWN: 
                if(event.key.keysym.sym == SDLK_F4 && 
                  (event.key.keysym.mod == KMOD_LALT || event.key.keysym.mod == KMOD_RALT)) 
                {
                    return;
                }
            default:
                break;
            }
            m_curScene->handleEvent(&event);
        }

        m_curScene->update();
        m_curScene->draw();

        if(SDL_Flip(m_screen)) {
            throw GameException();
        }

        // Regulate FPS
        if(m_fpsTimer.getTicks() < 1000.0 / GAME_FPS) {
            SDL_Delay((1000.0 / GAME_FPS) - m_fpsTimer.getTicks());
        }
    }
    
    // Game exit - wait for 2 seconds and then exit.
    SDL_Delay(2000);
}

} // namespace bejeweled