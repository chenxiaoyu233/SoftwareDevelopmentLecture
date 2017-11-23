#include "solver.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

int dis[maxn][maxn];
pii pre[maxn][maxn];
queue <pii> q;
const int oo = 0x3f3f3f3f;
#define FOR(i, l, r) for(int (i) = (l); (i) <= (r); (i)++)

void preWork(int w[maxn][maxn], int n, int m){
	while(!q.empty()) q.pop();
	memset(dis, 0x3f, sizeof(dis));
	FOR(i, 1, n) FOR(j, 1, m){
		if(w[i][j] == fStart) {
			q.push(pii(i, j));
			dis[i][j] = 0;
		}
	}
}
#define X first
#define Y second
void print_ans(int w[maxn][maxn], pii ed, vector <pii> &ans){
	pii tmp = ed; ans.clear();
	while(w[tmp.X][tmp.Y] != fStart){
		ans.push_back(tmp);
		tmp = pre[tmp.X][tmp.Y];
	}
	ans.push_back(tmp);
	reverse(ans.begin(), ans.end());
}
int dirx[] = {0, 0, 1, -1};
int diry[] = {1, -1, 0, 0};
void bfs(int w[maxn][maxn], int n, int m, vector <pii> &ans){
	while(!q.empty()){
		pii tt = q.front(); q.pop();
		if(w[tt.X][tt.Y] == fEnd){
			print_ans(w, tt, ans); return;
		}
		FOR(i, 0, 3){
			int x1 = tt.X + dirx[i], y1 = tt.Y + diry[i];
			if(x1 < 1 || y1 < 1 || x1 > n || y1 > m) continue;
			if(w[x1][y1] == fWall) continue;
			if(dis[x1][y1] > dis[tt.X][tt.Y] + 1){
				dis[x1][y1] = dis[tt.X][tt.Y] + 1;
				pre[x1][y1] = tt;
				q.push(pii(x1, y1));
			}
		}
	}
}
#undef X
#undef Y

void solver(int w[maxn][maxn], int n, int m, vector <pii> &ans){
	preWork(w, n, m);
	bfs(w, n, m, ans);
}
