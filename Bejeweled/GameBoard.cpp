#include <utility>
#include <SDL_mixer.h>
#include "GameException.h"
#include "GameBoard.h"

namespace bejeweled {

const int GameBoard::NUM_ROWS = 8;
const int GameBoard::NUM_COLS = 8;
const int GameBoard::BOARD_OFFSET_X = 241;
const int GameBoard::BOARD_OFFSET_Y = 36;
const string GameBoard::TILE_BLUE_IMG = "resources\\Blue.png";
const string GameBoard::TILE_GREEN_IMG = "resources\\Green.png";
const string GameBoard::TILE_PURPLE_IMG = "resources\\Purple.png";
const string GameBoard::TILE_RED_IMG = "resources\\Red.png";
const string GameBoard::TILE_YELLOW_IMG = "resources\\Yellow.png";
const string GameBoard::EFFECT_SELECTION = "resources\\select.ogg";
const string GameBoard::EFFECT_MATCH = "resources\\match.ogg";
const int GameBoard::NUM_COLORS = 5;

GameBoard::GameBoard(int tileSize) 
: GameObject(),
  m_boardState(UNINITIALIZED), 
  m_boardModel(NUM_ROWS, NUM_COLS, NUM_COLORS),
  m_boardView(m_boardModel, m_tileDrawer, BOARD_OFFSET_X, BOARD_OFFSET_Y, tileSize),
  m_selectedTile(-1, -1),
  m_prevSelectedTile(-1, -1),
  m_effectSelection(m_resManager.loadEffect(EFFECT_SELECTION)),
  m_effectMatch(m_resManager.loadEffect(EFFECT_MATCH))
{
    m_tileDrawer.addAvailableTileImage(m_resManager.loadImage(TILE_BLUE_IMG));
    m_tileDrawer.addAvailableTileImage(m_resManager.loadImage(TILE_GREEN_IMG));
    m_tileDrawer.addAvailableTileImage(m_resManager.loadImage(TILE_PURPLE_IMG));
    m_tileDrawer.addAvailableTileImage(m_resManager.loadImage(TILE_RED_IMG));
    m_tileDrawer.addAvailableTileImage(m_resManager.loadImage(TILE_YELLOW_IMG));
    
    m_boardModel.fillBoard(); // /// Initialize the model with random tiles
    m_boardState = FREEZE;
}

GameBoard::GameBoard(int x, int y, SDL_Surface* target, int tileSize) 
: GameObject(x, y, target),
  m_boardState(UNINITIALIZED),
  m_boardModel(NUM_ROWS, NUM_COLS, NUM_COLORS),
  m_boardView(m_boardModel, m_tileDrawer, BOARD_OFFSET_X, BOARD_OFFSET_Y, tileSize),
  m_selectedTile(-1, -1),
  m_prevSelectedTile(-1, -1),
  m_effectSelection(m_resManager.loadEffect(EFFECT_SELECTION)),
  m_effectMatch(m_resManager.loadEffect(EFFECT_MATCH))
{
    m_tileDrawer.addAvailableTileImage(m_resManager.loadImage(TILE_BLUE_IMG));
    m_tileDrawer.addAvailableTileImage(m_resManager.loadImage(TILE_GREEN_IMG));
    m_tileDrawer.addAvailableTileImage(m_resManager.loadImage(TILE_PURPLE_IMG));
    m_tileDrawer.addAvailableTileImage(m_resManager.loadImage(TILE_RED_IMG));
    m_tileDrawer.addAvailableTileImage(m_resManager.loadImage(TILE_YELLOW_IMG));

    m_boardModel.fillBoard(); // Initialize the model with random tiles
    m_boardState = FREEZE;
}

GameBoard::~GameBoard()
{ }

void GameBoard::handleEvent(SDL_Event* event) {
    // No need to make sure that this is a left-click event,  as the GameScene checks that.
    int x = event->button.x;
    int y = event->button.y;
    // Receive input only when board is ready or when one tile is selected.
    if(m_boardState == READY || m_boardState ==  WAIT_SELECT2) {
        // Board is ready to be clicked, and there are less than 2 selected tiles.
        if(m_boardView.isTileAtCoordinate(x, y)) {
            Mix_PlayChannel(-1, m_effectSelection, 0);
            int row = m_boardView.getTileRowByY(y);
            int col = m_boardView.getTileColumnByX(x);
            if(m_boardState == WAIT_SELECT2) {
                m_prevSelectedTile = m_selectedTile;
                m_boardState = SELECT2;
            } else {
                m_boardState = SELECT1;
            }
            m_selectedTile = std::make_pair(row, col);
        }
    }
}

void GameBoard::update() {
    /**
     * This is the board update logic. It is done in "Steps" to give the feeling of "animation" - that is, for every
     * call to update(), the board "stabilizes" itself in one step (drop one row of tiles, etc)
     * The following "switch/case" behavior can be seen as some sort of an finite state automata.
     */
    switch(m_boardState) {
    case CHECK_NO_MOVES:
        if(m_boardModel.hasMoreMoves()) {
            m_boardState = READY;
        } else {
            m_boardState = NO_MOVES;
        }
        break;
    case SELECT1:
        m_boardView.setTileSelected(m_selectedTile.first, m_selectedTile.second);
        m_boardState = WAIT_SELECT2;
        break;
    case WAIT_SELECT2:
        break;
    case SELECT2:
        m_boardView.deselectAllTiles();
        if(!m_boardModel.swapTiles(m_prevSelectedTile.first, m_prevSelectedTile.second,
            m_selectedTile.first, m_selectedTile.second))
        {
            // Unable to swap
            m_boardState = READY;
        } else {
            // Check if sequences were found after selection.
            if(!m_boardModel.hasSequencesProximity(m_selectedTile.first, m_selectedTile.second) &&
               !m_boardModel.hasSequencesProximity(m_prevSelectedTile.first, m_prevSelectedTile.second))
            {      
                // No sequence found - switch model back to original state
                m_boardModel.swapTiles(m_prevSelectedTile.first, m_prevSelectedTile.second,
                    m_selectedTile.first, m_selectedTile.second);
                m_boardState = READY;
            } else {
                // Found some sequence(s) - gravitate the board
                Mix_PlayChannel(-1, m_effectMatch, 0);
                m_boardModel.markAllSequencesOnBoard();
                m_boardState = GRAVITATE;
            }
        }
        break;
    case MARK_EMPTY_SEQ:
        if(!m_boardModel.markAllSequencesOnBoard()) {
            // No sequences were found - check if moves are possible and if so, set board to ready.
            m_boardState = CHECK_NO_MOVES;
        } else {
            Mix_PlayChannel(-1, m_effectMatch, 0);
            m_boardState = GRAVITATE;
        }
        break;
    case GRAVITATE:
        if(!m_boardModel.gravitateBoardStep()) {
            m_boardState = DROP_TILES;
        }
        break;
    case DROP_TILES:
        if(!m_boardModel.dropNewTilesRow()) {
            m_boardState = MARK_EMPTY_SEQ;
        } else {
            m_boardState = GRAVITATE;
        }
        break;
    default:
        break;
    };
}
void GameBoard::draw() {
    if(m_boardState != FREEZE && m_boardState != UNINITIALIZED) {
        m_boardView.draw(m_dstSurface);
    }
}

bool GameBoard::isPointInObject(int x, int y) const {
    return m_boardView.isTileAtCoordinate(x, y);
}

void GameBoard::notifyPlayable() {
    m_boardState = CHECK_NO_MOVES;
}

GameBoard::BoardState GameBoard::getBoardState() const {
    return m_boardState;
}

} // namespace bejeweled