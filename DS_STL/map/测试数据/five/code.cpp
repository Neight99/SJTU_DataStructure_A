#include<iostream>
#include<map>
#include<ctime>
#include<queue>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include "map.hpp"

using namespace std;

bool check1(){ //insert by []
	int a, b;
	sjtu::map<int, int> Q;
	std::map<int, int> stdQ;	
	for(int i = 1; i <= 50000; i++){
		a = rand(); b = rand();
		if(!Q.count(a)){
			Q[a] = b; stdQ[a] = b;
		}
	}
	sjtu::map<int, int> :: value_type pp;
	for(int i = 1; i <= 50000; i++){
		a = rand(); b = rand();
		if(!Q.count(a)){
			Q.insert(sjtu::map<int, int> :: value_type(a, b));
			stdQ.insert(std::map<int, int> :: value_type(a, b));
		}
	}
	if(Q.size() != stdQ.size()) return 0;
	sjtu::map<int, int>::iterator it;
	std::map<int, int>::iterator stdit;
	stdit = stdQ.begin();
	for(it = Q.begin(); it != Q.end(); it++){
		if(stdit -> first != it -> first) return 0;
		if(stdit -> second != (*it).second) return 0;
		stdit++;
	}
	stdit = --stdQ.end();
	for(it = --Q.end(); it != Q.begin(); it--){
		if(stdit -> first != it -> first) return 0;
		if(stdit -> second != (*it).second) return 0;
		stdit--;
	}
	return 1;
}

bool check2(){//Q.insert
	sjtu::map<int, int> Q;
	sjtu::map<int, int> :: iterator it;
	int num[51];
	for(int i = 1; i <= 50; i++) num[i] =i;
	for(int i = 1; i <= 100; i++) swap(num[rand() % 50 + 1], num[rand() % 50 + 1]);
	for(int i = 1; i <= 50; i++) Q[num[i]] = rand();
	int p = Q[6];
	if(Q.insert(sjtu::map<int, int>::value_type(6, 9)).second) return 0;
	it = Q.insert(sjtu::pair<int, int>(6, 9)).first;
	if(it -> second != Q[6]) return 0;
	
	it = Q.insert(sjtu::map<int, int>::value_type(325, 666)).first;
	if(it -> first != 325 || it -> second != 666) return 0;
	return 1;
}

bool check3(){//find remove 
	sjtu::map<int, int> Q;
	std::map<int, int> stdQ;
	int num[30001];
	num[0] = 0;
	for(int i = 1; i <= 30000; i++) num[i] = num[i - 1] + rand() % 325 + 1; 
	for(int i = 1; i <= 60000; i++) swap(num[rand() % 30000 + 1], num[rand() % 30000 + 1]);
	for(int i = 1; i <= 30000; i++){
		int t = rand();
		stdQ[num[i]] = t; Q[num[i]] = t;
	}
	
	sjtu::map<int, int>::iterator it;
	std::map<int, int>::iterator stdit;
	for(int i = 1; i <= 60000; i++) swap(num[rand() % 30000 + 1], num[rand() % 30000 + 1]);
	for(int i = 1; i <= 10325; i++){
		it = Q.find(num[i]); 
		Q.erase(it);
		stdit = stdQ.find(num[i]); stdQ.erase(stdit);
	}	
	if(Q.size() != stdQ.size()) return 0;
	it = Q.begin();
	for(stdit = stdQ.begin(); stdit != stdQ.end(); stdit++){ 
		if(stdit -> first != it -> first) return 0;
		if(stdit -> second != (*it).second) return 0;
		it++;
	}
	stdit = --stdQ.end();
	for(it = --Q.end(); it != Q.begin(); it--){
		if(stdit -> first != it -> first) return 0;
		if(stdit -> second != (*it).second) return 0;
		stdit--;
	}
	return 1;
}

bool check4(){//const_iterator
	int a, b;
	sjtu::map<int, int> Q;
	std::map<int, int> stdQ;
	for(int i = 1; i <= 30000; i++){
		a = rand(); b = rand();
		if(!Q.count(a)){
			Q[a] = b; stdQ[a] = b;
		}
	}
	sjtu::map<int, int> :: iterator pt;
	pt = Q.begin();
	sjtu::map<int, int> :: const_iterator it(pt), itt;
	std::map<int, int> :: const_iterator stdit;
	stdit = stdQ.cbegin();
	for(it = Q.cbegin(); it != Q.cend(); ++it){
		if(stdit -> first != it -> first) return 0;
		if(stdit -> second != (*it).second) return 0;
		stdit++;
	}
	stdit = --stdQ.cend();
	for(it = --Q.cend(); it != Q.cbegin(); it--){
		if(stdit -> first != it -> first) return 0;
		if(stdit -> second != (*it).second) return 0;
		stdit--;
	}
	itt = --Q.cend();
	if(it == itt) return 0;
	return 1;
}

bool check5(){// insert && remove 
	int a, b;
	sjtu::map<int, int> Q;
	std::map<int, int> stdQ;
	for(int i = 1; i <= 3000; i++){
		a = rand(); b = rand();
		if(!Q.count(a)){
			Q[a] = b; stdQ[a] = b;
		}
	}
	while(!stdQ.empty()){
		if(Q.begin() -> first != stdQ.begin() -> first || Q.begin() -> second != stdQ.begin() -> second) return 0; 
		Q.erase(Q.begin());
		stdQ.erase(stdQ.begin());
	}
	if(Q.begin() != Q.end()) return 0;
	Q.clear(); stdQ.clear();
	sjtu::map<int, int> :: iterator it;
	std::map<int, int> :: iterator stdit;	
	int num[3001], left[3001];
	memset(left, 0, sizeof(left));
	for(int i = 1; i <= 2000; i++) num[i] = i;
	for(int i = 2001; i <= 3000; i++) num[i] = i - 2000;
	for(int i = 1; i <= 6000; i++) swap(num[rand() % 3000 + 1], num[rand() % 3000 + 1]);
	for(int i = 1; i <= 3000; i++){
		if(left[num[i]]){
			if(stdQ.count(num[i])){
				it = Q.find(num[i]); Q.erase(it);
				stdit = stdQ.find(num[i]); stdQ.erase(stdit);
			}
			else cout << "fuck you!" << endl;
		}
		else{
			Q[num[i]] = num[i];
			stdQ[num[i]] = num[i];
			left[num[i]]++;
		}
	}
	if(Q.size() != stdQ.size()) return 0;
	it = Q.begin();
	for(stdit = stdQ.begin(); stdit != stdQ.end(); stdit++){ 
		if(stdit -> first != it -> first) return 0;
		if(stdit -> second != (*it).second) return 0;
		++it;
	}
	stdit = --stdQ.end();
	for(it = --Q.end(); it != Q.begin(); --it){
		if(stdit -> first != it -> first) return 0;
		if(stdit -> second != (*it).second) return 0;
		stdit--;
	}
	return 1;
}

bool check6(){ // copy test
	int a, b;
	sjtu::map<int, int> Q1;
	std::map<int, int> stdQ;
	sjtu::map<int, int> :: value_type pp;
	for(int i = 1; i <= 10000; i++){
		a = rand(); b = rand();
		if(!Q1.count(a)){
			Q1.insert(sjtu::pair<int, int>(a, b));
			stdQ.insert(std::map<int, int> :: value_type(a, b));
		}
	}
	sjtu::map<int, int> Q(Q1);
	if(Q.size() != stdQ.size()) return 0;
	sjtu::map<int, int>::iterator it;
	std::map<int, int>::iterator stdit;
	stdit = stdQ.begin();
	for(it = Q.begin(); it != Q.end(); it++){
		if(stdit -> first != it -> first) return 0;
		if(stdit -> second != (*it).second) return 0;
		stdit++;
	}
	stdit = --stdQ.end();
	for(it = --Q.end(); it != Q.begin(); it--){
		if(stdit -> first != it -> first) return 0;
		if(stdit -> second != (*it).second) return 0;
		stdit--;
	}
	while(!Q.empty()) Q.erase(Q.begin());
	if(Q.size() != 0 || Q.begin() != Q.end()) return 0;
	
	stdit = stdQ.begin();
	for(it = Q1.begin(); it != Q1.end(); it++){
		if(stdit -> first != it -> first) return 0;
		if(stdit -> second != (*it).second) return 0;
		stdit++;
	}
	stdit = --stdQ.end();
	for(it = --Q1.end(); it != Q1.begin(); it--){
		if(stdit -> first != it -> first) return 0;
		if(stdit -> second != (*it).second) return 0;
		stdit--;
	}
	return 1; 
}

bool check7(){ //"=" operator 
	int a, b;
	sjtu::map<int, int> Q1;
	std::map<int, int> stdQ;
	sjtu::map<int, int> :: value_type pp;
	for(int i = 1; i <= 10000; i++){
		a = rand(); b = rand();
		if(!Q1.count(a)){
			Q1.insert(sjtu::map<int, int> :: value_type(a, b));
			stdQ.insert(std::map<int, int> :: value_type(a, b));
		}
	}
	sjtu::map<int, int> Q;
	Q = Q1;
	if(Q.size() != stdQ.size()) return 0;
	sjtu::map<int, int>::iterator it;
	std::map<int, int>::iterator stdit;
	stdit = stdQ.begin();
	for(it = Q.begin(); it != Q.end(); it++){
		if(stdit -> first != it -> first) return 0;
		if(stdit -> second != (*it).second) return 0;
		stdit++;
	}
	stdit = --stdQ.end();
	for(it = --Q.end(); it != Q.begin(); it--){
		if(stdit -> first != it -> first) return 0;
		if(stdit -> second != (*it).second) return 0;
		stdit--;
	}
	while(!Q.empty()) Q.erase(Q.begin());
	if(Q.size() != 0 || Q.begin() != Q.end()) return 0;
	
	stdit = stdQ.begin();
	for(it = Q1.begin(); it != Q1.end(); it++){
		if(stdit -> first != it -> first) return 0;
		if(stdit -> second != (*it).second) return 0;
		stdit++;
	}
	stdit = --stdQ.end();
	for(it = --Q1.end(); it != Q1.begin(); it--){
		if(stdit -> first != it -> first) return 0;
		if(stdit -> second != (*it).second) return 0;
		stdit--;
	}
	return 1; 
}

bool check8(){ //  clear && insert
	int a, b;
	sjtu::map<int, int> Q;
	std::map<int, int> stdQ;
	for(int i = 1; i <= 1000; i++){
		a = rand(); b = rand();
		if(!stdQ.count(a)){
			if(Q.count(a)) return 0;
			stdQ[a] = b; Q[a] = b;
		}
	}
	Q.clear(); stdQ.clear();
	if(Q.begin() != Q.end()) return 0;
	if(Q.size()) return 0;
	for(int i = 1; i <= 1000; i++){
		a = rand(); b = rand();
		if(!stdQ.count(a)){
			if(Q.count(a)) return 0;
			stdQ[a] = b; 
			Q.insert(sjtu::map<int, int> :: value_type(a, b));
		}
	}
	sjtu::map<int, int> :: iterator it;
	std::map<int, int> :: iterator stdit;
	stdit = stdQ.begin();
	for(it = Q.begin(); it != Q.end(); ++it){
		if(stdit -> first != it -> first) return 0;
		if(stdit -> second != (*it).second) return 0;
		stdit++;
	}
	stdit = --stdQ.end();
	for(it = --Q.end(); it != Q.begin(); it--){
		if(stdit -> first != it -> first) return 0;
		if(stdit -> second != (*it).second) return 0;
		stdit--;
	}
	return 1;
}

bool check9(){//just have fun!
	sjtu::map<int, int> Q;
	sjtu::map<int, int> :: iterator fun;
	sjtu::map<int, int> :: const_iterator cfun;
	fun = Q.find(325); cfun = Q.find(325);
	sjtu::map<int, int> P(Q);
	sjtu::map<int, int> O;
	O = Q;
	Q.clear();
	if(Q.size()) return 0;
	Q[3] = 5; Q[6] = 10;
	const sjtu::map<int, int> Q_const(Q);
	sjtu::map<int, int> :: const_iterator cit;
	Q_const.at(3);
	cit = Q_const.find(3);
	O = Q;
	sjtu::map<int, int> :: iterator itQ, itO;
	sjtu::map<int, int> :: const_iterator citQ, citO;
	itQ = Q.end(); itO = O.end();
	citQ = Q.cend(); citO = O.cend();
	if(itQ == itO) return 0; if(citQ == citO) return 0;
	if(!(itQ != itO)) return 0; if(!(citQ != citO)) return 0;
	if(itQ == citO) return 0; if(itO == citQ) return 0;
	if(!(itQ != citO)) return 0; if(!(itO != citQ)) return 0;
	if(!(citQ == itQ)) return 0; if(citQ != itQ) return 0; 
	return 1;
}

class node{
	private:
	int num;
	public:
	node() : num(0) {}
	node(int p) : num(p) {}
	bool operator <(const node &b) const{
		return num < b.num;
	}
	bool operator !=(const node &b) const{
		return num != b.num;
	}
};
bool check10(){//class writen by users
	int a, b;
	sjtu::map<node, int> Q;
	std::map<node, int> stdQ;
	for(int i = 1; i <= 3000; i++){
		a = rand(); b = rand();
		if(!Q.count(a)){
			Q[node(a)] = b; stdQ[node(a)] = b;
		}
	}
	while(!stdQ.empty()){
		if(Q.begin() -> first != stdQ.begin() -> first || Q.begin() -> second != stdQ.begin() -> second) return 0; 
		Q.erase(Q.begin());
		stdQ.erase(stdQ.begin());
	}
	if(Q.begin() != Q.end()) return 0;
	Q.clear(); stdQ.clear();
	sjtu::map<node, int> :: iterator it;
	std::map<node, int> :: iterator stdit;	
	int num[3001], left[3001];
	memset(left, 0, sizeof(left));
	for(int i = 1; i <= 2000; i++) num[i] = i;
	for(int i = 2001; i <= 3000; i++) num[i] = i - 2000;
	for(int i = 1; i <= 6000; i++) swap(num[rand() % 3000 + 1], num[rand() % 3000 + 1]);
	for(int i = 1; i <= 3000; i++){
		if(left[num[i]]){
			if(stdQ.count(node(num[i]))){
				it = Q.find(node(num[i])); Q.erase(it);
				stdit = stdQ.find(node(num[i])); stdQ.erase(stdit);
			}
			else cout << "fuck you!" << endl;
		}
		else{
			Q[node(num[i])] = num[i];
			stdQ[node(num[i])] = num[i];
			left[num[i]]++;
		}
	}
	if(Q.size() != stdQ.size()) return 0;
	it = Q.begin();
	for(stdit = stdQ.begin(); stdit != stdQ.end(); stdit++){ 
		if(stdit -> first != it -> first) return 0;
		if(stdit -> second != (*it).second) return 0;
		++it;
	}
	stdit = --stdQ.end();
	for(it = --Q.end(); it != Q.begin(); --it){
		if(stdit -> first != it -> first) return 0;
		if(stdit -> second != (*it).second) return 0;
		stdit--;
	}
	return 1;	
}

bool check11(){
	sjtu::map<string, int> Q;
	sjtu::map<string, int> :: iterator kit;
	kit = Q.begin();
	Q["aa"] = 5;
	Q["bb"] = 16;
	Q["cc"] = 20;
	Q["lucky"] = 325;
	Q["lwher"] = 666;
	int p = Q.at("lwher");
	if(p != 666) return 0;
	p = Q.at("lucky");
	if(p != 325) return 0;
	int OK = 0;
	try{
		p = Q.at("dd");
	}
	catch(...) {OK++;}
	sjtu::map<string, int> :: iterator it;
	try{
		it = Q.find("ok");
		Q.erase(it);
	}
	catch(...) {OK++;}
	try{
		Q.erase(kit);
	}
	catch(...) {OK++;}
	sjtu::map<string, int> Q2(Q);
	try{
		it = Q2.find("cc");
		Q.erase(it);
	}
	catch(...) {OK++;}
	it = Q.find("cc");
	Q.erase(it);
	try{
		p = Q.at("cc");
	}
	catch(...) {OK++;}	
	const sjtu::map<string, int> Qc(Q);
	try{
		Qc["hehe"];
	}
	catch(...) {OK++;}
	return OK == 6;
}

bool check12(){ // erase(it++)
	sjtu::map<int, int> Q;
	std::map<int, int> stdQ;
	int num[30001];
	num[0] = 0;
	for(int i = 1; i <= 30000; i++) num[i] = num[i - 1] + rand() % 325 + 1; 
	for(int i = 1; i <= 60000; i++) swap(num[rand() % 30000 + 1], num[rand() % 30000 + 1]);
	for(int i = 1; i <= 30000; i++){
		int t = rand();
		stdQ[num[i]] = t; Q[num[i]] = t;
	}
	
	sjtu::map<int, int>::iterator it;
	std::map<int, int>::iterator stdit;
	for(int i = 1; i <= 60000; i++) swap(num[rand() % 30000 + 1], num[rand() % 30000 + 1]);
	for(int i = 1; i <= 10325; i++){
		it = Q.find(num[i]); Q.erase(it++);
		stdit = stdQ.find(num[i]); stdQ.erase(stdit++);
		if(it == Q.end()){
			if(stdit != stdQ.end()) return 0;
		}
		else{
			if(it -> first != stdit -> first) return 0;
		}
	}	
	if(Q.size() != stdQ.size()) return 0;
	it = Q.begin();
	for(stdit = stdQ.begin(); stdit != stdQ.end(); stdit++){ 
		if(stdit -> first != it -> first) return 0;
		if(stdit -> second != (*it).second) return 0;
		it++;
	}
	stdit = --stdQ.end();
	for(it = --Q.end(); it != Q.begin(); it--){
		if(stdit -> first != it -> first) return 0;
		if(stdit -> second != (*it).second) return 0;
		stdit--;
	}
	return 1;
}

bool check13(){ // erase(it--)
	sjtu::map<int, int> Q;
	std::map<int, int> stdQ;
	int num[30001];
	num[0] = 0;
	for(int i = 1; i <= 30000; i++) num[i] = num[i - 1] + rand() % 325 + 1; 
	for(int i = 1; i <= 60000; i++) swap(num[rand() % 30000 + 1], num[rand() % 30000 + 1]);
	for(int i = 1; i <= 30000; i++){
		int t = rand();
		stdQ[num[i]] = t; Q[num[i]] = t;
	}
	
	sjtu::map<int, int>::iterator it;
	std::map<int, int>::iterator stdit;
	for(int i = 1; i <= 60000; i++) swap(num[rand() % 30000 + 1], num[rand() % 30000 + 1]);
	for(int i = 1; i <= 10325; i++){
		it = Q.find(num[i]); if(it != Q.begin()) Q.erase(it--);
		stdit = stdQ.find(num[i]); if(stdit != stdQ.begin()) stdQ.erase(stdit--);
		if(it -> first != stdit -> first)return 0;
	}	
	if(Q.size() != stdQ.size()) return 0;
	it = Q.begin();
	for(stdit = stdQ.begin(); stdit != stdQ.end(); stdit++){ 
		if(stdit -> first != it -> first) return 0;
		if(stdit -> second != (*it).second) return 0;
		it++;
	}
	stdit = --stdQ.end();
	for(it = --Q.end(); it != Q.begin(); it--){
		if(stdit -> first != it -> first) return 0;
		if(stdit -> second != (*it).second) return 0;
		stdit--;
	}
	return 1;
}

bool check14(){// have fun
	sjtu::map<int, int> Q;
	Q[3] = 25; Q[25] = 3; Q[1314] = 520; Q[3225] = 1; Q[10000] = 6666; 
	sjtu::map<int, int>::iterator it;
	it = Q.find(3225);
	Q.erase(--Q.end());
	if(it -> first != 3225 || it -> second != 1) return 0;
	Q.erase(Q.begin());
	if(it -> first != 3225 || it -> second != 1) return 0;
	return 1;
}
/*bool check100(){
	sjtu::map<int, int> Q;
	Q[3] = 5;
	Q[6] =10;
	const sjtu::map<int, int> Q_const(Q);
	sjtu::map<int, int> :: iterator it;
	it = Q.begin();
	//it -> first++;
	//it = Q_const.begin();	
	//it = Q_const.find(6);
	sjtu::map<int, int> :: const_iterator cit;
	cit = Q_const.find(3);
	//cit -> second = 6;
	//(cit -> second)++;
	//cit -> fisrt = 10;
	//++Q_const.at(6);
}*/
int A = 325, B = 2336, Last = 233, Mod = 1000007;

int Rand(){
	return Last = (A * Last + B) % Mod;
}

void easy_test(){
	sjtu::map<int, int> Q;
	Q.clear();
	sjtu::map<int, int> :: iterator it;
	int num[3001], left[3001];
	memset(left, 0, sizeof(left));
	for(int i = 1; i <= 2000; i++) num[i] = i;
	for(int i = 2001; i <= 3000; i++) num[i] = i - 2000;
	for(int i = 1; i <= 6000; i++) swap(num[Rand() % 3000 + 1], num[Rand() % 3000 + 1]);
	for(int i = 1; i <= 3000; i++){
		if(left[num[i]]){
			if(Q.count(num[i])){
				it = Q.find(num[i]); Q.erase(it);
			}
			else cout << "fuck you!" << endl;
		}
		else{
			Q[num[i]] = num[i];
			left[num[i]]++;
		}
	}
	for(it = Q.begin(); it != Q.end(); ++it){ 
		cout << it -> first << " "  << it -> second << " ";
	}
	cout << endl;
}

int main(){
	//freopen("testans_advance.out", "w", stdout);
	srand(time(NULL));
	easy_test();
	if(!check1()) cout << "Test 1 Failed......" << endl; else cout << "Test 1 Passed!" << endl;
	if(!check2()) cout << "Test 2 Failed......" << endl; else cout << "Test 2 Passed!" << endl;
	if(!check3()) cout << "Test 3 Failed......" << endl; else cout << "Test 3 Passed!" << endl;
	if(!check4()) cout << "Test 4 Failed......" << endl; else cout << "Test 4 Passed!" << endl;
	if(!check5()) cout << "Test 5 Failed......" << endl; else cout << "Test 5 Passed!" << endl;
	if(!check6()) cout << "Test 6 Failed......" << endl; else cout << "Test 6 Passed!" << endl;
	if(!check7()) cout << "Test 7 Failed......" << endl; else cout << "Test 7 Passed!" << endl;
	if(!check8()) cout << "Test 8 Failed......" << endl; else cout << "Test 8 Passed!" << endl;
	if(!check9()) cout << "Test 9 Failed......" << endl; else cout << "Test 9 Passed!" << endl;
	if(!check10()) cout << "Test 10 Failed......" << endl; else cout << "Test 10 Passed!" << endl;
	if(!check11()) cout << "Test 11 Failed......" << endl; else cout << "Test 11 Passed!" << endl;
	if(!check12()) cout << "Test 12 Failed......" << endl; else cout << "Test 12 Passed!" << endl;
	if(!check13()) cout << "Test 13 Failed......" << endl; else cout << "Test 13 Passed!" << endl;
	if(!check14()) cout << "Test 14 Failed......" << endl; else cout << "Test 14 Passed!" << endl;
	return 0;
}

