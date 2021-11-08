#ifndef _BOM_
#define _BOM_

class SDL_Texture;

class bom
{
public:
	bom(double x, double y, int dir, char val);
	int getX(){return x;}
	int getY(){return y;}
	char GetChar(){return val;}
	int getDir(){return dir;}
	int getState(){return state;}
	void setX(int i){ x = i; }
	void setY(int i){ y = i; }
	int getW() { return w; };
	int getH() { return h; };
	void sport();

private:
	void collision();

private:
	int x;
	int y;
	int w;
	int h;
	char val = 'b';
	int dir;
	int speed = 5;
	int state = 1;
};
#endif