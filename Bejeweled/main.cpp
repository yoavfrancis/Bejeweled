#include <iostream>
#include "Engine.h"
#include "GameException.h"

using game::Engine;
using game::GameException;

int main(int argc, char* argv[]) {
    try {
        Engine().run();
    } catch(const GameException& ex) {
        std::cerr << "Error occurred : " << ex.what() << std::endl;
        return 1;
    } catch(...) {
        std::cerr << "An unhandled exception was thrown" << std::endl;
        return 1;
    }
    return 0;
}