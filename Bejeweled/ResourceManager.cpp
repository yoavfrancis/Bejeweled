#include <string>
#include <SDL.h>
#include "ResourceManager.h"
#include "SurfaceProxy.h"
#include "GameException.h"


namespace bejeweled {

using std::string;

ResourceManager::ResourceManager() 
{ }

ResourceManager::~ResourceManager() {
    for(int i=0; i<m_surfaces.size(); ++i) {
        SDL_FreeSurface(m_surfaces.at(i));
    }
    for(int i=0; i<m_fonts.size(); ++i) {
        TTF_CloseFont(m_fonts.at(i));
    }
    m_surfaces.clear();
    m_fonts.clear();
}

SDL_Surface* ResourceManager::loadImage(const string& path) {
    SDL_Surface* img = SurfaceProxy::loadOptimizedImage(path);
    m_surfaces.push_back(img);
    return img;
}


SDL_Surface* ResourceManager::loadSimpleImage( const string& path ) {
    SDL_Surface* img = SurfaceProxy::loadRegularImage(path);
    m_surfaces.push_back(img);
    return img;
}

TTF_Font* ResourceManager::loadFont(const string& path, int size) {
    TTF_Font* font = TTF_OpenFont(path.c_str(), size);
    if(!font) {
        throw GameException();
    }
    m_fonts.push_back(font);
    return font;
}

} //namespace bejeweled

