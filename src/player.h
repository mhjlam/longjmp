#pragma once
#include <SDL2/SDL.h>
#include <map>
#include <vector>
#include "maths.h"


class Block;

class Player
{
public:
	float x, y;
	float width, height;
	bool collides;
	float speed;
	Rect rect;


public:
	Player(float px, float py, float w, float h);

	void draw(SDL_Renderer* renderer);
	void update(std::map<int, bool> keys, std::vector<Block*>& blocks);
};
