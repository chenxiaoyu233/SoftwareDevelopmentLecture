#include "Automaton.h"

void keyboard(unsigned char key, int x, int y){ 
	switch(key){
		case 'L': 
			if(!isLight){
				glEnable(GL_LIGHTING);
				isLight = 1;
			} else {
				glDisable(GL_LIGHTING);
				isLight = 0;
			}
			break;
		case 'x':
			generator(N, M);
			Me.initPosition();
			ans.clear();
			break;
		case 'h':
			solver(w, N, M, ans);
			break;
		case 'w': 
			Me.move(0, 1);
			break;
		case 's':
			Me.move(0, -1);
			break;
		case 'a':
			Me.move(-1, 0);
			break;
		case 'd':
			Me.move(1, 0);
			break;
		case 'i':
			phi += pi/180;
			break;
		case 'k':
			phi -= pi/180;
			break;
		case 'j':
			theta += pi/180;
			break;
		case 'l':
			theta -= pi/180;
			break;
	}
}
void mouseButton(int botton, int state, int x, int y){ 
	if(botton == GLUT_LEFT_BUTTON && state == GLUT_DOWN)  zoom++;
	if(botton == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) zoom--;
}
void mouseMotion(int x,int y){ 
	Point cur(x, winH - y, 0);
	theta -= (cur.x - LMP.x) * pi / 180;
	phi -= (cur.y - LMP.y) * pi / 180;
	LMP = cur;
}
