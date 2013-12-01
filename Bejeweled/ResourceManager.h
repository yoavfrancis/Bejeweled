#ifndef __GameTest_ResourceManager__
#define __GameTest_ResourceManager__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <Vector>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

namespace game {

using std::string;

/**
 * The resource manager. Used to load and unload images and fonts.
 * There CAN be multiple instances of this class - instead of doing it a singleton.
 * Singleton would yield no added value here and can introduce more problems (destruction, global initialization, etc.).
 */
class ResourceManager
{
public:
    ResourceManager();

    /// frees all the loaded images within the context of this manager instance
    ~ResourceManager();

    /** 
     * Loads an optimized version of the image and saves it in the surfaces vector, 
     * which is freed upon class destruction. This must be called after calling SetVideoMode.
     */
    SDL_Surface* loadImage(const string& path);

    /**
     * Loads a non-optimized version of the image.
     * can be safely called before calling SetVideoMode
     */
    SDL_Surface* loadSimpleImage(const string& path);

    /**
     * Loads a font and saves it to the font vector, to be freed upon class destruction.
     * Font path should be a local path.
     */
    TTF_Font* loadFont(const string& path, int size);

private:

    /// Prevent Copying and Assignment
    ResourceManager(const ResourceManager&);
    ResourceManager& operator=(const ResourceManager&);

    std::vector<SDL_Surface*> m_surfaces;
    std::vector<TTF_Font*> m_fonts;

}; // class ResourceManager

} // namespace game

#endif // __GameTest_ResourceManager__
