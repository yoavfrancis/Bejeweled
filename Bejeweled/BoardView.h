#ifndef __GameTest_BoardView_h__
#define __GameTest_BoardView_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <SDL.h>
#include <map>
#include "GameObject.h"
#include "Drawable.h"
#include "TileView.h"
#include "TileViewFactory.h"
#include "BoardModel.h"

namespace game {

/**
 * Represents the game board view as a drawable object.
 * Polls the board model and draws it.
 */
class BoardView : public Drawable
{
public:
    static const int TILE_NOT_FOUND = -1;

    /**
     * Constructor - receives a reference to the model and to the tile provider.
     * Also receives the tile size (as it is a square tile).
     */
    BoardView(const BoardModel& model, const TileViewFactory& tileProvider,
              int originX, int originY, int tileSize);

    /// Destructor - does nothing
    virtual ~BoardView();

    /// Draws the board on the given surface.
    virtual void draw(SDL_Surface* dst) const;

    /// get object in position
    bool isTileAtCoordinate(int x, int y) const;

    /// remove tile.
    void removeTileAtIndex(int row, int col);

    /// Should only be called after setting the tile width/height
    int getTileRowByY(int y) const;
    int getTileColumnByX(int x) const;

    /// Tile selection methods
    void setTileSelected(int row, int col);
    void setTileDeselected(int row, int col);
    bool isTileSelected(int row, int col) const;
    void deselectAllTiles();

private:
    /// Prevent Copying and Assignment
    BoardView(const BoardView&);
    BoardView& operator=(const BoardView&);

    const BoardModel& m_boardModel;
    const TileViewFactory& m_tileProvider;

    /// BoardView dimensions
    int m_numCols, m_numRows;

    /// Origin axis of the board
    int m_originX, m_originY;

    std::map<Point, bool> m_selectedTiles;

    int m_tileHeight, m_tileWidth;
}; // class BoardView

} // namespace game

#endif // __GameTest_BoardView_h__
