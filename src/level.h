#pragma once
#include <SDL2/SDL.h>
#include <vector>

class Block;

class Level
{
public:
	std::vector<Block*> blocks;


public:
	Level();
	~Level();

	virtual void init();
	virtual void draw(SDL_Renderer* renderer);
	virtual void update();
	virtual void destroy();

	virtual void addblock(float x, float y, float width, float height);
	virtual void addblock(float width, float height, float spacing);
};
