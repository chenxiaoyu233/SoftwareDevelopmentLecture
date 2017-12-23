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
	const int _50MB_ = 50000000;
	struct FastInput{
		size_t cnt, total;
		Byte *buffer;
		size_t bfSize;
		FILE *in;
		FastInput(const char *name, size_t bfSize):bfSize(bfSize){
			in = fopen(name, "rb");
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
		inline int readInt(){
			int ans = 0;
			fread(&ans, sizeof(int), 1, in);
			return ans;
		}
		inline void reopen(const char *name){ 
			freopen(name, "rb", in); 
			total = cnt = 0;
		}
		size_t getSize(const char *name){
			FILE *file = fopen(name, "rb");
			fseek(file, 0, SEEK_END);
			size_t size = ftell(file);
			fclose(file);
			return size;
		}
		~FastInput(){ 
			delete[] buffer;
			fclose(in); 
		}
	};
	// 超神输出
	struct FastOutput{
		size_t cnt, total;
		Byte *buffer;
		size_t bfSize;
		FILE *out;
		FastOutput(const char *name, size_t bfSize):bfSize(bfSize){
			out = fopen(name, "wb");
			buffer = new Byte[bfSize];
			memset(buffer, 0, sizeof(Byte) * bfSize);
			total = bfSize << 3, cnt = 0;
		}
		inline void reopen(const char *name){
			freopen(name, "wb", out);
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
		inline void putInt(int x){
			fwrite(&x, sizeof(int), 1, out);
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
struct Bar{
	int flag;
	void init(){
		flag = 0;
	}
	void clear(size_t size){
		printf("[");
		for(int i = 1; i <= 100; i++) printf(" ");
		printf("] %10d / %-10lu 0.0000%%", 0, size);
	}
	void print(size_t cur, size_t size){
		if(!flag) clear(size);
		flag = 1;
		for(int i = 1; i <= 150; i++) printf("\b");
		//cerr << endl;
		printf("[");
		int rat = (double)cur/size * 100 + 0.5;
		for(int i = 1; i <= rat; i++) printf("#");
		for(int i = 1, del = 100 - rat; i <= del; i++) printf(" ");
		printf("] %10lu / %-10lu %5.2f%%", cur, size, (double)cur/size*100);
	}
};


void Compress(const char *from, IO::FastOutput &Out){
	IO::FastInput In(from, IO::_50MB_); 
	//IO::FastOutput Out(to, IO::_50MB_);
	size_t size = In.getSize(from);
	size_t new_size = 0;
	Bar bar; 

	puts("HaffMan Tree initial...");
	HAFFMAN::init();
	puts("Couting words ..."); bar.init();
	size_t now = 0;
	while(In.hasNext()) {
		HAFFMAN::addByte(In.readByte());
		++now;
		if(now % 1000000 == 0) bar.print(now, size);
	} bar.print(size, size);
	puts(" finish ...");
	printf("building HaffMan Tree ...");
	HAFFMAN::build(); 
	puts(" finish ...");
	printf("writting HaffMan Tree ...");
	In.reopen(from);
	//fwrite(&(HAFFMAN::cnt), sizeof(int), 256, Out.out);
	for(int i = 0; i < 256; i++){
		for(int j = 0; j < 32; j++)
			Out.putBit((HAFFMAN::cnt[i]>>j) & 1);
	}
	new_size += 256 * 4 * 8;
	puts(" finish ...");

	puts("Compressing ...");
	bar.init(); now = 0;
	while(In.hasNext()) {
		Byte cur = In.readByte();
		FOR(i, 0, HAFFMAN::length[cur]) Out.putBit(HAFFMAN::wd[cur][i]);
		new_size += HAFFMAN::length[cur];
		++now;
		if(now % 1000000 == 0) bar.print(now, size);
	} bar.print(size, size);
	puts(" finish ...");
	FOR(i, 0, HAFFMAN::length[256]) Out.putBit(HAFFMAN::wd[256][i]);
	new_size += HAFFMAN::length[256];
	printf("the compress ratio is: %5.2f%%\n", (double)new_size/(double)size*100/8);
}

void Decompress(IO::FastInput &In, const char *to){
	//IO::FastInput In(from, IO::_50MB_);
	IO::FastOutput Out(to, IO::_50MB_);
	size_t size = 100000000000/*Out.getSize(to)*/, new_size = 0;

	printf("building HaffMan Tree ...");
	HAFFMAN::init();
	//fread(&(HAFFMAN::cnt), sizeof(int), 256, In.in);
	for(int i = 0; i < 256; i++){
		HAFFMAN::cnt[i] = 0;
		for(int j = 0; j < 32; j++){
			HAFFMAN::cnt[i] |= (In.readBit() << j);
		}
	}
	new_size += 256 * 4;
	HAFFMAN::build();
	puts(" finish ...");

	puts("Decompressing ...");
	Bar bar; bar.init();
	for(short cur = HAFFMAN::root; In.hasNext(); cur = HAFFMAN::son[cur][In.readBit()]){
		if(cur < 256 && cur >= 0) {
			Out.putByte(cur), cur = HAFFMAN::root;
			new_size++;
		};
		if(cur == 256) break;
		if(new_size % 1000000 == 0) bar.print(new_size, size);
	}bar.print(size, size);
	puts(" finish ...");
}

#include <experimental/filesystem>
using namespace std::experimental::filesystem;

void CompressDIR(char *from, char *to){
	IO::FastOutput Out(to, IO::_50MB_);
	int cnt = 0;
	for(auto &p: directory_iterator(path(from))) {
		if(is_directory(status(p))) cnt++;
	} cnt++;
	fwrite(&cnt,sizeof(int), 1, Out.out);
	int len = strlen(from);
	fwrite(&len, sizeof(int), 1, Out.out);
	fwrite(from, sizeof(char), len, Out.out);
	for(auto &p: directory_iterator(path(from))) {
		if(is_directory(status(p))){
			int len = strlen(p.path().c_str());
			fwrite(&len, sizeof(int), 1, Out.out);
			for(int i = 0; i < len; i++){
				char ch = p.path().c_str()[i];
				fwrite(&ch, sizeof(char), 1, Out.out);
			}
		}
	}

	cnt = 0;
	for(auto &p: directory_iterator(path(from))) {
		if(is_regular_file(status(p))) cnt++;
	}
	fwrite(&cnt,sizeof(int), 1, Out.out);
	for(auto &p: directory_iterator(path(from))){
		if(is_regular_file(status(p))) {
			int len = strlen(p.path().c_str());
			fwrite(&len, sizeof(int), 1, Out.out);
			for(int i = 0; i < len; i++){
				char ch = p.path().c_str()[i];
				fwrite(&ch, sizeof(char), 1, Out.out);
			}
		}
	}
	for(auto &p: directory_iterator(path(from))){
		if(is_regular_file(status(p))) {
			printf("Compress %s\n", p.path().c_str());
			Compress(p.path().c_str(), Out);
		}
	}
}

void DecompressDIR(char *from, char *to){
	IO::FastInput In(from, IO::_50MB_);
	int cnt = 0; fread(&cnt, sizeof(int), 1, In.in);
	create_directory(to);
	for(int i = 0, len = 0; i < cnt; i++){
		fread(&len, sizeof(int), 1, In.in);
		char *ch = new char[len];
		fread(ch, sizeof(char), len, In.in);
		string s(to); s = s + string(ch+1);
		create_directory(path(s.c_str()));
		delete[] ch;
	}
	cnt = 0; fread(&cnt, sizeof(int), 1, In.in);
	vector <string> vec; vec.clear();
	for(int i = 0, len = 0; i < cnt; i++){
		fread(&len, sizeof(int), 1, In.in);
		char *ch = new char[len+1];
		fread(ch, sizeof(char), len, In.in);
		ch[len] = '\0';
		string s(to); s = s + string(ch+1);
		vec.push_back(s);
		delete[] ch;
	}
	for(int i = 0, len = 0; i < vec.size(); i++){
		char *ch = new char[vec[i].length() + 1];
		for(int j = 0; j < vec[i].length(); j++) ch[j] = vec[i][j];
		ch[vec[i].length()] = '\0';
		printf("%s\n", ch);
		Decompress(In, ch);
		delete[] ch;
	}
}

#include <bitset>
#include <cstdlib>
namespace LZ77{
	int endFlag;
	const int oo = 0x3f3f3f3f;
	int upperLog(int x){
		int ans;
		for(ans = 1; (1 << ans) < x; ans++);
		return ans;
	}

	template <class BitSet>
	void shift(IO::FastInput &In, BitSet &buffer, int l, int n){
		for(buffer >>= l, endFlag -= l; endFlag <= n && In.hasNext(); endFlag++){
			buffer[endFlag] = In.readBit();
		}
	}

	template <class BitSet>
	int matchLength(BitSet &buffer, int s1, int s2){
		for(int ans = 0; ans + s2 < endFlag; ans++)
			if(buffer[ans+s1] != buffer[ans+s2] || ans + s2 >= endFlag - 1) 
				return ans;
	}

	void BitWrite(IO::FastOutput &Out, int num, int len){
		for(int i = 0; i < len; i++, num >>= 1) {
			Out.putBit(num&1);
		}
	}

#define offset(i) n - Ls + (i)
	typedef pair<int, int> pii;
	template <class BitSet>
	pii Match(BitSet &buffer, int Ls, int n){
		int *next = new int[Ls + 1]; next[1] = 0;
		for(int i = 2, cur = 0; i < Ls; i++){
			while(buffer[offset(i)] != buffer[offset(cur+1)] && cur > 0) cur = next[cur];
			cur += buffer[offset(i)] == buffer[offset(cur+1)];
			cur = cur >= Ls ? Ls-1 : cur;
			next[i] = cur;
		}
		pii ans(-oo, 1);
		for(int i = 1, cur = 0; i <= n; i++){
			while(buffer[i] != buffer[offset(cur+1)] && cur > 0) cur = next[cur];
			cur += buffer[i] == buffer[offset(cur+1)];
			cur = cur >= Ls ? Ls-1 : cur;
			if(i - cur + 1 <= n - Ls && cur > ans.first){
				ans = pii(cur, i - cur + 1);
			}
		}
		delete[] next;
		return ans;
	}

	template <class BitSet>
	void CompressLz77(BitSet buffer, char *from, char *to, int Ls, int n){ // |A| = 2
		int del = 0, cnt = 0;

		endFlag = n+1;
		IO::FastInput In(from, IO::_50MB_);
		IO::FastOutput Out(to, IO::_50MB_);
		buffer.reset();
		int upperLogLs = upperLog(Ls), upperLogNmLs = upperLog(n - Ls);
		Out.putInt(Ls), Out.putInt(n);
		for(int L = Ls; shift(In, buffer, L, n), endFlag > n - Ls + 1; ){
			L = -oo; int p = n - Ls;
			pii cur = Match(buffer, Ls, n);
			L = cur.first + 1, p = cur.second;
			del += upperLogNmLs+upperLogLs+1;
			cnt += L;
			BitWrite(Out, p-1, upperLogNmLs);
			BitWrite(Out, L-1, upperLogLs);
			BitWrite(Out, buffer[n - Ls + L], 1);
		}
	}

	int BitRead(IO::FastInput &In, int len){
		int ans = 0;
		for(int i = 0; i < len; i++){
			ans |= (In.readBit() << i);
		}
		return ans;
	}

	template <class BitSet>
	void DecompressLz77(BitSet buffer, char *from, char *to){
		int cnt = 0;
		IO::FastInput In(from, IO::_50MB_);
		IO::FastOutput Out(to, IO::_50MB_);
		int Ls = In.readInt(), n = In.readInt();
		int upperLogLs = upperLog(Ls), upperLogNmLs = upperLog(n - Ls);
		buffer.reset();
		while(In.hasNext()){
			int p = BitRead(In, upperLogNmLs);
			int L = BitRead(In, upperLogLs);
			cnt += L;
			for(int i = 0; i < L; i++){
				buffer >>= 1;
				buffer[n - Ls] = buffer[p];
			}
			buffer >>= 1;
			buffer[n-Ls] = BitRead(In, 1);
			for(int i = L; i >= 0; i--){
				Out.putBit(buffer[n-Ls-i]);
			}
		}
	}
};

int main(int argv, char **args){
	//CompressDIR("./doc", "bb");
	//DecompressDIR("bb", "./doc1");
	if(argv == 4){
		if(strcmp(args[1], "-c") == 0) {
			IO::FastOutput Out(args[3], IO::_50MB_);
			Compress(args[2], Out);
		}
		if(strcmp(args[1], "-d") == 0) {
			IO::FastInput In(args[2], IO::_50MB_);
			Decompress(In, args[3]);
		}

		if(strcmp(args[1], "-rc") == 0 || strcmp(args[1], "-cr") == 0)
			CompressDIR(args[2], args[3]);
		if(strcmp(args[1], "-rd") == 0 || strcmp(args[1], "-dr") == 0)
			DecompressDIR(args[2], args[3]);

		if(strcmp(args[1], "-fc") == 0 || strcmp(args[1], "-cf") == 0)
			LZ77::CompressLz77(bitset<1024 * 32 * 8 + 1>(), args[2], args[3], 64, 1024 * 8);
		if(strcmp(args[1], "-fd") == 0 || strcmp(args[1], "-df") == 0) 
			LZ77::DecompressLz77(bitset<1024 * 32 * 8 + 1>(), args[2], args[3]);
	}else {
		puts("Uesage:");
		puts("-c file1 file2: 表示将文件1压缩为文件2, 使用哈夫曼编码");
		puts("-d file1 file2: 表示将文件1解压问文件2, 使用哈夫曼编码");
		puts("-fc file1 file2: 表示将文件1压缩为文件2, 使用Lz77算法 (慎用, 很慢, 压缩率有时不理想)");
		puts("-fd file1 file2: 表示将文件1解压问文件2, 使用lz77算法 (慎用, 很慢, 压缩率有时不理想)");
	}
	return 0;
};

// 开O2优化之后跑得飞快
