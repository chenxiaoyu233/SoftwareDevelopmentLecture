#ifndef LIGHT_H_
#define LIGHT_H_
#include "Point.h"
extern const int N, M;
extern float dx, dy;
struct Light{
	int x, y;
	Light();
	void setPosition(int x, int y);
	void move(int dx, int dy);
	Point getPosition();
	void initPosition();
	void setLight();
};

#endif
