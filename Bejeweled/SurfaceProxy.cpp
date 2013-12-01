#include <SDL.h>
#include <SDL_image.h>
#include <utility>
#include <string>
#include "Point.h"
#include "SurfaceProxy.h"
#include "GameException.h"

namespace bejeweled {

using std::string;

SDL_Surface* SurfaceProxy::loadOptimizedImage(const string& path) {
    SDL_Surface* loadedImg = IMG_Load(path.c_str());
    if(!loadedImg) {
        throw GameException();
    }
    
    SDL_Surface* optimizedImg = SDL_DisplayFormatAlpha(loadedImg);
    if(!optimizedImg) {
        throw GameException();
    } else {
        /// This is not mandatory if using transparent PNG's
        SDL_SetColorKey(optimizedImg, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImg->format, 0, 0xFF, 0xFF ) );
    }

    SDL_FreeSurface(loadedImg);
    return optimizedImg;
}

SDL_Surface* SurfaceProxy::loadRegularImage(const string& path) {
    SDL_Surface* loadedImg = IMG_Load(path.c_str());
    if(!loadedImg) {
        throw GameException();
    }
    return loadedImg;
}

void SurfaceProxy::draw(int x, int y, SDL_Surface* src, SDL_Surface* dst, SDL_Rect* clip) {
    if(!src || !dst) {
        throw GameException("Must draw to/from non-null surfaces.");
    }
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    if(SDL_BlitSurface(src, clip, dst, &offset)) {
        throw GameException();
    }
}

Point SurfaceProxy::getImageDimensions(const string& path) {
    SDL_Surface* loadedImg = IMG_Load(path.c_str());
    if(!loadedImg) {
        throw GameException();
    }
    int h = loadedImg->h;
    int w = loadedImg->w;

    SDL_FreeSurface(loadedImg);
    return std::make_pair(w,h);
}

} // namespace bejeweled
