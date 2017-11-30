#include "Light.h"
#include <GLUT/GLUT.h>
#include "Generator.h"
float LightAmbient[] = {0.1, 0.1, 0.1, 1.0};
float LightDiffuse[] = {1.0, 1.0, 1.0, 1.0};
float LightPosition[] = {0.0, 0.0, 0.0, 1.0};

Light::Light(){ x = y = 1; }
void Light::setPosition(int x, int y){
	if(x < 1 || x > N || y < 1 || y > M) return;
	this -> x = x, this -> y = y;
}
void Light::move(int dx, int dy){
	if(x + dx < 1 || x + dx > N) return;
	if(y + dy < 1 || y + dy > M) return;
	if(w[x + dx][y + dy] != fRoad) return;
	x += dx, y += dy;
}

Point Light::getPosition(){
	return Point(-1 + x * dx - 0.5 * dx, -1 + y * dy - 0.5 * dy, 0.2);
}

void Light::setLight(){
	glDisable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	LightPosition[0] = -1 + x * dx - 0.5 * dx;
	LightPosition[1] = -1 + y * dy - 0.5 * dy;
	LightPosition[2] = 0.2;
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
	glEnable(GL_LIGHT1);
}

void Light::initPosition(){
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= M; j++){
			if(w[i][j] == fStart) {
				x = i, y = j;
				return;
			}
		}
}
