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
	//超神读入
	struct FastInput{
		size_t cnt, total;
		Byte *buffer;
		size_t bfSize;
		FILE *in;
		FastInput(char *name, size_t bfSize):bfSize(bfSize){
			in = fopen(name, "r");
			buffer = new Byte[bfSize];
			cnt = total = 0;
		}
		inline bool hasNext(){
			if(cnt == total){ total = fread(buffer, sizeof(Byte), bfSize, in) << 3; cnt = 0; }
			return cnt != total;
		}
		inline bool readBit(){
			if(!hasNext()) return 0;
			size_t cntd8 = cnt >> 3;
			bool ans = buffer[cntd8] >> (cnt - (cntd8 << 3)) & 1; cnt++;
			return ans;
		}
		inline Byte readByte(){
			if(!hasNext()) return 0;
			Byte ans = buffer[cnt >> 3]; cnt += 8;
			return ans;
		}
		inline void reopen(char *name){ 
			freopen(name, "r", in); 
			total = cnt = 0;
		}
		~FastInput(){ 
			delete[] buffer;
			fclose(in); 
		}
	};
	struct FastOutput{
		size_t cnt, total;
		Byte *buffer;
		size_t bfSize;
		FILE *out;
		FastOutput(char *name, size_t bfSize):bfSize(bfSize){
			out = fopen(name, "w");
			buffer = new Byte[bfSize];
			memset(buffer, 0, sizeof(Byte) * bfSize);
			total = bfSize << 3, cnt = 0;
		}
		inline void reopen(char *name){
			freopen(name, "w", out);
			memset(buffer, 0, sizeof(Byte) * bfSize);
			cnt = 0;
		}
		inline void clearBuffer(){
			fwrite(buffer, sizeof(Byte), cnt >> 3, out);
			memset(buffer, 0, sizeof(Byte) * bfSize);
			cnt = 0;
		}
		inline void checkBuffer(){
			if(cnt == (bfSize << 3)) clearBuffer();
		}
		inline void putBit(bool x){
			checkBuffer();
			size_t cntd8 = cnt >> 3;
			buffer[cntd8] |= x << (cnt - (cntd8 << 3));
			cnt ++;
		}
		inline void putByte(Byte x){
			checkBuffer();
			buffer[cnt >> 3] = x;
			cnt += 8;
		}
		~FastOutput(){
			clearBuffer();
			delete[] buffer;
			fclose(out);
		}
	};
};

void Compress(char *from, char *to){
	IO::FastInput In(from, 50000000); 
	IO::FastOutput Out(to, 50000000);

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
	IO::FastInput In(from, 50000000);
	IO::FastOutput Out(to, 50000000);

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
