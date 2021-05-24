#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <cstdio>
#include <map>
#include "game.h"

int main(int argc, char* argv[])
{
	Game game;
	game.start();
	return 0;
}
