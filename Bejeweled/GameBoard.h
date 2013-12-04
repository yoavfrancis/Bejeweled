#ifndef __Bejeweled_GameBoard_h__
#define __Bejeweled_GameBoard_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include "GameObject.h"
#include "Point.h"
#include "BoardView.h"
#include "BoardModel.h"
#include "TileViewDrawer.h"
#include "ResourceManager.h"

namespace bejeweled {

using std::string;

/**
 * Represents the game board object as a GameObject
 */
class GameBoard : public GameObject {
public:
    /// Constants for the game board
    static const int NUM_ROWS;
    static const int NUM_COLS;
    static const int BOARD_OFFSET_X;
    static const int BOARD_OFFSET_Y;
    static const string TILE_BLUE_IMG;
    static const string TILE_GREEN_IMG;
    static const string TILE_PURPLE_IMG;
    static const string TILE_RED_IMG;
    static const string TILE_YELLOW_IMG;
    static const string EFFECT_SELECTION;
    static const string EFFECT_MATCH;
    static const int NUM_COLORS;

    enum BoardState {UNINITIALIZED, FREEZE, READY, SELECT1, WAIT_SELECT2, SELECT2,
        MARK_EMPTY_SEQ, GRAVITATE, DROP_TILES, CHECK_NO_MOVES, NO_MOVES};

    /// Constructor - initializes empty surface at (0,0). Receives a square tile size (in pixels)
    GameBoard(int tileSize = 0);

    /// Constructor - initializes the given surface at the given (x,y) coordinates.
    GameBoard(int x, int y, SDL_Surface* target = NULL, int tileSize = 0);

    /**
     * Destructor - Does nothing.
     * Resources acquired by the resource manager would be freed upon its destruction automatically 
     */
    virtual ~GameBoard();

    /// Game object methods
    virtual void handleEvent(SDL_Event* event);
    virtual void update();
    virtual void draw();
    bool isPointInObject(int x, int y) const;

    /**
     * Sets the board to a ready state, that allows it to receive input.
     * Practically, it sets the board to check_moves state first.
     */
    void notifyPlayable();

    /// returns the current board state.
    BoardState getBoardState() const;

private:
    /// Disallow copying and assignment.
    GameBoard(const GameBoard&);
    GameBoard& operator=(const GameBoard&);

    BoardState m_boardState;
    TileViewDrawer m_tileDrawer;
    BoardModel m_boardModel; /// Model MUST appear before the view in this class. (Initialization order)
    BoardView m_boardView;
    ResourceManager m_resManager;
    Point m_selectedTile, m_prevSelectedTile;
    Mix_Chunk* m_effectSelection;
    Mix_Chunk* m_effectMatch;
}; // class GameBoard

} // namespace bejeweled

#endif // __Bejeweled_GameBoard_h__
