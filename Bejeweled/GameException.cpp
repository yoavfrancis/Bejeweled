#include <SDL.h>
#include "GameException.h"

namespace bejeweled {

GameException::GameException() : runtime_error(SDL_GetError()) {
}

GameException::GameException(const string& msg) : runtime_error(msg) {
}

GameException::GameException(const char* msg) : runtime_error(msg) {
}

GameException::~GameException() throw() {
}

} //namespace bejeweled
