#pragma once

#include <SDL2/SDL.h>
#include <map>

class Level;
class Player;

class Game
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	Level* level;
	Player* player;

	int frameskip;
	bool running;
	std::map<int, bool> keys;


public:
	Game();
	~Game();

	void init();
	void start();
	void stop();
	void quit();

	void run();
	void draw();
	void update();

	void keydown(SDL_Event* event);
	void keyup(SDL_Event* event);


private:
	void fillrect(SDL_Rect rc, int r, int g, int b);
	void showfps(int fps);
};
