#include"cstdlib"
#include"SDL2/SDL.h"
#include "World.h"
#include"bom.h"
#include"tankAI.h"

int j = 0;//方块个数
int deva = -1;//误差判断
int dis = 0;//路程
extern int devasize;//误差大小

//AI行为
void tankAI::AI()
{
	double prex = x, prey = y;
	sportAI();
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
void tankAI::sportAI()
{
	++dis;
	switch (getDir())
	{
		case 0:
		{
			x += speed;
		}break;
		case 1:
		{
			x -= speed;
		}break;
		case 2:
		{
			y -= speed;
		}break;
		case 3:
		{
			y += speed;
		}break;
	}
}