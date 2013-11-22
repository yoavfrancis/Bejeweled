#include <SDL.h>
#include "TileView.h"
#include "GameException.h"
#include "SurfaceProxy.h"

namespace game {

TileView::TileView(int x, int y, SDL_Surface* tileImg) 
: m_x(x), m_y(y), m_tileImg(tileImg), m_isEmpty(false) {
    if(!tileImg) {
        throw GameException("Uninitialized tile image surface given");
    }
}

TileView::TileView() :  m_x(0), m_y(0), m_isEmpty(true), m_tileImg(NULL) {
}

TileView::~TileView() {
    ///Resource manager destroys SDL objects
}

TileView::TileView(const TileView& other) {
    this->operator=(other);
}

TileView& TileView::operator=(const TileView& other) {
    if(this != &other) {
        m_x = other.m_x;
        m_y = other.m_y;
        m_tileImg = other.m_tileImg;
        m_isEmpty = other.m_isEmpty;
    }
    return *this;
}

void TileView::draw(SDL_Surface* dst) const {
    if(!m_isEmpty) {
        SurfaceProxy::draw(m_x, m_y, m_tileImg, dst);
    }
}

int TileView::getOriginX() const {
    return m_x;
}

int TileView::getOriginY() const{
    return m_y;
}
int TileView::getWidth() const {
    return m_tileImg->w;
}
int TileView::getHeight() const {
    return m_tileImg->h;
}

} // namespace game
