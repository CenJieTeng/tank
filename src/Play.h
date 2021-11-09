#ifndef _PLAY_H_
#define _PLAY_H_

#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
#include "tank.h"
#include "bom.h"
#include "BaseState.h"

class tank;
class tankAI;
class World;

class Play : public BaseState
{
    friend World;
public:
    void addScore(int score);

protected:
    virtual void enterState() override;
    virtual BaseState* update() override;
    virtual void exitState() override;

private:
    void drawTank(tank *t, SDL_Rect *cut);
    void drawBom(bom &bom);
    void drawScore();
    void draw();
    void sceneInit(int W, int H);
    bool checkWin();

private:
    const std::string file = "../resources/";//资源路径
    const std::string stu = "分数:";
    SDL_Window *win = NULL;//窗口
    SDL_Renderer *renderer = NULL;//渲染器
    SDL_Surface *sur1 = NULL;//表面
    SDL_Texture *tex1 = NULL;//坦克画刷
    SDL_Texture *tex2 = NULL;//背景画刷
    SDL_Texture *tex3 = NULL;//按键画刷
    SDL_Texture *tex4 = NULL;//子弹画刷
    SDL_Texture *tex5 = NULL;//场景方块画刷
    SDL_Texture *tex6 = NULL;//子弹按键画刷
    SDL_Texture *tex7 = NULL;//游戏结束画刷
    SDL_Texture *tex8 = NULL;//分数层画刷
    TTF_Font *font = NULL;//字体
    Mix_Music *music1 = NULL;//开始音乐
    Mix_Music *music2 = NULL;//爆炸音乐
    Mix_Music *music3 = NULL;//坦克移动音乐
    tank *t;//坦克
    tankAI *tis[4];
    int numTis = 4;
    int sh;//场景高
    int w, h;//单位宽，高
    bool end = true;//判断游戏结束
    SDL_Rect box1;//单位方格
    SDL_Rect box2 = {30, 80, 100, 100};//按键大小
    SDL_Rect box5[2];//子弹(左右.上下)大小
    SDL_Rect box6 = {100,1600, 200, 200};//子弹按键大小
    //SDL_Rect box9;//子弹爆炸大小
    SDL_Rect box10;//分数层位置
    SDL_Rect box11;//分数位置
    SDL_Rect cut1[4] = {70, 0, 30, 30, 210, 0, 30, 30, 38, 0, 30, 35, 140, 0, 30, 35};//坦克截图
    SDL_Rect cut2[4] = {10, 180, 8, 8, 0, 180, 8, 8, 0, 170, 8, 8, 10, 170, 8, 8};//子弹截图
    SDL_Rect cut3 = {20, 203, 90, 90};//按键截图
    SDL_Rect cut4 = {384, 135, 96, 90};//场景方块截图
    SDL_Rect cut5 = {123, 455, 180, 180};//子弹按键截图
    //SDL_Rect cut6 = {690, 310, 20, 20};//子弹爆炸截图
    int score = 0;//分数
};

#endif