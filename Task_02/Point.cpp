#include "Point.h"
#include <cmath>

const double pi = acos(-1);

Point::Point(double x, double y, double z): x(x), y(y), z(z){}
Point operator + ( Point a,  Point b){ return Point(a.x + b.x, a.y + b.y, a.z + b.z); }
Point operator - ( Point a,  Point b){ return Point(a.x - b.x, a.y - b.y, a.z - b.z); }
Point operator * ( Point a, double b){ return Point(a.x * b, a.y * b, a.z * b); }
Point operator / ( Point a, double b){ return Point(a.x / b, a.y / b, a.z / b); }

double Dot( Point a,  Point b){ return a.x*b.x + a.y*b.y + a.z*b.z; }
Point Cross( Point a,  Point b){ return Point(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x); }
double Length( Point a){ return sqrt(Dot(a,a)); }
Point Rotate(Point a, double theta){ // 只对前两维作用的旋转
	return Point(a.x * cos(theta) - a.y * sin(theta), a.x * sin(theta) + a.y * cos(theta), a.z);
}
