#ifndef __Bejeweled_Drawable_h__
#define __Bejeweled_Drawable_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <SDL.h>

namespace bejeweled {

/**
 * Interface for drawable objects
 */
class Drawable
{
public:
    virtual void draw(SDL_Surface* dst, int x, int y) const = 0;

    /// Destructor
    virtual ~Drawable() {}
}; // class Drawable

} // namespace bejeweled



#endif // __Bejeweled_Drawable_h__