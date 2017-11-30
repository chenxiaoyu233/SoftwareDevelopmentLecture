#include "Automaton.h"

GLfloat winW, winH;
GLfloat initW = 1000.0, initH = 1000.0;
GLint state; // 0 static, 1 move
int N = 21, M = 21;
float dx = 2.0/N, dy = 2.0/M, dh = 2.0/N * 3;
vector <pii> ans;
Point eye, towards, upView;
Light Me;
int isLight;
int zoom;
Point LMP;
float theta, phi;

char s[1005];
void printFile(string name){
	FILE * in = fopen(name.c_str(), "r");
	while(fgets(s, 1000, in) != NULL){
		printf("%s", s);
	}
	fclose(in);
}

void helpFunc() {
#ifdef __APPLE__
	system("clear");
#else
	system("cls");
#endif
	printFile("helpFile");
}

void init(){
	glClearColor(0.3, 0.3, 0.3, 0.0);
	glClearDepth(10.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthRange (-10.0f, 10.0f);
	ans.clear();
	zoom = 100;
	helpFunc();
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
	glutPassiveMotionFunc(&mouseMotion);
	init();
	glutDisplayFunc(&mydisplay);
	glutIdleFunc(&mydisplay);

	glutMainLoop();
}

void Winner(){
	printFile("winFile");
	cout << "按下任意键继续" << endl;
	getchar();
	exit(0);
}
