#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include "map.hpp"
long long aa=13131,bb=5353,MOD=(long long)(1e9+7),now=1;
int rand()
{
	for(int i=1;i<3;i++)
		now=(now * aa + bb) % MOD;
	return now;
}
class Key{
public:
	int x;
	Key(const Key &other):x(other.x){}	
	Key(int x):x(x){}
	int num()const{
		return x;	
	}
};
class Data{
public:
	int* x;
	Data():x(new int(1)){}
	Data(int p):x(new int(p)){}
	Data(const Data &other):x(new int(*(other.x))){}
	~Data(){
		delete x;
	}
	Data & operator = (const Data &other){
		if(this == &other) return *this;
		*x = *(other.x);
		return *this;	
	}
	int num()const{
		return *x;	
	}
};
struct cmp{
	bool operator ()(const Key &a,const Key &b)const{return a.x > b.x;} 	
};
sjtu::map<Key,Data,cmp> map;
int num = 5000;
void test_insert(){
	puts("Test: insert");
	std::cout<<"empty:"<<map.empty()<<std::endl;
	std::cout<<"size:"<<map.size()<<std::endl;
	int num = 1000;
	for(int i=1;i<=num;i++)
	{
		int tmp(rand() % 10000);
		map[Key(tmp)] = Data(rand());
	}
	for(int i=1;i<=num;i++)
	{
		try{	
			map.at(Key(rand() % 10000)) = Data(rand());	
		}catch(...){}
	}
	for(int i=1;i<=num;i++){
		Key key(rand() % 10000);
		Data data(rand());
		sjtu::pair<sjtu::map<Key,Data,cmp>::iterator,bool> it = map.insert(sjtu::map<Key,Data,cmp>::value_type(key,data));
		if (it.second) std::cout<<(it.first->second).num()<<' ';
		else std::cout<<"0 ";
	}
	puts("");
	for(int i=1;i<=num;i++){
		int tmp(rand() % 10000);
		std::cout<<(map[Key(tmp)]).num()<<' ';
	}
	puts("");
	for(int i=1;i<=num;i++){
		int tmp(rand() % 10000);
		try{
			std::cout<<(map.at(Key(tmp))).num()<<' ';
		}catch(...){}
	}
	puts("");
}
void Print(){
	for(sjtu::map<Key,Data,cmp>::const_iterator it(map.cbegin());it!=map.cend();++it)
		std::cout<<(it->first).num()<<' '<<((*it).second).num()<<' ';
	puts("");
}
void test_erase(){
	puts("Test: erase");
	for(int i=1;i<=100 && !map.empty();i++){
		int p = rand() % map.size();
		sjtu::map<Key,Data,cmp>::iterator it(map.begin());
		while (p--) it++;
		map.erase(it);
	}
	Print();
}
void test_const_at(){
	puts("Test: const_at");
	const sjtu::map<Key,Data,cmp> mm(map);
	for(int i=1;i<=num;i++){
		int tmp(rand() % 10000);
		try{
			std::cout<<(mm.at(Key(tmp))).num()<<' ';
		}catch(...){}
	}
	
	for(int i=1;i<=num;i++){
		int tmp(rand() % 10000);
		try{
			std::cout<<(mm[Key(tmp)]).num()<<' ';
		}catch(...){}
	}
	puts("");
}
void test_count(){
	puts("Test: count");
	const sjtu::map<Key,Data,cmp> mm(map);
	for(int i=1;i<=num;i++){
		int tmp(rand() % 10000);
		try{
			std::cout<<(int)(mm.count(Key(tmp)))<<' ';
		}catch(...){}
	}
	puts("");
}
void test_find(){
	puts("Test: find");
	const sjtu::map<Key,Data,cmp> mm(map);
	for(int i=1;i<=num;i++){
		int tmp(rand() % 10000);
		sjtu::map<Key,Data,cmp>::iterator it(map.find(Key(tmp)));
		if(it == map.end()) std::cout<<"END ";
		else std::cout<<(it->first).num()<<' '<<(it->second).num()<<' ';
	}
	puts("");
	
	for(int i=1;i<=num;i++){
		int tmp(rand() % 10000);
		sjtu::map<Key,Data,cmp>::const_iterator it(mm.find(Key(tmp)));
		if(it == mm.cend()) std::cout<<"END ";
		else std::cout<<(it->first).num()<<' '<<(it->second).num()<<' ';
	}
	puts("");
}
void test_throw(){
	puts("Test: throw");
	sjtu::map<Key,Data,cmp>::iterator it;
	it = map.begin();
	try{
		it--;	
	}catch(...){puts("OK1");}
	try{
		--it;	
	}catch(...){puts("OK2");}
	it = map.end();
	try{
		it++;	
	}catch(...){puts("OK3");}
	try{
		++it;	
	}catch(...){puts("OK4");}
	sjtu::map<Key,Data,cmp> new_map;
	it = new_map.begin();
	try{
		it++;	
	}catch(...){puts("OK5");}
	try{
		++it;	
	}catch(...){puts("OK6");}
}
void test_const_throw(){
	puts("Test: const_throw");
	const sjtu::map<Key,Data,cmp> mm(map);
	sjtu::map<Key,Data,cmp>::const_iterator it;
	it = mm.cbegin();
	try{
		it--;	
	}catch(...){puts("OK7");}
	try{
		--it;	
	}catch(...){puts("OK8");}
	it = map.cend();
	try{
		it++;	
	}catch(...){puts("OK9");}
	try{
		++it;	
	}catch(...){puts("OK10");}
	const sjtu::map<Key,Data,cmp> new_map;
	it = new_map.cbegin();
	try{
		it++;	
	}catch(...){puts("OK11");}
	try{
		++it;	
	}catch(...){puts("OK12");}
}
void test_copy()
{
	puts("Test: copy");
	sjtu::map<Key,Data,cmp> m1(map),m2;
	m2 = map;
	map.clear();
	std::cout<<map.size()<<' '<<map.empty()<<std::endl;
	sjtu::map<Key,Data,cmp>::iterator it1(m1.begin()),it2(m2.begin());
	for(;it1!=m1.end() || it2!=m2.end();it1++,it2++)
	{
		std::cout<<(it1->first).num()<<' '<<(it1->second).num()<<' '<<(it2->first).num()<<' '<<(it2->second).num()<<' ';
	}
	puts("");
}
void test_iterator()
{
	sjtu::map<Key,Data,cmp>::iterator it1 = map.begin();
	for(int i=1;i<=3;i++)
	{
		int tmp = rand() % 5;
		while (tmp--)
		{
			try{
				sjtu::map<Key,Data,cmp>::const_iterator it2(it1++);
				sjtu::map<Key,Data,cmp>::const_iterator it3(++it1);
				sjtu::map<Key,Data,cmp>::iterator it4(it1++);
				sjtu::map<Key,Data,cmp>::iterator it5(++it1);
				std::cout<<(it2->first).num()<<' '<<(it2->second).num()<<std::endl;
				std::cout<<(it3->first).num()<<' '<<(it3->second).num()<<std::endl;
				std::cout<<(it4->first).num()<<' '<<(it4->second).num()<<std::endl;
				std::cout<<((*it5).first).num()<<' '<<((*it5).second).num()<<std::endl;
			}catch(...){}
		}
	}
}
int main(){
	test_insert();
	test_erase();
	test_const_at();
	test_count();
	test_find();
	test_copy();
	test_iterator();
}
