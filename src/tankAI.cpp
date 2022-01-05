#include"cstdlib"
#include"SDL2/SDL.h"
#include "World.h"
#include"bom.h"
#include"tankAI.h"

int dis = 0;//路程

//AI行为
void tankAI::AI(double elasped)
{
	double prex = x, prey = y;
	sportAI(elasped);
	if (rand() % 50 == 0)
		shoot();
	if(WORLD->collision(*this) || dis >= 50)
	{
		x = prex;
		y = prey;
		dis = 0;
		int i = rand() % 6;
		switch (i)
		{
			case 0:setDir(0);break;
			case 1:setDir(1);break;
			case 2:setDir(2);break;
			case 3:setDir(3);break;
		}
	}
}

//AI坦克移动
void tankAI::sportAI(double elasped)
{
	++dis;
	switch (getDir())
	{
		case 0:
		{
			x += speed * elasped;
		}break;
		case 1:
		{
			x -= speed * elasped;
		}break;
		case 2:
		{
			y -= speed * elasped;
		}break;
		case 3:
		{
			y += speed * elasped;
		}break;
	}

	std::vector<double> lowerBound({(double)x, (double)y});
	std::vector<double> upperBound({(double)(x + w), (double)(y + h)});
	WORLD->updateAABB((AABBKey)this, lowerBound, upperBound);
}