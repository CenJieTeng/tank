#ifndef _TANKAI_
#define _TANKAI_
#include"tank.h"
#include"bom.h"

class SDL_Rect;
class tankAI : public tank
{
public:
	void AI(double elasped);

private:
	void sportAI(double elasped);
};
#endif