#ifndef POINT_H_
#define POINT_H_

struct Point{
	double x,y,z;
	Point(double x = 0.0f, double y = 0.0f, double z = 0.0f);
	friend Point operator + ( Point ,  Point );
	friend Point operator - ( Point ,  Point );
	friend Point operator * ( Point , double );
	friend Point operator / ( Point , double );
};
double Dot( Point,  Point);
Point Cross( Point,  Point );
double Length( Point );
Point Rotate( Point , double );

extern const double pi;

#endif
