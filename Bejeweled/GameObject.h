#ifndef __Bejeweled_GameObject_h__
#define __Bejeweled_GameObject_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <SDL.h>
#include <utility>
#include "Point.h"

namespace bejeweled {

/**
 * Interface for a game object that can update, draw, handleEvents.
 * Objects that are to be drawn on the screen should inherit from this class
 */
class GameObject{
public:
    /// Constructor - Sets the surface to NULL and sets position at (0, 0)
    GameObject();

    /// Constructor - sets the given position and the target surface
    GameObject(int x, int y, SDL_Surface* target = NULL);

    /// Destructor - Does NOT free the contained surface.
    virtual ~GameObject();

    /// Sets the game object origin at the given position.
    void setOrigin(int x, int y);

    /// Sets the game object target surface to the given one. Overrides previously set surface.
    void setTargetSurface(SDL_Surface* target);

    /// Game loop functions
    virtual void handleEvent(SDL_Event* event) = 0;
    virtual void update() = 0;
    virtual void draw() = 0;

    /// @return true    If the given coordinate is within the surface boundaries. false otherwise.
    virtual bool isPointInObject(int x, int y) const = 0;

protected:
    /// These are protected as the destination surface and its origins should be accessed by derived classes
    SDL_Surface* m_dstSurface;
    int m_originX, m_originY;
}; // class GameObject 

} // namespace bejeweled

#endif // __Bejeweled_GameObject_h__
