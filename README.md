Bejeweled
========
This is my take on implementing the classical [Bejeweled](http://en.wikipedia.org/wiki/Bejeweled)/Match-3 game.  It's written purely with [SDL 1.2](http://www.libsdl.org/) and C++, and thus should be portable. (I've yet to test it on OSX/Linux though)

Unlike many game implementations, I attempted to employ an object-oriented design to the game, using [MVC](http://en.wikipedia.org/wiki/Model%E2%80%93view%E2%80%93controller) and other approaches, making it very modular and an _easy-to-pickup_ code.

[![](http://i.imgur.com/0E9NY9A.png)](http://youtu.be/vLgxC8o44g8)

### Compilation Prerequisites 

These instructions are for compilation with VC++ on Windows machines. Compiling on other platforms isn't much harder - look for instructions on [Lazyfoo's SDL Tutorials](http://lazyfoo.net/SDL_tutorials/)
	
The provided solution file is of VS2013, but it can also be opened with VS2012. You can, of course, use any IDE of your choice.

- You need to have the following headers and libraries
 - [SDL 1.2.15](http://www.libsdl.org/release/SDL-devel-1.2.15-VC.zip)
 - [SDL\_ttf 2.0.11](http://www.libsdl.org/projects/SDL_ttf/release/SDL_ttf-devel-2.0.11-VC.zip) 
 - [SDL\_image 1.2.12](http://www.libsdl.org/projects/SDL_image/release/SDL_image-devel-1.2.12-VC.zip)
 - [SDL\_mixer 1.2.12](http://www.libsdl.org/projects/SDL_mixer/release/SDL_mixer-devel-1.2.12-VC.zip)
 - The VS project is configured to look for the headers/libraries in matching subdirectories under C:\SDL - but you can change it in the project properties.

- You also need to have the following DLL's in your project directory (files are available in the above packages)
 -  From SDL_ttf:
    - libfreetype-6.dll
    - SDL_ttf.dll
    - zlib1.dll
 - From SDL_image:
    - libjpeg-8.dll
    - libpng15-15.dll
    - SDL_image.dll
 - From SDL_mixer:
    - SDL_mixer.dll
	- libvorbis-0.dll
	- libvorbis-0.dll
	- libogg-0.dll
 - From SDL:
    - SDL.dll

If you are having a hard time compiling/linking/running with SDL, do not hesitate to check out [Lazyfoo's Tutorial](http://lazyfoo.net/SDL_tutorials/lesson01/windows/msvsnet2010e/index.php)

### Copyrights

Graphical resources and sound effects are courtesy of the [Freegemas](https://code.google.com/p/freegemas/) project, an open-source Bejeweled version built on top of the [Gosu](http://www.libgosu.org/) library (GNU GPL v2).
Background music(_A Conversation with Saul (Jazz/Blues Shuffle)_) by [Matthew Pablo](http://opengameart.org/content/a-conversation-with-saul-jazzblues-shuffle) (CC-BY 3.0)
Rest of the project is licensed under GPLv2 (see LICENSE.MD)

### Author

[Yoav Francis](https://www.linkedin.com/in/yoavfrancis)

### Future todo's:

- Employ State pattern for different states (main menu, game screen, records screen, etc.)
- Employ Strategy pattern for abstraction of game mechanics.

-------

Appendix -  Design Ideas
------------------

I'll not delve into the code itself, but I'll try to abstractly present the "algorithm" (Or to put more correctly, how the game works)

In putting the game to an [MVC](http://en.wikipedia.org/wiki/Model%E2%80%93view%E2%80%93controller) design, There arises the following problem : 

Consider the "View" part, which essentially handles drawing to the screen - must reflect the board state ("Model"). However, if a match was to be found on the board - it'll be cleared, new tiles will be dropped to the board - and it will again be drawn to the user.

This is _very_ unpleasant, to say the least, in regards to user experience - the user will see the board shifting from one state to another, totally different state - without any transition.

And thus we must find a way to draw the board in _every step of change_. "A step" is a vague definition - but for that matter what it means is every change in the board model.

And so, once we alter our model to work in a "step-wise" fashion (which will soon be explained more clearly), our view part _easily_ reflects the board state to create a satisfiable user experience.

The best way to model the board states would be with a deterministic finite automaton (DFA). The "Controller" manages the current state of the board and follows the following  DFA for the board states ("state of the model"):

__Pleaes note that this should accompany you when you review the code, otherwise it may be a bit hard to comprehend without relevant screenshots__ (_Which I plan to add later on_)

![](http://i.imgur.com/74Y6lcA.png "DFA for Bejeweled")

1. Uninitialized
  * Uninitialized state set by the controller.
2. Freeze
  * Board is initialized with random tiles. User has not pressed "Play" yet so board is unplayable and not drawn.
3. Check if there are no moves
  * There is a chance that the board will be generated or reach a state without any possible moves (tile switches that generate a sequence of 3 or more tiles)
4. No moves are available
  * Game is over and player is notified
5. Ready
  * Board is ready to be played (clicked)
6. Selected first tile
7. Selected second tile
8. Gravitate rows once
  - Consider the board state now. We have some missing tiles (corresponding to the positions in which the match was found
  - We would like to "pull down" the tiles above them, essentially putting some "gravity" into play and bring down the tiles above.
  - This is done "step-by-step" in order to give a better user experience.
  - Once the board is "gravitatized" - we can drop new tiles from above.
9. Drop new tiles from above
  - Drops a single row of new tiles
  - If no tile was dropped - time to check the board for matches.
  - otherwise, we need to "graviatize" the board again, bringing the new tiles down to their respective positions.
10. Board is now in the stable state ("Gravitatized" and with no empty tiles that await to be filled with tiles "from above")
 - If there are no matching sequences on the board, we can head back to the (3) state.
 - Otherwise, matching sequences are eliminated and the board is sent to the (8) state, just as if the user made a valid switch that resulted in a match.