#ifndef AUTOMATON_H_
#define AUTOMATON_H_
#include <GLUT/GLUT.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>
#include <vector>
#include "solver.h"
#include "Generator.h"
#include "Point.h"
#include "Light.h"
using namespace std;

void openGLInit();
void keyboard(unsigned char key, int x, int y);
void mouseButton(int botton, int state, int x, int y);
void mouseMotion(int x,int y);
void myReshape(int w,int h);
void mydisplay();
void saveGame();
void loadGame();

extern float winW, winH;
extern float initW , initH;
extern int state; // 0 static, 1 move
extern int N, M;
extern float dx, dy, dh;
extern vector <pii> ans;
extern Point eye, towards, upView;
extern Light Me;
extern int isLight;
extern int zoom;
extern Point LMP;
extern float theta, phi;

#define FOR(i, l, r) for(int (i) = (l); (i) <= (r); (i)++)
#define draw(TYPE, OBJ, NUM) do{ \
	glBegin(TYPE); \
	FOR(i, 0, NUM) glVertex2fv(OBJ[i]); \
	glEnd(); \
}while(0)

#endif
