#include <SDL.h>
#include "SelectedTileView.h"
#include "GameException.h"

namespace bejeweled {

SDL_Color SelectedTileView::TILE_BORDER_COLOR = {100,255,255};
int SelectedTileView::TILE_BORDER_WIDTH = 3;

SelectedTileView::SelectedTileView(SDL_Surface* tileImg) 
: TileView(tileImg) { }

SelectedTileView::SelectedTileView() :  TileView() {
}

SelectedTileView::~SelectedTileView() {
    ///Resource manager destroys SDL objects
}

SelectedTileView::SelectedTileView(const SelectedTileView& other) {
    this->operator=(other);
}

SelectedTileView& SelectedTileView::operator=(const SelectedTileView& other) {
    TileView::operator=(other);
    return *this;
}

void SelectedTileView::draw(SDL_Surface* dst, int x, int y) const{
    TileView::draw(dst, x, y);

    // Now draw some borders.
    SDL_Rect rectLeft = {x, y, TILE_BORDER_WIDTH, getHeight()};
    SDL_Rect rectTop = {x, y, getWidth(), TILE_BORDER_WIDTH};
    SDL_Rect rectBottom = {x, y+getHeight()-TILE_BORDER_WIDTH, getWidth(), TILE_BORDER_WIDTH};
    SDL_Rect rectRight = {x + getWidth() - TILE_BORDER_WIDTH, y, TILE_BORDER_WIDTH, getHeight()};
    Uint32 color = SDL_MapRGB(dst->format, TILE_BORDER_COLOR.r, TILE_BORDER_COLOR.g, TILE_BORDER_COLOR.b);

    if(SDL_FillRect(dst,  &rectLeft, color) || SDL_FillRect(dst, &rectRight, color) ||
       SDL_FillRect(dst, &rectTop, color) || SDL_FillRect(dst, &rectBottom, color)) 
    {
        throw GameException();
    }
}

} // namespace bejeweled
