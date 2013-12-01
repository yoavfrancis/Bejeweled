Bejeweled
====================================

This is my take on implementing the classical [Bejeweled](http://en.wikipedia.org/wiki/Bejeweled) / Match-3 game.
This is written purely with [SDL 1.2](http://www.libsdl.org/) and C++, and thus should be portable. (I've yet to test it on OSX/Linux though)

Unlike most implementations, I attempted to employ an object-oriented design to the game, using MVC and other approaches, making it very modular with an easy-to-pickup code

### Compilation Prerequisites 

These instructions are for compilation with VC++ on Windows machines. Compiling on other platforms isn't much harder - look for instructions on [Lazyfoo's SDL Tutorials](http://lazyfoo.net/SDL_tutorials/)

The provided solution file is of VS2013, but it can also be opened with VS2012. You can, of course, use any IDE of your choice.

- You need to have the following headers and libraries
 - [SDL 1.2.15](http://www.libsdl.org/release/SDL-devel-1.2.15-VC.zip)
 - [SDL\_ttf 2.0.11](http://www.libsdl.org/projects/SDL_ttf/release/SDL_ttf-devel-2.0.11-VC.zip) 
 - [SDL\_image 1.2.12](http://www.libsdl.org/projects/SDL_image/release/SDL_image-devel-1.2.12-VC.zip)
 - The VS project is configured to look for them under C:\SDL - but you can change it in the project properties.
- You also need to have the following DLL's in your project directory (files are available in the above packages)
 -  From SDL_ttf:
    - libfreetype-6.dll
    - SDL_ttf.dll
    - zlib1.dll
 - From SDL_image:
    - libjpeg-8.dll
    - libpng15-15.dll
    - SDL_image.dll
 - From SDL:
    - SDL.dll

If you are having a hard time compiling/linking/running with SDL, do not hesitate to check out [Lazyfoo's Tutorial](http://lazyfoo.net/SDL_tutorials/lesson01/windows/msvsnet2010e/index.php)

### Copyrights

Graphical resources are courtesy of the [Freegemas](https://code.google.com/p/freegemas/) project, an open-source bejeweled version built on top of the [Gosu](http://www.libgosu.org/) library. (GNU GPL v2)
The project is licensed under GPLv2 (see LICENSE.MD)












