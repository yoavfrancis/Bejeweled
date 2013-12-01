#include <utility>
#include "BoardView.h"
#include "GameException.h"
#include "GameObject.h"
#include "Point.h"

namespace bejeweled {

BoardView::BoardView(const BoardModel& model, const TileViewDrawer& tileDrawer,
                    int originX, int originY, int tileSize)
: m_boardModel(model), 
  m_tileDrawer(tileDrawer),
  m_originX(originX), m_originY(originY),
  m_tileHeight(tileSize), m_tileWidth(tileSize),
  m_numRows(m_boardModel.getNumRows()), m_numCols(m_boardModel.getNumColumns())
{ }

BoardView::~BoardView() {
}

void BoardView::draw(SDL_Surface* dst, int x, int y) const {
    for(int j=0; j<m_numCols; ++j) {
        for(int i=0; i<m_numRows; ++i) {
            m_tileDrawer.drawTile(dst,
                                  m_originX + j*m_tileWidth,
                                  m_originY + i*m_tileHeight,
                                  m_boardModel.getTileId(i, j),
                                  isTileSelected(i,j));
        }
    }
}

int BoardView::getTileRowByY(int y) const {
    if(m_tileHeight <= 0) {
        return TILE_NOT_FOUND;
    }
    if(y <= m_originY || y >= m_originY + m_numRows*m_tileHeight) {
        return TILE_NOT_FOUND;
    }
    return (y-m_originY) / m_tileHeight;
}

int BoardView::getTileColumnByX(int x) const {
    if(m_tileWidth <= 0) {
        return TILE_NOT_FOUND;
    }
    if(x <= m_originX || x >= m_originX + m_numCols*m_tileWidth) {
        return TILE_NOT_FOUND;
    }
    return (x-m_originX) / m_tileWidth;
}

bool BoardView::isTileAtCoordinate(int x, int y) const {
    int col = getTileColumnByX(x);
    int row = getTileRowByY(y);
    return !(row==TILE_NOT_FOUND || col==TILE_NOT_FOUND);
}

void BoardView::setTileSelected(int row, int col) {
    m_selectedTiles[std::make_pair(row, col)] = true;
}

void BoardView::setTileDeselected(int row, int col) {
    m_selectedTiles.erase(std::make_pair(row, col));    
}

bool BoardView::isTileSelected(int row, int col) const {
    Point location = std::make_pair(row, col);
    if(m_selectedTiles.count(location) == 0) {
        return false;
    } 
    return (m_selectedTiles.find(location) != m_selectedTiles.end());
}

void BoardView::deselectAllTiles() {
    m_selectedTiles.clear();
}

} // namespace bejeweled
