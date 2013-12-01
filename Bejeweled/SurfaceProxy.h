#ifndef __Bejeweled_SurfaceProxy_h__
#define __Bejeweled_SurfaceProxy_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <utility>
#include <string>
#include "SDL.h"
#include "Point.h"

namespace bejeweled {

using std::string;

/**
 * Handles loading of Surfaces. 
 * Used to optimize the image to the current display format.
 * Also used for drawing of the surface.
 */
class SurfaceProxy
{
public:
    /**
     * Proxies loading of SDL_surface and returns an optimized version.
     * We do not want SDL to change the image format on every blit - so we will convert it.
     * (For instance, if the image has 24-bit depth, and the screen is 32-bit)
     *
     * Should only be called after we set the video mode with SDL_SetVideoMode.
     */ 
    static SDL_Surface* loadOptimizedImage(const string& path);
    
    /**
     * Proxies the call for IMG_Load. Does NOT optimize the loaded image.
     * This can be safely called before SDL_SetVideoMode (for example, in order to load an icon)
     */
    static SDL_Surface* loadRegularImage(const string& path);

    /**
     * Used to draw the surface according to the given parameters.
     */
    static void draw(int x, int y, SDL_Surface* src, SDL_Surface* dst, SDL_Rect* clip = NULL);

    /**
     * Returns the dimensions of an image at the given path.
     */
    static Point getImageDimensions(const string& path);

private:
    // Prevent Creation, Copying and Assignment
    SurfaceProxy();
    SurfaceProxy(const SurfaceProxy&);
    SurfaceProxy& operator=(const SurfaceProxy&);
}; // class SurfaceProxy

} // namespace bejeweled

#endif // __Bejeweled_SurfaceProxy_h__