#pragma once

#include <SDL2/SDL.h>
#include "maths.h"


class Block
{
public:
	float x, y;
	float width, height;
	Rect rect;

public:
	Block(float px = 0.f, float py = 0.f, float w = 10.f, float h = 10.f);

	void draw(SDL_Renderer* renderer);
	void update();
};
