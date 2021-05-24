#include "block.h"


Block::Block(float px, float py, float w, float h) : x(px), y(py), width(w), height(h)
{
	rect.left = x;
	rect.right = x + width;
	rect.top = y;
	rect.bottom = y + height;
}


void Block::draw(SDL_Renderer* renderer)
{
	SDL_Rect sdlrect;
	sdlrect.x = (int)x;
	sdlrect.y = (int)y;
	sdlrect.w = (int)width;
	sdlrect.h = (int)height;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &sdlrect);
}

void Block::update()
{
	rect.left = x;
	rect.right = x + width;
	rect.top = y;
	rect.bottom = y + height;
}

