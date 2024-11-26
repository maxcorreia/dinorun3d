#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <SDL2/SDL.h>

struct Global{
	// Current dinosaur height
	int currentDinoHeight = 0;

	// Current cactus position
	int cactusPosition = 400;


};

// External linkage such that the
// global variable is available
// everywhere.
extern Global g;

#endif
