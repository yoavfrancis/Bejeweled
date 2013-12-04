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
    for(int i=0; i<m_music.size(); ++i) {
        Mix_FreeMusic(m_music.at(i));
    }
    for(int i=0; i<m_effects.size(); ++i) {
        Mix_FreeChunk(m_effects.at(i));
    }
    m_surfaces.clear();
    m_fonts.clear();
    m_music.clear();
    m_effects.clear();
}

SDL_Surface* ResourceManager::loadImage(const string& path) {
    SDL_Surface* img = SurfaceProxy::loadOptimizedImage(path);
    m_surfaces.push_back(img);
    return img;
}


SDL_Surface* ResourceManager::loadSimpleImage(const string& path) {
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

Mix_Music* ResourceManager::loadMusic(const string& path) {
    Mix_Music* music = Mix_LoadMUS(path.c_str());
    if(!music) {
        throw GameException();
    }
    m_music.push_back(music);
    return music;
}

Mix_Chunk* ResourceManager::loadEffect(const string& path) {
    Mix_Chunk* effect = Mix_LoadWAV(path.c_str());
    if(!effect) {
        throw GameException();
    }
    m_effects.push_back(effect);
    return effect;
}

} //namespace bejeweled
