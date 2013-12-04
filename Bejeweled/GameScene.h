#ifndef __Bejeweled_GameScene_h__
#define __Bejeweled_GameScene_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <SDL.h>
#include <string>
#include "ResourceManager.h"
#include "GameButton.h"
#include "GameBoard.h"
#include "GameObject.h"

namespace bejeweled {

/**
 * Represents the game scene itself.
 */
class GameScene : public GameObject
{
public:
    /// The path to the background image and to the music
    static const std::string BACKGROUND_IMG;
    static const std::string BACKGROUND_MUSIC;

    /// Constructor
    GameScene(int x, int y, SDL_Surface* target = NULL);

    /// Destructor
    virtual ~GameScene();

    /// Indicates if the game is over
    bool isGameover() const;

    /// Inherited Game loop functions 
    virtual void update();
    virtual void draw();
    virtual void handleEvent(SDL_Event* event);
    virtual bool isPointInObject(int x, int y) const;
    
private:
    /// Prevent Copying and Assignment
    GameScene(const GameScene&);
    GameScene& operator=(const GameScene&);

    /// Indicates if the game over
    bool m_isGameover;

    /// Resource manager for background image and music
    ResourceManager m_resManager;

    /// Represents the game screens
    SDL_Surface* message;
    SDL_Surface* m_backgroundImage;

    /// Background music
    Mix_Music* m_music;

    /// Objects on the game screen
    GameBoard m_gameBoard;
    GameButton m_button;
}; // class GameScene

} // namespace bejeweled

#endif // __Bejeweled_GameScene_h__
