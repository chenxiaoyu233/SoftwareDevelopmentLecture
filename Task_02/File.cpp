#include "Automaton.h"
#include <cstdio>
using namespace std;

void saveGame(){
	FILE *out = fopen("Maze", "w");
	fprintf(out, "%d %d\n", N, M);
	FOR(i, 1, N) {
		FOR(j, 1, M){
			fprintf(out, "%d ", w[i][j]);
		} fprintf(out, "\n");
	}
	fprintf(out, "%f %f\n", Me.x, Me.y);
	fclose(out);
}

void loadGame(){
	FILE *in = fopen("Maze", "r");
	fscanf(in, " %d%d", &N, &M);
	FOR(i, 1, N) FOR(j, 1, M) 
		fscanf(in, " %d", &w[i][j]);
	float x, y;
	fscanf(in, " %f%f", &x, &y);
	Me.setPosition(x, y);
	fclose(in);
}
