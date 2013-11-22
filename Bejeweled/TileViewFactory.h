#ifndef __GameTest_TileViewFactory_h__
#define __GameTest_TileViewFactory_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <Vector>
#include <SDL.h>
#include "TileView.h"

namespace game {

/**
 * Represents a tile on the game board
 */
class TileViewFactory
{
public:
	TileViewFactory();

    /// @adds a new SDL_Surface to the available tile images collection
    void addAvailableTileImage(SDL_Surface* img);

    /// @return a random TileView
    TileView provideRandomTile(int x, int y) const;

     // @return a TileView with a surface matching for the id given.
    TileView* provideTileById(int x, int y, int id, int isSelected=false) const;

    /// This of course works assuming that all tiles are of same size.
    int getTileWidth() const;
    int getTileHeight() const;

private:
    std::vector<SDL_Surface*> m_tileImages;
}; // class TileViewFactory

} // namespace game

#endif // __GameTest_TileViewFactory_h__
