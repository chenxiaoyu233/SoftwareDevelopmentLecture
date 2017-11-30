#include "Automaton.h"
#include "Tools.h"

void myReshape(int w,int h){
	glMatrixMode(GL_MODELVIEW);
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

float c[4][3] = {
	{1.0, 0.5, 0.5},
	{0.0, 1.0, 0.4},
	{0.2, 0.4, 1.0},
	{0.2, 0.1, 0.5}
};

void drawMaze(){ 
	FOR(i, 1, N) FOR(j, 1, M) {
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
			FOR(i, 0, 3){
				glColor3fv(c[i]);
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
}

void drawAns(){
	if(ans.empty()) return;
	glColor3f(1.0, 0, 0.0);
	glLineWidth(10);
	glBegin(GL_LINES);
	Point last = Point(-1 + ans[0].first * dx - 0.5 * dx, -1 + ans[0].second * dy - 0.5 * dy, 0.1 * dx);
	FOR(i, 1, (int)ans.size()-1){
		Point cur = Point(-1 + ans[i].first * dx - 0.5 * dx, -1 + ans[i].second * dy - 0.5 * dy, 0.1 * dx);
		glVertex3f(last.x, last.y, last.z);
		glVertex3f(cur.x, cur.y, cur.z);
		last = cur;
	}
	glEnd();
	glLineWidth(1);
}

void LookAt(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	eye = Me.getPosition();
	towards = Point(cos(phi) * cos(theta), cos(phi) * sin(theta), sin(phi)) + eye;
	upView = getUpView(eye, towards);
	gluLookAt(eye.x, eye.y, eye.z, towards.x, towards.y, towards.z, upView.x, upView.y, upView.z);
	//cerr << (towards-eye).x << " " << (towards-eye).y << " " << (towards-eye).z << endl;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(zoom, 1, 0.1* dx, 10*dx);
	//glOrtho(-dx, dx, -dy, dy, -2*dx, 2*dx);
}

void mydisplay(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);


	Me.setLight();
	LookAt();
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	drawMaze();
	drawAns();

	glFlush();
	glutSwapBuffers();
}

