#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_s

#include "BaseState.h"

class SDL_Texture;

class GameOver : public BaseState
{
public:
    virtual BaseState* update(double elasped) override;
    virtual void enterState() override;
    virtual void exitState() override;

private:
    int count_ = 0;
    SDL_Window *win;//窗口
    SDL_Renderer *renderer;//渲染器
    SDL_Texture *tex; //背景
};

#endif