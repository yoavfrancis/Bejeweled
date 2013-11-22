#ifndef __GameTest_TileView_h__
#define __GameTest_TileView_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <SDL.h>
#include "Drawable.h"

namespace game {

/**
 * Represents a drawable tile on the game board
 */
class TileView : public Drawable
{
public:
	/**
     * Constructor
     * @param x Horizontal origin point
     * @param y Vertical origin point
     * @param tileImg is the source surface of the tile. It is NOT to be freed by this class.
     */ 
	TileView(int x, int y, SDL_Surface* tileImg);

    /// Empty ctor for empty tile
    TileView();

    /// Copy ctor - does not duplicate surface.
    TileView(const TileView&);

    /// Assignment operator - does not duplicate surface
    TileView& operator=(const TileView&);

	/// Destructor
	virtual ~TileView();

    /// Draws the tile on the given positions
    virtual void draw(SDL_Surface* dst) const;

    /// Getters
    int getOriginX() const;
    int getOriginY() const;
    int getWidth() const;
    int getHeight() const;

private:
    /// Origin location for this tile (Upper left corner)
    int m_x, m_y;

    /// Tile image surface.
    SDL_Surface* m_tileImg;

    /// is this an empty tile
    bool m_isEmpty;
}; // class TileView

} // namespace game

#endif // __GameTest_TileView_h__
