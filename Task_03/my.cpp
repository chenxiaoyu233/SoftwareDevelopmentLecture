#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;

typedef unsigned char Byte;

#define FOR(i, l, r) for(int (i) = (l); (i) < (r); (i)++)
namespace HAFFMAN{
	const int maxn = 270;
	short tot, root;
	short son[maxn * 2][2]; // 合法的区间为[0, 256], 其中256表示EOF
	int cnt[maxn * 2];
	short length[maxn * 2];
	bool wd[maxn][maxn];

	inline short& lson(short rt){ return son[rt][0]; }
	inline short& rson(short rt){ return son[rt][1]; }
	inline void addByte(Byte x){ cnt[x]++; }
	inline int newNode(){ return ++tot; }

	void init(){
		root = 0; tot = 256;
		FOR(i, 0, 257) lson(i) = rson(i) = -1;
		cnt[256] = 1;
	}
	struct cmp{
		bool operator () (const int &a, const int &b){
			return cnt[a] > cnt[b];
		}
	};
	bool num[maxn*2];
	void dfs(int x, int at){
		if(lson(x) == -1 && rson(x) == -1){ // leaf
			length[x] = at;
		       	memcpy(wd[x], num, sizeof(bool) * at);
			return;
		}
		num[at] = 0, dfs(lson(x), at+1);
		num[at] = 1, dfs(rson(x), at+1);
	}
	void build(){
		priority_queue <int, vector<int>, cmp> q;
		FOR(i, 0, 257) q.push(i);
		while(q.size() > 1){
			int t1 = q.top(); q.pop();
			int t2 = q.top(); q.pop();
			int cur = newNode();
			lson(cur) = t1, rson(cur) = t2;
			cnt[cur] = cnt[t1] + cnt[t2];
			q.push(cur);
		}
		root = tot;
		dfs(root, 0);
	}
};

namespace IO{
	struct Input{
		Byte buffer;
		int cnt;
		FILE *in;
		Input(char *name){ 
			in = fopen(name, "r"); cnt = 8; 
		}
		void reopen(char *name){ 
			freopen(name, "r", in);
			cnt = 8;
		}
		bool hasNext(){
			if(cnt == 8) cnt = (fread(&buffer, 1, 1, in) == 1) ? 0 : 8;
			return cnt != 8;
		}
		bool readBit(){
			if(cnt == 8){ 
				fread(&buffer, 1, 1, in); 
				cnt = 0; 
			}
			return (buffer >> (cnt++)) & 1;
		}
		Byte readByte(){ 
			if(cnt == 8) fread(&buffer, 1, 1, in); cnt = 8;
			return buffer; 
		}
		~Input(){ fclose(in); }
	};
	struct Output{
		int cnt;
		Byte buffer;
		FILE *out;
		Output(char *name){ 
			out = fopen(name, "w"); 
			buffer = cnt = 0;
		}
		void reopen(char *name){ 
			fclose(out);
			out = fopen(name, "w");
			buffer = cnt = 0;
		}
		void putBit(bool s){
			buffer |= s << (cnt++);
			if(cnt == 8){ 
				fwrite(&buffer, 1, 1, out); 
				buffer = cnt = 0; 
			}
		}
		void putByte(Byte s){ fwrite(&s, 1, 1, out); }
		~Output(){ 
			if(cnt != 0){ fwrite(&buffer, 1, 1, out); } // 清空缓冲区
			fclose(out); 
		}
	};
};

void Compress(char *from, char *to){
	IO::Input In(from); 
	IO::Output Out(to);

	HAFFMAN::init();
	while(In.hasNext()) HAFFMAN::addByte(In.readByte());
	HAFFMAN::build(); 

	In.reopen(from);
	fwrite(&(HAFFMAN::cnt), sizeof(int), 256, Out.out);
	while(In.hasNext()) {
		Byte cur = In.readByte();
		FOR(i, 0, HAFFMAN::length[cur]) Out.putBit(HAFFMAN::wd[cur][i]);
	}
	FOR(i, 0, HAFFMAN::length[256]) Out.putBit(HAFFMAN::wd[256][i]);
}
void unCompress(char *from, char *to){
	IO::Input In(from);
	IO::Output Out(to);

	HAFFMAN::init();
	fread(&(HAFFMAN::cnt), sizeof(int), 256, In.in);
	HAFFMAN::build();

	for(short cur = HAFFMAN::root; In.hasNext(); cur = HAFFMAN::son[cur][In.readBit()]){
		if(cur < 256 && cur >= 0) Out.putByte(cur), cur = HAFFMAN::root;
		if(cur == 256) break;
	}
}

int main(int argv, char **args){
	if(strcmp(args[1], "-c") == 0) Compress(args[2], args[3]);
	if(strcmp(args[1], "-u") == 0) unCompress(args[2], args[3]);
	return 0;
};
