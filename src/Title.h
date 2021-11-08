#ifndef _TITLE_H_
#define _TITLE_H_
 
#include "SDL2/SDL_ttf.h"
#include "BaseState.h"

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;

class Title : public BaseState
{
protected:
    virtual BaseState* update() override;
    virtual void enterState() override;
    virtual void exitState() override;

private:
    SDL_Window *win;//窗口
    SDL_Renderer *renderer;//渲染器
    SDL_Texture *tex;
    SDL_Texture *bgTex;
    TTF_Font *font;
};

#endif