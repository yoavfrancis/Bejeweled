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

void SurfaceProxy::applyAnaglyph3D(SDL_Surface* src, SDL_Surface* dst, int shift) {
    if (!src || !dst) {
        throw GameException("Must apply anaglyph to/from non-null surfaces.");
    }

    SDL_LockSurface(src);
    SDL_LockSurface(dst);

    int w = dst->w;
    int h = dst->h;

    for (int y = 0; y < h; y++) {
        Uint32* srcRow = (Uint32*)((Uint8*)src->pixels + y * src->pitch);
        Uint32* dstRow = (Uint32*)((Uint8*)dst->pixels + y * dst->pitch);

        for (int x = 0; x < w; x++) {
            Uint8 r = 0, g = 0, b = 0;
            Uint8 lr, lg, lb, rr, rg, rb;

            // Left eye: red channel, source shifted right by 'shift' pixels
            int leftX = x + shift;
            if (leftX >= 0 && leftX < src->w) {
                SDL_GetRGB(srcRow[leftX], src->format, &lr, &lg, &lb);
                r = lr;
            }

            // Right eye: green+blue channels, source shifted left by 'shift' pixels
            int rightX = x - shift;
            if (rightX >= 0 && rightX < src->w) {
                SDL_GetRGB(srcRow[rightX], src->format, &rr, &rg, &rb);
                g = rg;
                b = rb;
            }

            dstRow[x] = SDL_MapRGB(dst->format, r, g, b);
        }
    }

    SDL_UnlockSurface(dst);
    SDL_UnlockSurface(src);
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
