#include "Light.h"
#include <GLUT/GLUT.h>
#include "Generator.h"
#include <cmath>

float LightAmbient[] = {0.1, 0.1, 0.1, 1.0};
float LightDiffuse[] = {1.0, 1.0, 1.0, 1.0};
float LightPosition[] = {0.0, 0.0, 0.0, 1.0};

Light::Light(){ x = y = 1; }
void Light::setPosition(float x, float y){
	if(x < -1 || x > 1 || y < -1 || y > 1) return;
	this -> x = x, this -> y = y;
}

extern float dx, dy;
void Light::move(float delx, float dely){
	if(x + delx < -1 || x + delx > 1) return;
	if(y + dely < -1 || y + dely > 1) return;
	int wx = ceil((1.0 + x + delx)/dx);
	int wy = ceil((1.0 + y + dely)/dy);
	if(w[wx][wy] == fWall) return;
	int Lx = ceil((1.0 + x) / dx);
	int Ly = ceil((1.0 + y) / dy);
	if(Lx != wx || Ly != wy){
		w[wx][wy] = fStart;
		w[Lx][Ly] = fRoad;
	}
	x += delx, y += dely;
}

Point Light::getPosition(){
	return Point(x, y, 0.2);
}

void Light::setLight(){
	glDisable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	LightPosition[0] = x;
	LightPosition[1] = y;
	LightPosition[2] = 0.2;
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
	glEnable(GL_LIGHT1);
}

void Light::initPosition(){
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= M; j++){
			if(w[i][j] == fStart) {
				x = -1 + i*dx - 0.5 * dx, y = -1 + j*dy - 0.5 * dy;
				return;
			}
		}
}
