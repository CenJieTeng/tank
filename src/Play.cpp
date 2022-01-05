#include <cmath>
#include <iostream>
#include "tank.h"
#include "tankAI.h"
#include "bom.h"
#include "World.h"
#include "GameOver.h"
#include "Title.h"
#include "Play.h"

BaseState* Play::update(double elasped)
{
    if (t->isDead())
    {
        return new GameOver;
    }

    //坦克更新
	t->handleInput();
    t->sport(elasped);

    //ai坦克更新
    for (int i = 0; i < numTis; ++i)
    {
        if (tis[i] != NULL)
        {
            tis[i]->AI(elasped);
        }
    }

    //bom更新
    for (auto iter = WORLD->bomList.begin(); iter != WORLD->bomList.end(); ++iter)
    {
		(*iter)->sport();
    }

	//清除bom
	WORLD->destroyBom();

	//绘制
    draw();

	//检测胜利
	if (checkWin())
	{
		return new Title;
	}

    return nullptr;
}

void Play::enterState()
{
	std::cout << "Play state" << std::endl;

	TTF_Init();
	win = WORLD->win;
	renderer = WORLD->renderer;
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
	
	//音乐&音效
	//开始音乐
	music1 = Mix_LoadMUS((file + "music1.wav").c_str());
	//爆炸音效
	music2 = Mix_LoadMUS((file + "music2.wav").c_str());
	//移动音效
	music3 = Mix_LoadMUS((file + "music3.wav").c_str());
	
	int W, H;
	SDL_GetWindowSize(win, &W, &H);//获取屏幕宽，高
	sh = H/19*10;
	w = W/11;
	h = H/19;
	box1 = {0, 0, w, h};
	box5[0] = {W/11, 800 + H/19/2, w/5, h/10};
	box5[1] = {W/11/2, 800 - H/19, h/10, w/5};
	box10 = {W-100, 0, 50, 50};
	box11 = {W-100, 50, 50, 50};
	tank::w = 30;
	tank::h = 30;
	sceneInit(W, H);

	//init world
	{
		SDL_Rect &sceneBox = WORLD->sceneBox;
		sceneBox = {0, (H-sh)/2, W, sh};
		WORLD->play = this;
		WORLD->H = H;
		WORLD->W = W;
		WORLD->reset();
	}

    SDL_Surface *tempSur = NULL;
	sur1 = IMG_Load((file + "tank.png").c_str());
	tex1 = SDL_CreateTextureFromSurface(renderer, sur1);
	//背景
	tempSur = IMG_Load((file + "background1.png").c_str());
	tex2 = SDL_CreateTextureFromSurface(renderer, tempSur);
	SDL_FreeSurface(tempSur);

	//按键
	tempSur = IMG_Load((file + "anjin1.png").c_str());
	tex3 = SDL_CreateTextureFromSurface(renderer, tempSur);
    SDL_FreeSurface(tempSur);

	//子弹
	tex4 = SDL_CreateTextureFromSurface(renderer, sur1);

	//场景方块
	tempSur = IMG_Load((file + "tank1.png").c_str());
	tex5 = SDL_CreateTextureFromSurface(renderer, tempSur);
	SDL_FreeSurface(tempSur);

	//子弹按键
	tempSur = IMG_Load((file + "anjin2.jpg").c_str());
	tex6 = SDL_CreateTextureFromSurface(renderer, tempSur);
	SDL_FreeSurface(tempSur);

	//游戏结束
	tempSur = IMG_Load((file + "over.jpg").c_str());
	tex7 = SDL_CreateTextureFromSurface(renderer, tempSur);
    SDL_FreeSurface(tempSur);

	//分数
	SDL_Color color = {255, 255, 255};
	font = TTF_OpenFont((file + "Miui-Light.ttf").c_str(), 800);
	tempSur = TTF_RenderUTF8_Blended(font, stu.c_str(), color);
	tex8 = SDL_CreateTextureFromSurface(renderer, tempSur);
	SDL_FreeSurface(tempSur);

	t = new tank();
	t->setX(0),
	t->setY(H/2);

    //创建ai
    for (int i = 0; i < numTis; ++i)
	{
		tis[i] = new tankAI;
		tis[i]->create();
	}

    //开始游戏声音
    //Mix_PlayMusic(music1, 1);
    
    //初始绘制
    SDL_RenderCopy(renderer, tex3, &cut3, &box2);
	SDL_RenderCopy(renderer, tex6, &cut5, &box6);
}

void Play::exitState()
{
	delete t;
	t = NULL;
	SDL_DestroyTexture(tex1);
	Mix_FreeMusic(music1);
	Mix_FreeMusic(music2);
	Mix_FreeMusic(music3);
	TTF_CloseFont(font);
	
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
}

void Play::addScore(int score)
{
	this->score += score;
}

void Play::drawTank(tank *t, SDL_Rect *cut)
{
    int dir = t->getDir();
    SDL_Rect box;
    box.x = t->getX();
    box.y = t->getY();
    box.w = w;
    box.h = h;
    SDL_RenderCopy(renderer, tex1, &cut1[dir], &box);
}

void Play::drawBom(bom &bom)
{
    int dir = bom.getDir();
    SDL_Rect box = box5[dir/2];
    box.x = bom.getX();
	box.y = bom.getY();
	SDL_RenderCopy(renderer, tex4, &cut2[dir], &box);
}

void Play::drawScore()
{
	SDL_Point center = {0, 0};
    double angle = 90.0;
    SDL_RenderCopyEx(renderer, tex8, NULL, &box10, angle, &center, SDL_FLIP_NONE);
	
	char buf[10];
	sprintf(buf, "%d", score);	
	SDL_Color color = {255, 255, 255};
	SDL_Surface *sur = TTF_RenderUTF8_Blended(font, buf, color);
	SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, sur);
	static unsigned int x;
	SDL_RenderCopyEx(renderer, tex, NULL, &box11, angle, &center, SDL_FLIP_NONE);
	SDL_FreeSurface(sur);
	SDL_DestroyTexture(tex);
}

//渲染函数
void Play::draw()
{
	//背景
	SDL_RenderCopy(renderer, tex2, NULL, &WORLD->sceneBox);

	//渲染场景方块
    SDL_Rect *stageBox = WORLD->stageBox;
	for (int i = 0; i < 100; i++)
	{
		SDL_RenderCopy(renderer, tex5, &cut4, &stageBox[i]);
		//SDL_SetRenderDrawColor(renderer, 0xff, 0, 0, 0xff);
		//SDL_RenderFillRect(renderer, &stageBox[i]);
	}

    //绘制坦克
	drawTank(t, cut1);

    //绘制ai坦克
    for (int i = 0; i < numTis; i++)
    {
		if (tis[i] != NULL)
		{
			drawTank(tis[i], cut1);
		}
    }

    //绘制坦克子弹
    for (auto iter = WORLD->bomList.begin(); iter != WORLD->bomList.end(); ++iter)
    {
        drawBom(*(*iter));
    }

	//绘制分数
	drawScore();
}

void Play::sceneInit(int W, int H)
{
    SDL_Rect *stageBox = WORLD->stageBox;
	//T
	stageBox[0] = {w/2*17, 190, w/2, h/2};
	stageBox[1] = {w/2*17, 190+h/2, w/2, h/2};
	stageBox[2] = {w/2*17, 190+h/2*2, w/2, h/2};
	stageBox[3] = {w/2*17, 190+h/2*3, w/2, h/2};
	stageBox[4] = {w/2*17, 190+h/2*4, w/2, h/2};
	stageBox[5] = {w/2*16, 190+h/2*2, w/2, h/2};
	stageBox[6] = {w/2*15, 190+h/2*2, w/2, h/2};
	stageBox[7] = {w/2*14, 190+h/2*2, w/2, h/2};
	stageBox[8] = {w/2*13, 190+h/2*2, w/2, h/2};
	//A
	stageBox[9] = {w/2*17, 190+h/2*7, w/2, h/2};
	stageBox[10] = {w/2*16, 190+h/2*6+h/4 , w/2, h/2};
	stageBox[11] = {w/2*16, 190+h/2*7+h/4 , w/2, h/2};
	stageBox[12] = {w/2*15, 190+h/2*6, w/2, h/2};
	stageBox[13] = {w/2*15, 190+h/2*8, w/2, h/2};
	stageBox[14] = {w/2*14, 190+h/2*5+h/4, w/2, h/2};
	stageBox[15] = {w/2*14, 190+h/2*6+h/4, w/2, h/2};
	stageBox[16] = {w/2*14, 190+h/2*7+h/4, w/2, h/2};
	stageBox[17] = {w/2*14, 190+h/2*8+h/4, w/2,h/2};
	stageBox[18] = {w/2*13, 190+h/2*5, w/2,h/2};
	stageBox[19] = {w/2*13, 190+h/2*9, w/2,h/2};
	//N
	stageBox[20] = {w/2*17, 190+h/2*11, w/2, h/2};
	stageBox[21] = {w/2*16, 190+h/2*11, w/2, h/2};
	stageBox[22] = {w/2*15, 190+h/2*11, w/2, h/2};
	stageBox[23] = {w/2*14, 190+h/2*11, w/2, h/2};
	stageBox[24] = {w/2*13, 190+h/2*11, w/2, h/2};
	stageBox[25] = {w/2*16, 190+h/2*12, w/2, h/2};
	stageBox[26] = {w/2*15, 190+h/2*12+h/4, w/2, h/2};
	stageBox[27] = {w/2*14, 190+h/2*13, w/2, h/2};
	stageBox[28] = {w/2*17, 190+h/2*14, w/2, h/2};
	stageBox[29] = {w/2*16, 190+h/2*14, w/2, h/2};
	stageBox[30] = {w/2*15, 190+h/2*14, w/2, h/2};
	stageBox[31] = {w/2*14, 190+h/2*14, w/2, h/2};
	stageBox[32] = {w/2*13, 190+h/2*14, w/2, h/2};
	//K
	stageBox[33] = {w/2*17, 190+h/2*16, w/2, h/2};
	stageBox[34] = {w/2*16, 190+h/2*16, w/2, h/2};
	stageBox[35] = {w/2*15, 190+h/2*16, w/2, h/2};
	stageBox[36] = {w/2*14, 190+h/2*16, w/2, h/2};
	stageBox[37] = {w/2*13, 190+h/2*16, w/2, h/2};
	stageBox[38] = {w/2*17, 190+h/2*19, w/2, h/2};
	stageBox[39] = {w/2*16, 190+h/2*18, w/2, h/2};
	stageBox[40] = {w/2*15, 190+h/2*17, w/2, h/2};
	stageBox[41] = {w/2*14, 190+h/2*18, w/2, h/2};
	stageBox[42] = {w/2*13, 190+h/2*19, w/2, h/2};
	//2
	stageBox[43] = {w/2*10, 190+h/2, w/2, h/2};
	stageBox[44] = {w/2*10, 190+h/2*2, w/2, h/2};
	stageBox[45] = {w/2*10, 190+h/2*3, w/2, h/2};
	stageBox[46] = {w/2*10, 190+h/2*4, w/2, h/2};
	stageBox[47] = {w/2*9, 190+h/2*4, w/2, h/2};
	stageBox[48] = {w/2*8, 190+h/2*4, w/2, h/2};
	stageBox[49] = {w/2*8, 190+h/2, w/2, h/2};
	stageBox[50] = {w/2*8, 190+h/2*2, w/2, h/2};
	stageBox[51] = {w/2*8, 190+h/2*3, w/2, h/2};
	stageBox[52] = {w/2*7, 190+h/2, w/2, h/2};
	stageBox[53] = {w/2*6, 190+h/2, w/2, h/2};
	stageBox[54] = {w/2*6, 190+h/2*2, w/2, h/2};
	stageBox[55] = {w/2*6, 190+h/2*3, w/2, h/2};
	stageBox[56] = {w/2*6, 190+h/2*4, w/2, h/2};
	//0
	stageBox[58] = {w/2*10, 190+h/2*6, w/2, h/2};
	stageBox[59] = {w/2*10, 190+h/2*7, w/2, h/2};
	stageBox[60] = {w/2*10, 190+h/2*8, w/2, h/2};
	stageBox[61] = {w/2*10, 190+h/2*9, w/2, h/2};
	stageBox[62] = {w/2*9, 190+h/2*6, w/2, h/2};
	stageBox[63] = {w/2*8, 190+h/2*6, w/2, h/2};
	stageBox[64] = {w/2*7, 190+h/2*6, w/2, h/2};
	stageBox[65] = {w/2*6, 190+h/2*6, w/2, h/2};
	stageBox[66] = {w/2*9, 190+h/2*9, w/2, h/2};
	stageBox[67] = {w/2*8, 190+h/2*9, w/2, h/2};
	stageBox[68] = {w/2*7, 190+h/2*9, w/2, h/2};
	stageBox[69] = {w/2*6, 190+h/2*9, w/2, h/2};
	stageBox[70] = {w/2*6, 190+h/2*7, w/2, h/2};
	stageBox[71] = {w/2*6, 190+h/2*8, w/2, h/2};
	//1
	stageBox[72] = {w/2*10, 190+h/2*12, w/2, h/2};
	stageBox[73] = {w/2*10, 190+h/2*13, w/2, h/2};
	stageBox[74] = {w/2*9, 190+h/2*11, w/2, h/2};
	stageBox[75] = {w/2*9, 190+h/2*12, w/2, h/2};
	stageBox[76] = {w/2*9, 190+h/2*13, w/2, h/2};
	stageBox[77] = {w/2*8, 190+h/2*12, w/2, h/2};
	stageBox[78] = {w/2*8, 190+h/2*13, w/2, h/2};
	stageBox[79] = {w/2*7, 190+h/2*12, w/2, h/2};
	stageBox[80] = {w/2*7, 190+h/2*13, w/2, h/2};
	stageBox[81] = {w/2*6, 190+h/2*12, w/2, h/2};
	stageBox[82] = {w/2*6, 190+h/2*13, w/2, h/2};
	//7
	stageBox[83] = {w/2*10, 190+h/2*15, w/2, h/2};
	stageBox[84] = {w/2*10, 190+h/2*16, w/2, h/2};
	stageBox[85] = {w/2*10, 190+h/2*17, w/2, h/2};
	stageBox[86] = {w/2*10, 190+h/2*18, w/2, h/2};
	stageBox[87] = {w/2*9, 190+h/2*15, w/2, h/2};
	stageBox[88] = {w/2*9, 190+h/2*18, w/2, h/2};
	stageBox[89] = {w/2*8, 190+h/2*15, w/2, h/2};
	stageBox[90] = {w/2*8, 190+h/2*18, w/2, h/2};
	stageBox[91] = {w/2*7, 190+h/2*18, w/2, h/2};
	stageBox[92] = {w/2*6, 190+h/2*18, w/2, h/2};
	//scene box
	stageBox[93] = {-4, 0, 2, H};
	stageBox[94] = {W, 0, 2, H};
	stageBox[95] = {0, (H-sh)/2, W, 2};
	stageBox[96] = {0, (H-sh)/2+sh, W, 2};
}

bool Play::checkWin()
{
	for (int i = 0; i < 4; i++)
	{
		if (tis[i])
		{
			return false;
		}
	}
	return true;
}