#include"vector"
#include"stdio.h"
#include"SDL2/SDL.h"
#include"SDL2/SDL_mixer.h"
#include"SDL2/SDL_ttf.h"
#include"bom.h"
#include "Input.h"
#include "World.h"
#include"tankAI.h"
#include"tank.h"

int tank::w;
int tank::h;

tank::tank()
{
	std::vector<double> lowerBound({0, 0});
	std::vector<double> upperBound({0, 0});
	WORLD->insertAABB((AABBKey)this, lowerBound, upperBound);
}

tank::~tank()
{
	WORLD->removeAABB((AABBKey)this);
}

//坦克移动
void tank::sport()
{
	int offsetX = 0, offsetY = 0;
 	if (input()->isOn(Input::InputKey::INPUT_D))
	{
		dir = 0;
		offsetX = speed;
	}
	else if(input()->isOn(Input::InputKey::INPUT_A))
	{
		dir = 1;
		offsetX = -speed;
	}
	else if(input()->isOn(Input::InputKey::INPUT_W))
	{
		dir = 2;
		offsetY = -speed;
	}
	else if(input()->isOn(Input::InputKey::INPUT_S))
	{
		dir = 3;
		offsetY = speed;
	}
	x += offsetX;
	y += offsetY;
	std::vector<double> lowerBound({(double)x, (double)y});
	std::vector<double> upperBound({(double)(x + w), (double)(y + h)});
	WORLD->updateAABB((AABBKey)this, lowerBound, upperBound);

	if (WORLD->collision(*this))
	{
		//x -= offsetX ? (offsetX + (offsetX > 0 ? 1 : -1)) : 0;
		//y -= offsetY ? (offsetY + (offsetY > 0 ? 1 : -1)) : 0;
		x -= offsetX;
		y -= offsetY;
		std::vector<double> lowerBound2({(double)x, (double)y});
		std::vector<double> upperBound2({(double)(x + w), (double)(y + h)});
		WORLD->updateAABB((AABBKey)this, lowerBound2, upperBound2);
	}
}


int tank::getX()
{
	return x;
}

int tank::getY()
{
	return y;
}

int tank::getH()
{
	return h;
}

int tank::getW()
{
	return w;
}

int tank::getDir()
{
	return dir;
}

char tank::GetChar()
{
	return val;
}

void tank::setDir(int i)
{
	dir = i;
}

void tank::create()
{
	dir = 1;
	x =  400;
	y = 300 +  WORLD->H/19 * (rand() % 5);
	val = 'a';
	bomVal = 'd';
}

void tank::setX(double i)
{
	x = i;
}

void tank::setY(double i)
{
	y = i;
}

void tank::beHurt()
{
	dead = true;
}

bool tank::isDead()
{
	return dead;
}

void tank::handleInput()
{
	if (input()->isTrigger(Input::InputKey::INPUT_SPACE))
	{
		auto now = SDL_GetTicks();
		if (now - lastTick > 300)
		{
 			lastTick = now;
			shoot();
		}
			
	}
}

void tank::shoot()
{
	int W = WORLD->W;
	int H = WORLD->H;
	double bomx, bomy;
	switch (dir)
	{
		case 0:
		{
			bomx = x + W/11 - 10;
			bomy = y + H/19/2 + 2;
		}break;
		case 1:
		{
			bomx = x - 10;
			bomy = y + H/19/2;
		}break;
		case 2:
		{
			bomx = x + W/11/2 - 6;
			bomy = y - 5;
		}break;
		case 3:
		{
			bomx = x + W/11/2 - 6;
			bomy = y + H/19 - 16;
		}break;
	}
	WORLD->createBom(bomx, bomy, dir, bomVal);
}