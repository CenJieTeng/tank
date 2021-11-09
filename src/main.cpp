#include <iostream>
#include "SDL2/SDL.h"
#include "GameState.h"
#include "Input.h"
#include "World.h"

int main(int argv, char** args)
{
	WORLD->init();
	GameState gameState(GameState::StateType::TITLE);
	
	while (true)
	{
		SDL_Delay(16);
		input()->update();
		gameState.update();
	}
	return 0;
}