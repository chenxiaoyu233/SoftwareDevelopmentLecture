#ifndef GENERATOR_H_
#define GENERATOR_H_

const int maxn = 1005;
enum{
	fStart, fEnd, fWall, fRoad
} mazeFlag;

extern int w[maxn][maxn];
extern int n, m;

void generator(int n, int m);
#endif
