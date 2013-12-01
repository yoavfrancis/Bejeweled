#include <SDL.h>
#include <sstream>
#include "GameButton.h"
#include "GameException.h"
#include "SurfaceProxy.h"

namespace game {

// Initialize default values constants
const int GameButton::FONT_SIZE = 28;
const string GameButton::FONT_PATH = "resources\\arial.ttf";
const int GameButton::TEXT_OFFSET_INITIAL = 55;
const int GameButton::TEXT_OFFSET_TIMER = 75;
const int GameButton::TEXT_OFFSET_GAMEOVER = 10;
const int GameButton::TEXT_OFFSET_NOMOVES = 3;
const int GameButton::TEXT_OFFSET_Y = 10;
const std::string GameButton::TIMER_BUTTON_TEXT = "Start";
const int GameButton::BUTTON_OFFSET_X = 25;
const int GameButton::BUTTON_OFFSET_Y = 260;
const int GameButton::BUTTON_SIZE_X = 170;
const int GameButton::BUTTON_SIZE_Y = 60;
const SDL_Color GameButton::TIMER_TEXT_COLOR = {255, 255, 255};
const SDL_Color GameButton::BUTTON_BACKCOLOR = {0, 100, 100};
const float GameButton::GAME_TIME_SECS = 60.0f;

GameButton::~GameButton() {
    SDL_FreeSurface(m_fontSurface);
    SDL_FreeSurface(m_buttonSurface);
    // Fonts are closed by the resource manager
}

GameButton::GameButton(int x, int y,  SDL_Surface* target, int w, int h, const string& text,
               SDL_Color textColor, SDL_Color buttonBackgroundColor) 
    : GameObject(x, y, target),
    m_height(h),
    m_width(w),
    m_text(text),
    m_buttonSurface(SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0, 0, 0, 0)),
    m_font(m_resManager.loadFont(FONT_PATH, FONT_SIZE)),
    m_textColor(textColor),
    m_buttonColor(buttonBackgroundColor),
    m_fontSurface(NULL),
    m_buttonStatus(READY),
    m_textOffsetX(TEXT_OFFSET_INITIAL)
{  
    if(!m_buttonSurface) {
        throw GameException();
    }
    setText(m_text);
}

void GameButton::handleEvent(SDL_Event* event) {
    // No need to make sure that this is a left-click event,  as the GameScene checks that.
    if(!m_gameTimer.isStarted()) {
        m_gameTimer.start();
        m_buttonStatus = TIMER;
        m_textOffsetX = TEXT_OFFSET_TIMER;;
    }
}

void GameButton::update() {
    // Update the timer button text
    if(m_buttonStatus == TIMER) {
        std::ostringstream  time;
        int timeRemaining = static_cast<int>(GAME_TIME_SECS - m_gameTimer.getTicks()/1000.0);
        time << timeRemaining;
        setText(time.str());
        if(timeRemaining == 0) {
            m_gameTimer.stop();
            m_buttonStatus = GAMEOVER;
            setText("Game Over");
            m_textOffsetX = TEXT_OFFSET_GAMEOVER;
        }
    }
}

void GameButton::draw() {
    SDL_Rect rect;
    rect.h = m_height;
    rect.w = m_width;
    rect.x = 0;
    rect.y = 0;

    // Fill a rectangle for the button
    if(SDL_FillRect(m_buttonSurface, 
                    &rect, 
                    SDL_MapRGB(m_dstSurface->format, m_buttonColor.r, m_buttonColor.g, m_buttonColor.b))) 
    {
        throw GameException();
    }


    // Draw the button and then the text
    SurfaceProxy::draw(m_originX, m_originY, m_buttonSurface, m_dstSurface);
    SurfaceProxy::draw(m_originX + m_textOffsetX, m_originY + TEXT_OFFSET_Y, m_fontSurface, m_dstSurface);
}

bool GameButton::isPointInObject(int x, int y) const {
    return (x > m_originX && x < m_originX + m_width &&
            y > m_originY && y < m_originY + m_height);
}

void GameButton::setText(const string& text) {
    m_text = text;
    SDL_FreeSurface(m_fontSurface);
    m_fontSurface = TTF_RenderText_Blended(m_font, m_text.c_str(), m_textColor);
    if(!m_fontSurface) {
        throw GameException();
    }
}

GameButton::ButtonStatus GameButton::getButtonStatus() const {
    return m_buttonStatus;
}

void GameButton::notifyNoMoves() {
    m_gameTimer.stop();
    m_buttonStatus = NOMOVES;
    setText("No Moves!");
    m_textOffsetX = TEXT_OFFSET_NOMOVES;
}

} //namespace game
