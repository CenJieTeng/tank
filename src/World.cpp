#include "tank.h"
#include "tankAI.h"
#include "bom.h"
#include "Play.h"
#include "World.h"

World* World::world()
{
    static World world;;
    return &world;
}

void World::init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    win = SDL_CreateWindow("window", 0, 0, 480, 800, 0);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
}

void World::reset()
{
    for (bom *bom : bomList)
    {
        delete bom;
        bom = NULL;
    }
    bomList.clear();
}

void World::createBom(double x, double y, int dir, char val)
{
    bom *pbom = new bom(x, y, dir, val);
    bomList.push_back(pbom);
}

void World::destroyBom()
{
    bomList.remove_if([](bom *bom){
        return bom->getState() == -1;
    });
}