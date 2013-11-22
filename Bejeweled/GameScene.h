#ifndef __GameTest_GameScene_h__
#define __GameTest_GameScene_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <SDL.h>
#include <string>
#include "ResourceManager.h"
#include "GameButton.h"
#include "GameBoard.h"
#include "GameObject.h"

namespace game {

/**
 * Represents the game scene itself.
 */
class GameScene : public GameObject
{
public:
    /// The path to the background image
    static const std::string BACKGROUND_IMG;

    /// Constructor
    GameScene(int x, int y, SDL_Surface* target = NULL);

    /**
     * destructor - while it is still virtual (due to being defined as such in GameObject), 
     * not writing so signifies that the class should not be inherited. 
     * (Since the class frees the inherited destination surface - that is, the screen itself)
     */
    ~GameScene();

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

    ResourceManager m_resManager;

    /// Represents the game screens
    SDL_Surface* message;
    SDL_Surface* m_backgroundImage;

    /// Objects on the game screen
    GameBoard* m_gameBoard;
    GameButton* m_button;
}; // class GameScene

} // namespace game

#endif // __GameTest_GameScene_h__
