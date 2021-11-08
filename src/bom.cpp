#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "World.h"
#include "Input.h"
#include "bom.h"

bom::bom(double x, double y, int dir, char val)
{
    this->x = x,
    this->y = y;
	this->dir = dir;
    this->val = val;
	h = w = 8;
}


//子弹碰撞
void bom::collision()
{
	static SDL_Surface *sur = IMG_Load("../resources/tank.png");
	static SDL_Texture *tex = SDL_CreateTextureFromSurface(WORLD->renderer, sur);

	if (WORLD->collision(*this))
	{
		state = -1;
		//绘制爆炸
		SDL_Rect cut = {690, 310, 24, 24};
		SDL_Rect box = {x - 12, y - 12, 24, 24};
		SDL_RenderCopy(WORLD->renderer, tex, &cut, &box);
	}
}

//子弹移动
void bom::sport()
{
	switch (dir)
	{
		case 0: 
		{				
			x += speed;
			collision();
		}break;
		case 1: 
		{				
			x -= speed;
			collision();
		}break;
		case 2:
		{
			y -= speed;
			collision();
		}break;
		case 3: 
		{				
			y += speed;
			collision();
		}break;
	}
}