#ifndef _WORLD_H_
#define _WORLD_H_

#include <list>
#include "SDL2/SDL.h"
#include "AABB.h"
#include "Play.h"
#include "tankAI.h"

class tank;
class bom;
class Play;
class SDL_Renderer;
class SDL_Window;

class World
{
public:
    void init();
    void reset();
    void createBom(double x, double y, int dir, char val);
    void destroyBom();

    template<typename T>
    bool collision(T box);

    static World* world();

private:
    World(){};

public:
    Play *play;
    int W, H;
    std::list<bom*> bomList;
    aabb::Tree tree;
    SDL_Window *win;
    SDL_Rect sceneBox;//场景大小
    SDL_Rect stageBox[100]; //场景方块
    SDL_Renderer *renderer = NULL;
};

#define WORLD World::world()

static int devsize = 6;
//碰撞检测
template<typename T>
bool World::collision(T box)
{
    //场景方块碰撞
    int w = W/11, h = H/19;
    for (int i = 0; i < 100; i++)
    {
        if (box.getX() + box.getW() - 5 > stageBox[i].x && box.getY() + box.getH() - 5 > stageBox[i].y
            && stageBox[i].x + w/2 > box.getX() && stageBox[i].y + h/2 > box.getY())
        {
            if (box.GetChar() == 'b' || box.GetChar() == 'd')
            {
                stageBox[i].x = -100;
                stageBox[i].y = -100;
            }
            
            return true;
        }
    }

    //弹击中AI
    tankAI **tis = play->tis;
    if (box.GetChar() == 'b')
    {
        for (int i=0; i<4; ++i)
        {
            if (tis[i] != NULL && box.getX() > tis[i]->getX() && box.getX() < tis[i]->getX() + W/11 && box.getY() > tis[i]->getY() && box.getY() < tis[i]->getY() + H/19)
            {
                Mix_PlayMusic(play->music2, 1);
                play->addScore(100);
                delete tis[i];
                tis[i] = NULL;
                return true;
            }
        }
    }

    //炮弹击中玩家
    if (box.GetChar() == 'd')
    {
        tank &t = play->t;
        if (box.getX() > t.getX() && box.getX() < t.getX() + W/11 && box.getY() > t.getY() && box.getY() < t.getY() + H/19)
        {
            t.beHurt();
            return true;
        }
    }

    //场景边缘碰撞
    if (box.getX() < sceneBox.x || box.getX() + box.getW()  > sceneBox.x + sceneBox.w 
            || box.getY() < sceneBox.y || box.getY() + box.getH() > sceneBox.y + sceneBox.h)
    {
        return true;
    }
	
	return false;
}

// template<typename T>
// bool World::collision(T box)
// {
//     //场景方块碰撞
//     int w = W/11, h = H/19;
//     for (int i = 0; i < 100; i++)
//     {
//         if (box.getX() + box.getW() - 5 > stageBox[i].x && box.getY() + box.getH() - 5 > stageBox[i].y
//             && stageBox[i].x + w/2 > box.getX() && stageBox[i].y + h/2 > box.getY())
//         {
//             if (box.GetChar() == 'b' || box.GetChar() == 'd')
//             {
//                 stageBox[i].x = -100;
//                 stageBox[i].y = -100;
//             }
            
//             return true;
//         }
//     }

//     //弹击中AI
//     tankAI **tis = play->tis;
//     if (box.GetChar() == 'b')
//     {
//         for (int i=0; i<4; ++i)
//         {
//             if (tis[i] != NULL && box.getX() > tis[i]->getX() && box.getX() < tis[i]->getX() + W/11 && box.getY() > tis[i]->getY() && box.getY() < tis[i]->getY() + H/19)
//             {
//                 Mix_PlayMusic(play->music2, 1);
//                 play->addScore(100);
//                 delete tis[i];
//                 tis[i] = NULL;
//                 return true;
//             }
//         }
//     }

//     //炮弹击中玩家
//     if (box.GetChar() == 'd')
//     {
//         tank &t = play->t;
//         if (box.getX() > t.getX() && box.getX() < t.getX() + W/11 && box.getY() > t.getY() && box.getY() < t.getY() + H/19)
//         {
//             t.beHurt();
//             return true;
//         }
//     }

//     //场景边缘碰撞
//     if (box.getX() < sceneBox.x || box.getX() + box.getW()  > sceneBox.x + sceneBox.w 
//             || box.getY() < sceneBox.y || box.getY() + box.getH() > sceneBox.y + sceneBox.h)
//     {
//         return true;
//     }
	
// 	return false;
// }

#endif