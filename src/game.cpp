#include "game.h"
#include "level.h"
#include "block.h"
#include "player.h"
#include "maths.h"


int DISPLAY_WIDTH = 1280;
int DISPLAY_HEIGHT = 720;
int UPDATE_INTERVAL = 1000 / 60;


Game::Game() : frameskip(0), running(0), window(nullptr), renderer(nullptr)
{
	init();
}

Game::~Game()
{
	delete level;
	delete player;

	stop();
}


void Game::init()
{
	level = new Level();
	player = new Player(100, 200, 50, 50);
}

void Game::start()
{
	int flags = SDL_WINDOW_SHOWN;

	if (SDL_Init(SDL_INIT_EVERYTHING))
		return;

	if (SDL_CreateWindowAndRenderer(DISPLAY_WIDTH, DISPLAY_HEIGHT, flags, &window, &renderer))
		return;

	run();
}

void Game::stop()
{
	if (renderer)
	{
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	if (window)
	{
		SDL_DestroyWindow(window);
		window = nullptr;
	}

	SDL_Quit();
}

void Game::quit()
{
	running = false;
}



void Game::run()
{
	running = true;

	int past = SDL_GetTicks();
	int now = past, pastFps = past;
	int fps = 0, framesSkipped = 0;
	
	SDL_Event event;

	while (running)
	{
		int timeElapsed = 0;

		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit();
				break;

			case SDL_KEYDOWN:
				keydown(&event);
				break;

			case SDL_KEYUP:
				keyup(&event);
				break;

			case SDL_MOUSEBUTTONDOWN:
				break;

			case SDL_MOUSEBUTTONUP:
				break;

			case SDL_MOUSEMOTION:
				break;
			}
		}

		// update/draw
		timeElapsed = (now = SDL_GetTicks()) - past;

		if (timeElapsed >= UPDATE_INTERVAL)
		{
			past = now;
			update();

			if (framesSkipped++ >= frameskip)
			{
				draw();
				++fps;
				framesSkipped = 0;
			}
		}

		// fps
		if (now - pastFps >= 1000)
		{
			pastFps = now;
			showfps(fps);
			fps = 0;
		}

		SDL_Delay(1);
	}
}

void Game::update()
{
	level->update();
	player->update(keys, level->blocks);
}

void Game::draw()
{
	// Clear screen
	SDL_SetRenderDrawColor(renderer, 10, 10, 10, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	// draw level and player
	level->draw(renderer);
	player->draw(renderer);

	SDL_RenderPresent(renderer);
}


void Game::keydown(SDL_Event* evt)
{
	keys[evt->key.keysym.sym] = true;

	if (keys[SDLK_ESCAPE]) quit();
}

void Game::keyup(SDL_Event* evt)
{
	keys[evt->key.keysym.sym] = false;
}



void Game::fillrect(SDL_Rect rc, int r, int g, int b)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &rc);
}

void Game::showfps(int fps)
{
	char szFps[128];
	sprintf_s(szFps, 128, "%s (%d FPS)", "Spring", fps);
	SDL_SetWindowTitle(window, szFps);
}

