#include "Tools.h"

Point getUpView(Point eye, Point towards){
	towards = towards - eye;
	Point t1 = Point(towards.x, towards.y, 0);
	t1 = Rotate(t1, pi/2);
	return Cross(towards, t1);
}
