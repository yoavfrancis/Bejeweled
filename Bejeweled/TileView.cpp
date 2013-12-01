#include <SDL.h>
#include "TileView.h"
#include "GameException.h"
#include "SurfaceProxy.h"

namespace bejeweled {

TileView::TileView(SDL_Surface* tileImg) 
: m_tileImg(tileImg), m_isEmpty(false) {
    if(!tileImg) {
        throw GameException("Uninitialized tile image surface given");
    }
}

TileView::TileView() : m_isEmpty(true), m_tileImg(NULL) {
}

TileView::~TileView() {
    ///Resource manager destroys SDL objects
}

TileView::TileView(const TileView& other) {
    this->operator=(other);
}

TileView& TileView::operator=(const TileView& other) {
    if(this != &other) {
        m_tileImg = other.m_tileImg;
        m_isEmpty = other.m_isEmpty;
    }
    return *this;
}

void TileView::draw(SDL_Surface* dst, int x, int y) const {
    if(!m_isEmpty) {
        SurfaceProxy::draw(x, y, m_tileImg, dst);
    }
}

int TileView::getWidth() const {
    return m_tileImg->w;
}
int TileView::getHeight() const {
    return m_tileImg->h;
}

} // namespace bejeweled
