# Encroaching-Void-LD50-
My COMPO entry for Ludem Dare 50, using C++ and the SFML/TGUI libraries.

WASD to move, left click to shoot, right click to bless an area. 3 hits to kill an enemy. 
Bless resets on kill and does 1 hit to all enemies inside. Don’t let the void corrupt you! 
But let’s be honest.. it’s inevitable…

CURRENT BUG: Shooting from the walls seems to not work, this is because its collide with the wall (a result of my really shitty collision methods)
CURRENT BUG: Moving the window with a keydown will have you stuck moving in that direction. Resize or Lose Focus of Window to fix.

If you wish to compile your self for say linux, ensure you have downloaded SFML/2.5.1 and TGUI/0.9
If on windows, dont forget to set: SFML_DIR and TGUI_DIR.

Everything here was created within 48 hours.
*Except for CMAKELISTS, Classes: State.hpp/Engine.hpp/cpp
(These were downloaded from my prior projects on github: Algoviewer/TicTacShader.

Beware of the spagetti code.
