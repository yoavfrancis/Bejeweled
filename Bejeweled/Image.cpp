#include "Image.h"
#include <SDL_image.h>
#include <SDL.h>

namespace game_test 
{

Image::Image(const char* path)
: m_surface(IMG_Load(path)) {

}

Image::Image(const Image& other) 
: m_surface(other.m_surface->
}

Image::~Image() {
    SDL_FreeSurface(m_surface);
}

} // namespace game_test