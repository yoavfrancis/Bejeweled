#include <SDL.h>
#include "SelectedTileView.h"
#include "GameException.h"

namespace game {

SDL_Color SelectedTileView::TILE_BORDER_COLOR = {100,255,255};
int SelectedTileView::TILE_BORDER_WIDTH = 3;

SelectedTileView::SelectedTileView(int x, int y, SDL_Surface* tileImg) 
: TileView(x,y,tileImg) { }

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

void SelectedTileView::draw(SDL_Surface* dst) const{
    TileView::draw(dst);

    // Now draw some borders.
    SDL_Rect rectLeft = {getOriginX(), getOriginY(), TILE_BORDER_WIDTH, getHeight()};
    SDL_Rect rectTop = {getOriginX(), getOriginY(), getWidth(), TILE_BORDER_WIDTH};
    SDL_Rect rectBottom = {getOriginX(), getOriginY()+getHeight()-TILE_BORDER_WIDTH, getWidth(), TILE_BORDER_WIDTH};
    SDL_Rect rectRight = {getOriginX() + getWidth() - TILE_BORDER_WIDTH, getOriginY(), TILE_BORDER_WIDTH, getHeight()};
    Uint32 color = SDL_MapRGB(dst->format, TILE_BORDER_COLOR.r, TILE_BORDER_COLOR.g, TILE_BORDER_COLOR.b);

    if(SDL_FillRect(dst,  &rectLeft, color) || SDL_FillRect(dst, &rectRight, color) ||
       SDL_FillRect(dst, &rectTop, color) || SDL_FillRect(dst, &rectBottom, color)) 
    {
        throw GameException();
    }
}

} // namespace game
