#include "player.h"
#include "block.h"


extern int DISPLAY_WIDTH;
extern int DISPLAY_HEIGHT;



Player::Player(float px, float py, float w, float h) : x(px), y(py), width(w), height(h)
{
	speed = 20;

	rect.left = x;
	rect.right = x + width;
	rect.top = y;
	rect.bottom = y + height;
}


void Player::draw(SDL_Renderer* renderer)
{
	SDL_Rect sdlrect;
	sdlrect.x = (int)x;
	sdlrect.y = (int)y;
	sdlrect.w = (int)width;
	sdlrect.h = (int)height;

	SDL_SetRenderDrawColor(renderer, 255, 25, 25, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &sdlrect);
}


void Player::update(std::map<int, bool> keys, std::vector<Block*>& blocks)
{
	static int elapsed = 0;
	elapsed++;
	
	// sophisticated gravity simulation
	y += 10;


// 	if (keys[SDLK_LEFT] && x > 0)
// 	{
// 		x -= speed;
// 	}
// 	else if (keys[SDLK_RIGHT] && x < DISPLAY_WIDTH - width)
// 	{
// 		x += speed;
// 	}
// 
// 	if (keys[SDLK_UP] && y > 0)
// 	{
// 		y -= speed;
// 	}
// 	else if (keys[SDLK_DOWN] && y < DISPLAY_HEIGHT - height)
// 	{
// 		y += speed;
// 	}

	rect.left = x;
	rect.right = x + width;
	rect.top = y;
	rect.bottom = y + height;

	collides = false;

	for (auto block : blocks)
	{
		if (collision(rect, block->rect))
		{
			collides = true;

			if (rect.bottom > block->rect.top)
			{
				y = (block->y - height);
			}
		}
	}

	if (keys[SDLK_SPACE] && elapsed > 10 && collides)
	{
		y -= 100;
		elapsed = 0;
	}
}

