#include "GameObject.h"

namespace bejeweled {

GameObject::GameObject() 
: m_dstSurface(NULL), m_originX(0), m_originY(0) 
{ }

GameObject::GameObject(int x, int y, SDL_Surface* target)
: m_originX(x), m_originY(y), m_dstSurface(target) 
{ }

GameObject::~GameObject() {
    // dst surface not to be freed by the game engine.
}

void GameObject::setOrigin(int x, int y) {
    m_originX = x;
    m_originY = y;
}

void GameObject::setTargetSurface(SDL_Surface* target) {
    m_dstSurface = target;
}

} // namespace bejeweled
