#include <cmath>
#include <iostream>
#include <string>
#include <algorithm>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include "Input.h"
#include "World.h"
#include "Play.h"
#include "Title.h"

BaseState* Title::update()
{
    if (input()->isTrigger(Input::InputKey::INPUT_SPACE))
    {
        return new Play;
    }

    SDL_Point center2 = {512/2, 448/2};
    SDL_Rect box2 = {0, 448/2, 512, 448};
    SDL_RenderCopyEx(renderer, bgTex, 0, &box2, 90.0, &center2, SDL_FLIP_NONE);

    // int w, h;
    // TTF_SizeUTF8(font, "任意键开始", &w, &h);
    SDL_Point center = {0, 0};
    SDL_Rect box = {100, 400, 90, 24};
    static int x = 0;
    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(tex, abs(sin(x++/32.0)) * 255.0);
    SDL_RenderCopyEx(renderer, tex, 0, &box, 90.0, &center, SDL_FLIP_NONE);

    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
        
    return nullptr;
}

void Title::enterState()
{
    TTF_Init();
    win = WORLD->win;
	renderer = WORLD->renderer;
    font = TTF_OpenFont("../resources/Miui-Light.ttf", 18);

    SDL_Surface *sur = TTF_RenderUTF8_Blended(font, "空 格 键 开 始", SDL_Color{255, 255, 255});
    tex = SDL_CreateTextureFromSurface(renderer, sur);

    sur = IMG_Load("../resources/title.jpg");
    bgTex = SDL_CreateTextureFromSurface(renderer, sur);

    SDL_FreeSurface(sur);
}

void Title::exitState()
{
    SDL_DestroyTexture(tex);
    TTF_CloseFont(font);

    TTF_Quit();
}