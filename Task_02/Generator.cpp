#include "Generator.h"
#include <cstring>
#include <vector>
#include <utility>
#include <ctime>
#include <cstdlib>
using namespace std;
typedef pair<int, int> pii;

int w[maxn][maxn];
int fa[maxn * maxn];
int find(int x){
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

#define FOR(i, l, r) for(int (i) = (l); (i) <= (r); (i)++)

int randint(int l, int r){
	int del = r - l + 1;
	return l + rand() % del;
}

vector <pii> edges;
void prework(int n, int m){
	srand(time(NULL));
	FOR(i, 1, n * m) fa[i] = i;
	FOR(i, 1, n) FOR(j, 1, m) w[i][j] = fWall;
	for(int i = 2; i <= n; i += 2) 
		for(int j = 2; j <= m; j += 2){
			w[i][j] = fRoad;
			if(i + 2 <= n){
				int u = (i-1) * m + j - 1;
				int v = (i+2-1) * m + j - 1;
				edges.push_back(pii(u, v));
			}
			if(j + 2 <= m){
				int u = (i-1) * m + j - 1;
				int v = (i-1) * m + j + 2 - 1;
				edges.push_back(pii(u, v));
			}
		}
	for(int i = 0; i < edges.size(); i++){
		 int at = randint(i, edges.size()-1);
		 swap(edges[i], edges[at]);
	}
}

void build(int n, int m){
	for(int i = 0; i < edges.size(); i++){
		int fx = find(edges[i].first);
		int fy = find(edges[i].second);
		if(fx != fy){
			int x1 = edges[i].first/m + 1;
			int y1 = edges[i].first%m + 1;
			int x2 = edges[i].second/m + 1;
			int y2 = edges[i].second%m + 1;
			int x = (x1 + x2) >> 1;
			int y = (y1 + y2) >> 1;
			w[x][y] = fRoad;
			fa[fx] = fy;
		}
	}
	int cnt = randint(1, 5);
	for(int i = 1; i <= cnt; i++){
		int x = randint(2, n-1);
		int y = randint(2, m-1);
		w[x][y] = fStart;
	}
	cnt = randint(1, 5);
	for(int i = 1; i <= cnt; i++){
		int x = randint(2, n-1);
		int y = randint(2, m-1);
		w[x][y] = fEnd;
	}
}

void generator(int n, int m){ // 必须保证n, m是奇数
	prework(n, m);
	build(n, m);
}
