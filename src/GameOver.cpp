#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "World.h"
#include "Title.h"
#include "GameOver.h"

BaseState* GameOver::update()
{
    if (++count_ >= 60)
    {
        return new Title;
    }

    SDL_RenderCopyEx(renderer, tex, 0, 0, 90.0, 0, SDL_FLIP_NONE);
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);

    return nullptr;
}

void GameOver::enterState()
{
    win = WORLD->win;
	renderer = WORLD->renderer;

	//背景
    SDL_Surface *tempSur = NULL;
	tempSur = IMG_Load("../resources/over.jpg");
	tex = SDL_CreateTextureFromSurface(renderer, tempSur);
	SDL_FreeSurface(tempSur);
}

void GameOver::exitState()
{
}