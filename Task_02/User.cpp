#include "Automaton.h"

void keyboard(unsigned char key, int x, int y){ 
	towards = Point(cos(phi) * cos(theta), cos(phi) * sin(theta), 0);
       	towards = towards / Length(towards) * 0.1 * dx;
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
			Me.move(towards.x, towards.y);
			break;
		case 's':
			towards = towards * -1;
			Me.move(towards.x, towards.y);
			break;
		case 'a':
			towards = Rotate(towards, pi/2);
			Me.move(towards.x, towards.y);
			break;
		case 'd':
			towards = Rotate(towards, -pi/2);
			Me.move(towards.x, towards.y);
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
		case 'c':
			saveGame();
			break;
		case 'v': 
			loadGame();
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
