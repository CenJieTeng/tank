#ifndef _TANK_
#define _TANK_
class tank
{
public:
	tank();
	~tank();
	void sport();
	void deDeviation();
	void create();
	int getX();
	int getY();
	void setX(double );
	void setY(double );
	int getH();
	int getW();
	int getDir();
	int getNum();
	char GetChar();
	void setDir(int );
	void setNum(int );
	void touchScreen();
	void bom1Sport();
	void beHurt();
	bool isDead();
	void handleInput();
	void shoot();

public:
	static int w, h;

protected:
	double x = 0;
	double y = 0;
	int dir = 0;
	int speed = 2;
	char val = 't';
	char bomVal = 'b';
	bool dead = false;
	unsigned lastTick = 0;
};
#endif