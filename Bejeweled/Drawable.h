#ifndef __GameTest_Drawable_h__
#define __GameTest_Drawable_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <SDL.h>

namespace game {

/**
 * Interface for drawable objects
 */
class Drawable
{
public:
    virtual void draw(SDL_Surface* dst) const = 0;

    /// Destructor
    virtual ~Drawable() {}
}; // class Drawable

} // namespace game



#endif // __GameTest_Drawable_h__