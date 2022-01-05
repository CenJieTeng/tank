#include <ctime>
#include <iostream>
#include "SDL2/SDL.h"
#include "GameState.h"
#include "Input.h"
#include "World.h"

#define MS_PRE_UPDATE 16

int main(int argv, char** args)
{
	WORLD->init();
	GameState gameState(GameState::StateType::TITLE);
	int totalFram = 0;
	time_t preTime = clock();
	double lag = 0;
	time_t lastTime = clock();
	while (true)
	{
		time_t current = clock();
		double elasped = std::difftime(current, lastTime);
		lastTime = current;

		lag += elasped;
		bool update = false;
		while (lag >= MS_PRE_UPDATE)
		{
			//update
			update = true;
			input()->update();
			gameState.update(MS_PRE_UPDATE/1000.0);
			lag -= MS_PRE_UPDATE;
		}
		
		if (update)
		{
			//calc fps
			totalFram += 1;
			if (totalFram == 30)
			{
				std::cout << elasped << "ms " << totalFram / std::difftime(current, preTime) * 1000 << "fps" << std::endl;
				totalFram = 0;
				preTime = clock();
			}

			//render
			SDL_RenderPresent(WORLD->renderer);
			SDL_RenderClear(WORLD->renderer);
		}
		else
		{
			SDL_Delay(1);
		}
	}
	return 0;
}