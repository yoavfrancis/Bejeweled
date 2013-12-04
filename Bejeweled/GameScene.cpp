#include <SDL.h>
#include <SDL_image.h>
#include "GameScene.h"
#include "SurfaceProxy.h"
#include "GameException.h"

namespace bejeweled {

const std::string GameScene::BACKGROUND_IMG = "resources\\Background.png";
const std::string GameScene::BACKGROUND_MUSIC = "resources\\music.ogg";

GameScene::GameScene(int x, int y, SDL_Surface* target)
: GameObject(x, y, target),
  m_isGameover(false),
  m_resManager(),
  m_backgroundImage(m_resManager.loadImage(BACKGROUND_IMG)),
  m_music(m_resManager.loadMusic(BACKGROUND_MUSIC)),
  m_gameBoard(GameBoard::BOARD_OFFSET_X,
              GameBoard::BOARD_OFFSET_Y,
              m_dstSurface,
              SurfaceProxy::getImageDimensions(GameBoard::TILE_BLUE_IMG).first),
  m_button(GameButton::BUTTON_OFFSET_X, GameButton::BUTTON_OFFSET_Y, m_dstSurface)
{ }

GameScene::~GameScene() {
}


bool GameScene::isGameover() const {
    return m_isGameover;
}

void GameScene::update() {
    GameButton::ButtonStatus buttonStatus = m_button.getButtonStatus();
    if(buttonStatus == GameButton::TIMER) {
        /// When game starts after pressing the button, inform the board that it is ready for play.
        GameBoard::BoardState curBoardState = m_gameBoard.getBoardState();
        if(curBoardState == GameBoard::FREEZE) {
            m_gameBoard.notifyPlayable();
            Mix_PlayMusic(m_music, -1); // Play the music
        } else if(curBoardState == GameBoard::NO_MOVES) {
            m_button.notifyNoMoves();
        }
        m_button.update();
        m_gameBoard.update();
    } else if(buttonStatus == GameButton::GAMEOVER || buttonStatus == GameButton::NOMOVES) {
        m_isGameover = true;
        //Mix_HaltMusic(); - To stop the music from playing upon "game over".
    }
}

void GameScene::draw() {
    SurfaceProxy::draw(0, 0, m_backgroundImage, m_dstSurface);
    m_gameBoard.draw();
    m_button.draw();
}

void GameScene::handleEvent(SDL_Event* event) {
    if(event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT) {
        int x = event->button.x;
        int y = event->button.y;
        if(m_button.isPointInObject(x,y)) {
            m_button.handleEvent(event);
        } else if(m_gameBoard.isPointInObject(x, y)) {
            m_gameBoard.handleEvent(event);
        } 
    }
}

bool GameScene::isPointInObject(int x, int y) const {
    return (x>=0 && y>=0);
}

} // namespace bejeweled