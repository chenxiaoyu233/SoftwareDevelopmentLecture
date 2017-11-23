#include <GLUT/GLUT.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>
#include "solver.h"
#include "Generator.h"
using namespace std;

#define FOR(i, l, r) for(int (i) = (l); (i) <= (r); (i)++)
#define draw(TYPE, OBJ, NUM) do{ \
	glBegin(TYPE); \
	FOR(i, 0, NUM) glVertex2fv(OBJ[i]); \
	glEnd(); \
}while(0)
GLfloat winW, winH;
GLfloat initW = 1000.0, initH = 1000.0;
GLint state; // 0 static, 1 move
const int N = 101, M = 101;

struct Point{
	GLdouble x,y,z;
	Point(GLdouble x = 0.0f, GLdouble y = 0.0f, GLdouble z = 0.0f):
		x(x), y(y), z(z){}
	friend Point operator + (const Point &a, const Point &b){
		return Point(a.x + b.x, a.y + b.y, a.z + b.z);
	}
	friend Point operator - (const Point &a, const Point &b){
		return Point(a.x - b.x, a.y - b.y, a.z - b.z);
	}
	friend Point operator * (const Point &a, GLdouble b){
		return Point(a.x * b, a.y * b, a.z * b);
	}
	friend Point operator / (const Point &a, GLdouble b){
		return Point(a.x / b, a.y / b, a.z / b);
	}
};
GLdouble Dot(const Point &a, const Point &b){
	return a.x*b.x + a.y*b.y + a.z*b.z;
}
Point Cross(const Point &a, const Point &b){
	return Point(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}
GLdouble Length(const Point &a){
	return sqrt(Dot(a,a));
}

Point lastP, nowP;
Point RoDir;
GLdouble RoAngle;
int bottonFlag;
int moveFlag;
void ClacPos(GLdouble x, GLdouble y, Point &p){
	if(x < 0) x = 0;
	if(y < 0) y = 0;
	if(x > initW) x = initW;
	if(y > initH) y = initH;
	GLdouble dx = x - (initW/2), dy = (initH/2) - y;
	dx /= initW/2, dy /= initH/2;
	GLdouble dz = sqrt(2.0 - dx * dx - dy * dy);
	p = Point(dx, dy, dz);
}
void mouseButton(int botton, int state, int x, int y){
	switch(state){
		case GLUT_DOWN :
			bottonFlag = 1;
			ClacPos(x, y, lastP);
			break;
		case GLUT_UP :
			bottonFlag = 0;
			break;
	}
}
const GLdouble pi = acos(-1);
void mouseMotion(int x,int y){
	if(!bottonFlag) {
		moveFlag = 0;
		return;
	} moveFlag = 1;
	ClacPos(x, y, nowP);
	RoDir = Cross(lastP, nowP);
	RoAngle = acos(Dot(lastP, nowP)/Length(lastP)/Length(nowP));
	RoAngle = RoAngle / pi * 180;
	lastP = nowP;
	if(RoDir.x == 0 && RoDir.y == 0 && RoDir.z == 0) moveFlag = 0;
	cerr << RoAngle << " " << RoDir.x << " " << RoDir.y << " " << RoDir.z << endl;
}
GLint kd;
GLfloat curAngle;
void keyboard(unsigned char key, int x, int y){
	if(kd != -1) return;
	switch(key){
		case 'x': generator(N, M);
		default : kd = -1;
	}
}
void init_axis(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(0.6f, 0.6f, 0.6f);
}
GLfloat tmp[4][4] = {
	{1.0, 0.0, 0.0, 0.0},
	{0.0, 1.0, 0.0, 0.0},
	{0.0, 0.0, 1.0, 0.0},
	{0.0, 0.0, 0.0, 1.0}
};

void mydisplay(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	init_axis();

	if(moveFlag && bottonFlag){
		glPushMatrix();
		glLoadIdentity();
		glRotatef(RoAngle, RoDir.x, RoDir.y, RoDir.z);
		glMultMatrixf((GLfloat*)tmp);
		glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat *)tmp);
		moveFlag = 0;
		cerr << 1 << endl;
		glPopMatrix();
	}
	glMultMatrixf((GLfloat*)tmp);


	FOR(i, 1, N) FOR(j, 1, M) {
		float dx = 2.0/N, dy = 2.0/M;
		float dh = 2.0/N;
		Point p[4];
		p[0] = Point(-1 + i * dx, -1 + j * dy, 0);
		p[1] = Point(p[0].x - dx, p[0].y, 0);
		p[2] = Point(p[0].x - dx, p[0].y - dy, 0);
		p[3] = Point(p[0].x, p[0].y - dy, 0);
		if(w[i][j] == fRoad) glColor3f(0, 1.0, 0.0);
		if(w[i][j] == fStart) glColor3f(1.0 , 0.0, 0.0);
		if(w[i][j] == fEnd) glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_POLYGON);
		FOR(i, 0, 3) {
			glVertex3f(p[i].x, p[i].y, 0);
		}
		glEnd();
		if(w[i][j] == fWall){
			glColor3f(1.0, 1.0, 0.0);
			glBegin(GL_POLYGON);
			FOR(i, 0, 3) {
				glVertex3f(p[i].x, p[i].y, dh);
			}
			glEnd();
			glColor3f(0, 1.0, 1.0);
			FOR(i, 0, 3){
				int nx = (i + 1) % 4;
				glBegin(GL_POLYGON);
				glVertex3f(p[i].x, p[i].y, 0);
				glVertex3f(p[nx].x, p[nx].y, 0);
				glVertex3f(p[nx].x, p[nx].y, dh);
				glVertex3f(p[i].x, p[i].y, dh);
				glEnd();
			}
		}
	}
	glFlush();
	glutSwapBuffers();
}

void init(){
	glClearColor(0.3, 0.3, 0.3, 0.0);
	glClearDepth(10.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthRange (-10.0f, 10.0f);
	kd = -1;
}

void myReshape(int w,int h){
	glViewport(0, 0, w, h);
	glLoadIdentity();
	glScalef(0.6f, 0.6f, 0.6f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w <= h)
		gluOrtho2D(-1.0, 1.0, -1.0 * (GLfloat)h/w, 1.0 * (GLfloat)h/w);
	else 
		gluOrtho2D(-1.0 * (GLfloat)w/h, 1.0 * (GLfloat)w/h, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void openGLInit(){
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(initW, initH);
	glutCreateWindow("task_02");
	glutReshapeFunc(myReshape);
	glutMouseFunc(&mouseButton);
	glutMotionFunc(&mouseMotion);
	glutKeyboardFunc(&keyboard);
	init();
	glutDisplayFunc(&mydisplay);
	glutIdleFunc(&mydisplay);
	glutMainLoop();
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	generator(N, M);
	openGLInit();
	return 0;
}

