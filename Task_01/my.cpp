#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned long long ULL;

template <class Key, class Value, class Hash, class Collision>
struct HashTable{
	Value 	  *val;
	Key 	  *key;
	bool 	  *exist;
	bool 	  *isDel;
	ULL 	   length;
	Hash 	   hash;
	Collision  collision;
	ULL 	   cntElement;
	ULL	   cntExist;
	ULL	   factor;

#define ITERATION(operation) \
ULL at = hash(k) % length;\
ULL cur = at;\
collision.init();\
while(exist[cur]){\
	if(key[cur] == k && !isDel[cur]){\
		operation\
	}\
	cur = collision(at) % length;\
}\

	void init(){
		val   = new Value[length];
		key   = new Key[length];
		exist = new bool[length];
		isDel = new bool[length];
		memset(exist, 0, sizeof(bool) * length);
		memset(isDel, 0, sizeof(bool) * length);
		cntElement = cntExist = 0;
	}
	HashTable(ULL length, ULL factor = 3){
		this -> length = length;
		this -> factor = factor;
		init();
	}
	//void resize();
	void insert(Key k, Value v){
		ITERATION( break; )
		key[cur] = k, val[cur] = v, exist[cur] = true;
		++cntElement, ++cntExist;
		resize();
	}
	bool count(Key k){
		ITERATION( return true; )
		return false;
	}
	Value& operator [] (Key k){ // use this after call count.
		ITERATION( break; )
		return val[cur];
	}
	void erase(Key k){
		ITERATION( isDel[cur] = true; break; )
		--cntElement;
		resize();
	}
	void resize(){ // amortize O(1)
		if(cntExist * factor <= length) return;
		ULL newLength = 1;
		while(newLength  <= cntElement) newLength *= factor;
		swap(length, newLength);

		Value *tmpVal   = val;
		bool  *tmpExist = exist;
		Key   *tmpKey   = key;
		bool  *tmpIsDel = isDel;

		init();

		for(int i = 0; i < newLength; i++){
			if(tmpExist[i] && !tmpIsDel[i]){
				insert(tmpKey[i], tmpVal[i]);
			}
		}

		delete[] tmpVal;
		delete[] tmpExist;
		delete[] tmpKey;
		delete[] tmpIsDel;
	}
	~HashTable(){
		delete[] val;
		delete[] exist;
		delete[] key;
		delete[] isDel;
	}
#undef ITERATION
};

struct stringHash{
	static const ULL mod1 = 1000000007;
	static const ULL mod2 = 1000000009;
	ULL operator () (const string &name){
		ULL ans1 = 0, ans2 = 0;
		for(int i = 0; i < name.length(); i++){
			ans1 *= 19260817;
			ans1 += name[i];
			ans1 %= mod1;
		}
		for(int i = 0; i < name.length(); i++){
			ans2 *= 19260817;
			ans2 += name[i];
			ans2 %= mod2;
		}
		return (ans1 << 32) | ans2;
	}
};

struct numberHash{
	static const ULL mod1 = 1000000007;
	static const ULL mod2 = 1000000009;
	ULL operator () (const ULL &nu){
		return ((nu % mod1) << 32) | (nu % mod2);
	}
};

struct Collision1{ // 线性探测再散列
	ULL i;
	void init(){
		i = 1;
	}
	ULL operator () (ULL x){
		ULL ans = x + i;
		i ++;
		return ans;
	}
};

struct Collision2{
	ULL i, sgn;
	void init(){
		sgn = i = 1;
	}
	ULL operator () (ULL x){
		ULL ans = x + sgn * i * i;
		sgn *= -1;
		if(sgn > 0) ++i;
		return ans;
	}
};

struct Collision3{
	static const ULL mod1 = 12255871;
	static const ULL mod2 = 21788233;
	ULL cur;
	bool flag;
	void init(){
		flag = false;
	}
	ULL operator () (ULL x){
		if(flag == false) cur = x;
		flag = true;
		return cur = ((cur % mod1) << 32) | (cur % mod2);
	}
};

struct Person{
	string name, address;
	ULL number;
	Person(string name = "", string address = "", ULL number = 0):
		name(name), address(address), number(number){ }
};

template <class StringToPerson, class NumberToPerson>
void work(StringToPerson *name2per, NumberToPerson *num2per){
	string op;
	ULL num;
	printf("~$ ");
	while(cin >> op){
		if(op == "query"){
			puts("What info would you like to use to query ? [name/number]");
			printf("~$ "); cin >> op;
			if(op == "name"){
				puts("Please input the name.");
				printf("~$ "); cin >> op;
				bool flag = name2per -> count(op);
				if(flag) {
					puts("");
					cout << "   name: " << (*name2per)[op].name << endl;
					cout << "address: " << (*name2per)[op].address << endl;
					cout << " number: " << (*name2per)[op].number << endl;
					puts("");
				} else  puts("This person doesn't exist");
			}else if(op == "number"){
				puts("Please input the number.");
				printf("~$ "); cin >> num;
				bool flag = num2per -> count(num);
				if(flag) {
					puts("");
					cout << "name: " << (*num2per)[num].name << endl;
					cout << "address: " << (*num2per)[num].address << endl;
					cout << "number: " << (*num2per)[num].number << endl;
					puts("");
				} else puts("This person doesn't exist");
			}else {
				puts("invalid input.");
			}
		} else if(op == "add"){
			string name, address; ULL number;
			puts("Please input the info of the person");
			printf("~$    name: "); cin >> name;
			printf("~$ address: "); cin >> address;
			printf("~$  number: "); cin >> number;
			bool flag = name2per -> count(name);
			if(flag){
				puts("This Person is already exist.");
				puts("What would you like to do next? [add/cover]");
				printf("~$ "); cin >> op;
				if(op == "add"){
					while(name2per -> count(name)) name += '*';
					name2per -> insert(name, Person(name, address, number));
					num2per -> insert(number, Person(name, address, number));
				} else if(op == "cover"){
					ULL numTmp = (*name2per)[name].number;
					num2per -> erase(numTmp);
					name2per -> erase(name);
					name2per -> insert(name, Person(name, address, number));
					num2per -> insert(number, Person(name, address, number));
				} else puts("invalid input");
			} else {
				name2per -> insert(name, Person(name, address, number));
				num2per -> insert(number, Person(name, address, number));
			}
		} else if(op == "delete"){
			string name;
			puts("Please input the name of the person");
			printf("~$ "); cin >> name;
			bool flag = name2per -> count(name);
			if(flag){
				ULL numTmp = (*name2per)[name].number;
				name2per -> erase(name);
				num2per -> erase(numTmp);
			} else puts("This person doesn't exist");
		} else if(op == "print"){
			puts("-----------------------------------");
			for(int i = 0; i < num2per -> length; i++){
				if(num2per -> exist[i] && !(num2per -> isDel[i])){
					printf("   name: "); cout << (num2per -> val[i]).name << endl;
					printf("address: "); cout << (num2per -> val[i]).address << endl;
					printf(" number: "); cout << (num2per -> val[i]).number << endl;
					puts("-----------------------------------");
				}
			}
		} else if(op == "save"){
			string name;
			puts("please input the file's name");
			printf("~$"); cin >> name;
			FILE *out = fopen(name.c_str(), "w");
			fprintf(out, "%llu\n", num2per -> length);
			for(int i = 0; i < num2per -> length; i++){
				if(num2per -> exist[i] && !(num2per -> isDel[i])){
					fprintf(out, "%s\n", (num2per -> val[i]).name.c_str());
					fprintf(out, "%s\n", (num2per -> val[i]).address.c_str());
					fprintf(out, "%llu\n", (num2per -> val[i]).number);
				}
			}
			fclose(out);
		} else if(op == "load"){
			string name, address; ULL number;
			puts("please input the file's name");
			printf("~$ "); cin >> name;
			ifstream in(name.c_str(), ios::in);
			ULL len; in >> len;
			delete name2per; delete num2per;
			name2per = new StringToPerson(len);
			num2per = new NumberToPerson(len);

			while(in >> name >> address >> number){
				name2per -> insert(name, Person(name, address, number));
				num2per -> insert(number, Person(name, address, number));
			}
			in.close();
		} else if(op == "exit"){
			delete name2per;
			delete num2per;
			break;
		} else if(op == "help"){
			puts("");
			puts(" query: use name/number to query a person");
			puts("   add: add a person");
			puts("delete: del a person with name");
			puts(" print: print the whole table");
			puts("  save: save the current table to flie");
			puts("  load: load table from file");
			puts("  exit: exit the program");
			puts("");
		}

		printf("~$ ");
	}
}

void mainLoop(){
	string op;
	ULL kind, size;
	puts("Welcome to use this app to help you remember the person you know.");
	puts("-----------------------------");
	puts("type \"init\" to use this app");
	puts("-----------------------------");
	printf("~$ ");
	while(cin >> op){
		if(op == "init"){
			puts("What's method you'd like to deal with collision ?");
			puts("-1- 线性探测再散列");
			puts("-2- 二次探测再散列");
			puts("-3- 再哈希法");
			printf("~$ "); cin >> kind;

			puts("What's the possible size of the table ?");
			printf("~$ "); cin >> size;

			puts("Initial workspace.");
			puts("Finish.");

#define WORK( Method ) \
do{\
	HashTable <string, Person, stringHash, Method> *t1\
		= new HashTable<string, Person, stringHash, Method>(size * 2);\
	HashTable <ULL, Person, numberHash, Method> *t2\
		= new HashTable<ULL, Person, numberHash, Method>(size * 2);\
	work(t1, t2);\
	return;\
}while(0)
			if(kind == 1) WORK( Collision1 );
			else if(kind == 2) WORK( Collision2 );
			else WORK( Collision3 );
		} else if(op == "exit") {
			break;
		}
		printf("~$ ");
	}
}
int main(){
	mainLoop();
	return 0;
}
