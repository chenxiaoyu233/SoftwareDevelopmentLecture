#ifndef LIGHT_H_
#define LIGHT_H_
#include "Point.h"
extern int N, M;
extern float dx, dy;
struct Light{
	float x, y;
	Light();
	void setPosition(float x, float y);
	void move(float dx, float dy);
	Point getPosition();
	void initPosition();
	void setLight();
};

#endif
