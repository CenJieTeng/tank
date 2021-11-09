#include <vector>
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

    double fatten = 0.1;
    std::vector<bool> periodic({true, true});
    std::vector<double> boxSize({1000, 1000});
    int AABBMaxNum = 1000;
    tree = new aabb::Tree(2, fatten, periodic, boxSize, AABBMaxNum, false);
}

void World::reset()
{
    for (bom *bom : bomList)
    {
        delete bom;
        bom = NULL;
    }
    bomList.clear();

    tree->removeAll();
    for (int i = 0; i < 100; i++)
    {
        auto rect = stageBox[i];
        if (i < 93)
        {
            rect.x -= 6;
            rect.y -= 6;
        }
        std::vector<double> lowerBound({(double)rect.x, (double)rect.y});
        std::vector<double> upperBound({(double)(rect.x + rect.w), (double)(rect.y + rect.h)});
        tree->insertParticle(i, lowerBound, upperBound);
    }
}

void World::insertAABB(AABBKey key, std::vector<double> &lowerBound, std::vector<double> &upperBound)
{
    tree->insertParticle(key, lowerBound, upperBound);
}

void World::updateAABB(AABBKey key, std::vector<double> &lowerBound, std::vector<double> &upperBound)
{
    tree->updateParticle(key, lowerBound, upperBound, true);
}

void World::removeAABB(AABBKey key)
{
    tree->removeParticle(key);
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