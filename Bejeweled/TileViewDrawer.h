#ifndef __Bejeweled_TileViewDrawer_h__
#define __Bejeweled_TileViewDrawer_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <Vector>
#include <SDL.h>
#include "TileView.h"
#include "SelectedTileView.h"

namespace bejeweled {

/**
 * Manages existing tile views and images.
 * Draws the tile on top of the board view.
 */
class TileViewDrawer
{
public:
    TileViewDrawer();

    /// Adds a new SDL_Surface to the available tile images collection
    void addAvailableTileImage(SDL_Surface* img);
    
    /// Draws the tile by the given id on top onto the given SDL_Surface
    void drawTile(SDL_Surface* dst, int x, int y, int id, int isSelected = false) const;

    /// This of course works assuming that all tiles are of same dimensions.
    int getTileWidth() const;
    int getTileHeight() const;

private:
    /// Since we are dealing with limited small amount of possible tile colors, we'll just hold them in containers
    /// instead of generating them upon every draw call.
    std::vector<SelectedTileView> m_selectedTileViews;
    std::vector<TileView> m_tileViews;
    TileView m_emptyTile;

}; // class TileViewDrawer

} // namespace bejeweled

#endif // __Bejeweled_TileViewDrawer_h__
