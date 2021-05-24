#include "level.h"
#include "block.h"

#include <random>


extern int DISPLAY_WIDTH;
extern int DISPLAY_HEIGHT;


Level::Level()
{
	init();
}

Level::~Level()
{
	for (auto b : blocks) delete b;

	destroy();
}


void Level::init()
{
	float x = 0.f;

	for (int i = 0; i < 8; ++i)
	{
		addblock(x, DISPLAY_HEIGHT - 200.f, 150.f, 200.f);
		x += (150.f + 0.f);
	}
}


void Level::draw(SDL_Renderer* renderer)
{
	for (auto b : blocks)
		b->draw(renderer);
}


void Level::update()
{
	std::random_device rd;
	std::mt19937 mt(rd());

	std::uniform_int_distribution<int> spawn(0, 100);
	std::uniform_int_distribution<int> space(1, 2);
	std::uniform_real_distribution<float> height(100, 300);


	// move blocks
	for (auto block : blocks)
	{
		block->x -= 4;
		block->update();
	}

	// remove blocks passed from screen
	auto first = blocks.front();

	if (first->x < -first->width)
	{
		delete first;
		blocks.erase(blocks.begin());
	}

	// spawn new block at end
	auto last = blocks.back();

	if (last->x + last->width < DISPLAY_WIDTH)
	{
		float spacing = 10.f + (5.f * space(mt));
		if (spawn(mt) < 12) spacing += 150.f;

		float x = (last->x + last->width) + spacing;
		float h = height(mt);

		addblock(x, DISPLAY_HEIGHT - h, 150.f, h);
	}
}


void Level::destroy()
{
	
}


void Level::addblock(float x, float y, float width, float height)
{
	blocks.push_back(new Block(x, y, width, height));
}


void Level::addblock(float width, float height, float spacing)
{
	blocks.push_back(new Block(DISPLAY_WIDTH + spacing, DISPLAY_HEIGHT - height, width, height));
}

