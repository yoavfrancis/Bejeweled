#ifndef __GameTest_GameButton_h__
#define __GameTest_GameButton_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Timer.h"

namespace game {

using std::string;

/**
 * A button game object that is clickable and displays text.
 * Represents the start button of our game, and the timer is also displayed on it.
 */
class GameButton : public GameObject
{
public:

    /// Default values constants
    static const int FONT_SIZE;
    static const string FONT_PATH;
    static const int TEXT_OFFSET_X;
    static const int TEXT_OFFSET_Y;
    static const string TIMER_BUTTON_TEXT;
    static const int BUTTON_OFFSET_X;
    static const int BUTTON_OFFSET_Y;
    static const int BUTTON_SIZE_X;
    static const int BUTTON_SIZE_Y;
    static const SDL_Color TIMER_TEXT_COLOR;
    static const SDL_Color BUTTON_BACKCOLOR;
    static const float GAME_TIME_SECS;
    
    /// Indicates the current game status 
    enum ButtonStatus {READY, TIMER, GAMEOVER, NOMOVES};

    GameButton(int x = BUTTON_OFFSET_X,
           int y = BUTTON_OFFSET_Y,
           SDL_Surface* target = NULL,
           int w = BUTTON_SIZE_X,
           int h = BUTTON_SIZE_Y,
           const string& text = TIMER_BUTTON_TEXT,
           SDL_Color textColor = TIMER_TEXT_COLOR,
           SDL_Color buttonBackgroundColor = BUTTON_BACKCOLOR);

    /**
     * Destructor - frees the contained button and text surfaces.
     * Resources acquired by the resource manager would be freed upon its destruction automatically 
     */
    virtual ~GameButton();

    /// Changes the button text
    void setText(const string& text);

    virtual void handleEvent(SDL_Event* event);
    virtual void update();
    virtual void draw();
    virtual bool isPointInObject(int x, int y) const;
    ButtonStatus getButtonStatus() const;

    /// Notifies the button that no moves are available, and displays a message
    void notifyNoMoves();

private:
    // Prevent Copying and Assignment
    GameButton(const GameButton&);
    GameButton& operator=(const GameButton&);

    ResourceManager m_resManager;

    SDL_Surface* m_buttonSurface;
    SDL_Surface* m_fontSurface;
    TTF_Font* m_font;
    string m_text;
    SDL_Color m_textColor;
    SDL_Color m_buttonColor;

    Timer m_gameTimer;
    int m_height, m_width;
    int m_textOffsetX;
    ButtonStatus m_buttonStatus;

}; // class GameButton

} // namespace game

#endif // __GameTest_GameButton_h__