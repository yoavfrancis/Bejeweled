#include "TileViewFactory.h"
#include "TileView.h"
#include "SelectedTileView.h"
#include <ctime>
#include <cstdlib>
#include <SDL.h>

namespace game {

TileViewFactory::TileViewFactory() : m_tileImages(0) {
    std::srand(std::time(0));
}

void TileViewFactory::addAvailableTileImage(SDL_Surface* img) {
    m_tileImages.push_back(img);
}

TileView TileViewFactory::provideRandomTile(int x, int y) const {
    if(m_tileImages.empty()) {
        return TileView();
    }
    
    int type = std::rand() % m_tileImages.size();
    return TileView(x, y, m_tileImages[type]);
}

int TileViewFactory::getTileHeight() const {
    if(m_tileImages.empty()) {
        return -1;
    }
    return m_tileImages[0]->h;
}

int TileViewFactory::getTileWidth() const {
    if(m_tileImages.empty()) {
        return -1;
    }
    return m_tileImages[0]->w;
}

TileView* TileViewFactory::provideTileById(int x, int y, int id, int isSelected) const {
    if(m_tileImages.empty() || id < 0 || id > m_tileImages.size()) {
        return new TileView(); 
    }
    if(isSelected) {
        return new SelectedTileView(x, y, m_tileImages[id]);
    } else {
        return new TileView(x, y, m_tileImages[id]);
    }
}




} // namespace game
