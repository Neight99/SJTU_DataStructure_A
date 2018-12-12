#include <fstream>
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <ctime>
#include "exceptions.hpp"
#include "map.hpp"

const int MAXN = 10001;

enum Color{
	Red, Green, Blue, Normal
};

class TestCore{
private:
	const char *title;
	const int id, total;
	long dfn;
	int counter, enter;
public:	
	TestCore(const char *title, const int &id, const int &total) : title(title), id(id), total(total), dfn(clock()), counter(0), enter(0) {
	}
	void init() {
		static char tmp[200];
		sprintf(tmp, "Test %d: %-55s", id, title);
		printf("%-65s", tmp);
	}
	void showMessage(const char *s, const Color &c = Normal) {
	}
	void showProgress() {
	}
	void pass() {
		showMessage("PASSED", Green);
		printf("PASSED");
	}
	void fail() {
		showMessage("FAILED", Red);
		printf("FAILED");
	}
	~TestCore() {
		puts("");
		fflush(stdout);
	}
};

class IntA{
public:
	static int counter;
	int val;
	
	IntA(int val) : val(val) {
		counter++;
	}

	IntA(const IntA &rhs) {
		val = rhs.val;
		counter++;
	}

	IntA & operator = (const IntA &rhs) {
		assert(false);
	}
	
	bool operator ==(const IntA &rhs) {
		return val == rhs.val;
	}
	friend bool operator < (const IntA &lhs, const IntA &rhs) {
		return lhs.val > rhs.val;
	}
	
	~IntA() {
		counter--;
	}
};

int IntA::counter = 0;

class IntB{
public:
	int *val;
	explicit IntB(int val = 0) : val(new int(val)) {
	}
	
	IntB(const IntB &rhs) {
		val = new int(*rhs.val);
	}
	
	IntB & operator =(const IntB &rhs) {
		if (this == &rhs) return *this;
		delete this->val;
		val = new int(*rhs.val);
		return *this;
	}
	
	bool operator !=(const IntB &rhs) const {
		return *val != *rhs.val;
	}
	
	bool operator ==(const IntB &rhs) const {
		return *val == *rhs.val;
	}
	
	~IntB() {
		delete this->val;
	}
};

struct Compare{
	bool operator ()(const IntA &a, const IntA &b)const {
		return a.val > b.val;
	}
};

const std::vector<int> & generator(int n = MAXN) {
	static std::vector<int> raw;
	raw.clear();
	for (int i = 0; i < n; i++) {
		raw.push_back(rand());
	}
	return raw;
}

void tester1() {
	TestCore console("Operator [] & Iterator traverse testing...", 1, 2 * MAXN);
	console.init();
	auto ret = generator(MAXN);
	try{
		std::map<IntA, IntB, Compare> stdmap;
		sjtu::map<IntA, IntB, Compare> srcmap;
		for (int i = 0; i < (int)ret.size(); i++) {
			auto x = ret[i];
			IntB tmp = IntB(rand());
			stdmap[x] = tmp;
			srcmap[x] = tmp;
			//printf("insert(%d, %d)\n", x, tmp.val);
			for (int c = 0; c < 10; c++) {
				int p = rand() % (i + 1);
				if (stdmap[ret[p]] != srcmap[ret[p]]) {
					//std::cerr << ret[p] << " ";
					//std::cerr << stdmap[ret[p]] << " " << srcmap[ret[p]] << std::endl;
					console.fail();
					return;
				}
			}
			console.showProgress();
		}
		auto itB = srcmap.cbegin();
		for (auto itA = stdmap.begin(); itA != stdmap.end(); ++itA, ++itB) {
			if ((itA -> first).val != (itA -> first).val || (itB -> first).val != (itB -> first).val) {
				console.fail();
				return;
			}
			console.showProgress();
		}
	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.pass();
}

void tester2() {
	TestCore console("Insertion function testing...", 2, 2 * MAXN);
	console.init();
	auto ret = generator(MAXN);
	try{
		std::map<IntA, IntB, Compare> stdmap;
		sjtu::map<IntA, IntB, Compare> srcmap;
		for (int i = 0; i < (int)ret.size(); i++) {
			auto x = ret[i];
			IntB tmp = IntB(rand());
			stdmap.insert(std::map<IntA, IntB, Compare>::value_type(x, tmp));
			srcmap.insert(sjtu::map<IntA, IntB, Compare>::value_type(x, tmp));
			for (int c = 0; c < 10; c++) {
				int p = rand() % (i + 1);
				if (stdmap[ret[p]] != srcmap[ret[p]]) {
					console.fail();
					return;
				}
			}
			console.showProgress();
		}
		auto itB = srcmap.begin();
		for (auto itA = stdmap.begin(); itA != stdmap.end(); ++itA, ++itB) {
			if ((itA -> first).val != (itA -> first).val || (itB -> first).val != (itB -> first).val) {
				console.fail();
				return;
			}
			console.showProgress();
		}
	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.pass();
}

void tester3() {
	TestCore console("Deletion & Find function testing...", 3, 2 * MAXN);
	console.init();
	auto ret = generator(MAXN);
	try{
		std::map<IntA, IntB, Compare> stdmap;
		sjtu::map<IntA, IntB, Compare> srcmap;
		for (int i = 0; i < (int)ret.size(); i++) {
			auto x = ret[i];
			IntB tmp = IntB(rand());
			stdmap.insert(std::map<IntA, IntB, Compare>::value_type(x, tmp));
			srcmap.insert(sjtu::map<IntA, IntB, Compare>::value_type(x, tmp));
			console.showProgress();
		}
		std::random_shuffle(ret.begin(), ret.end());
		for (auto x : ret) {
			if (stdmap.find(x) != stdmap.end()) {
				srcmap.erase(srcmap.find(x));
				stdmap.erase(stdmap.find(x));
			}
			for (int c = 0; c < 10; c++) {
				int p = rand() % ret.size();
				if (stdmap.find(ret[p]) != stdmap.end()) {
					if (stdmap[ret[p]] != srcmap[ret[p]]) {
						console.fail();
						return;
					}
				}
			}
			console.showProgress();
		}
	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.pass();
}

void tester4() {
	TestCore console("Error throwing A - Invalid Iterator testing...", 4, 0);
	console.init();
	auto ret = generator(MAXN);
	try{
		sjtu::map<IntA, IntB, Compare> srcmap;
		++srcmap.end();
	} catch (sjtu::exception error) {
		try{
			sjtu::map<IntA, IntB, Compare> srcmap;
			--srcmap.begin();
		} catch (sjtu::exception error) {
			try{
				sjtu::map<IntA, IntB, Compare> srcmap;
				srcmap.end()++;
			} catch (sjtu::exception error) {
				try{
					sjtu::map<IntA, IntB, Compare> srcmap;
					srcmap.begin()--;
				} catch (sjtu::exception error) {
					console.pass();
					return;
				}
			}
		}
	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.fail();
}

void tester5() {
	TestCore console("Error throwing B - Invalid Const_Iterator testing...", 5, 0);
	console.init();
	auto ret = generator(MAXN);
	try{
		sjtu::map<IntA, IntB, Compare> srcmap;
		++srcmap.cend();
	} catch (sjtu::exception error) {
		try{
			sjtu::map<IntA, IntB, Compare> srcmap;
			--srcmap.cbegin();
		} catch (sjtu::exception error) {
			try{
				sjtu::map<IntA, IntB, Compare> srcmap;
				srcmap.cend()++;
			} catch (sjtu::exception error) {
				try{
					sjtu::map<IntA, IntB, Compare> srcmap;
					srcmap.cbegin()--;
				} catch (sjtu::exception error) {
					console.pass();
					return;
				}
			}
		}
	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.fail();
}

void tester6() {
	TestCore console("Error throwing C - Invalid Index testing...", 6, 2 * MAXN);
	console.init();
	auto ret = generator(MAXN);
	try{
		sjtu::map<IntA, IntB, Compare> srcmap;
		for (auto x : ret) {
			srcmap[x] = IntB(rand());
			console.showProgress();
		}
		try{
			sjtu::map<IntA, IntB, Compare> srcmap;
			srcmap.at(IntA(-1)) = IntB(2);
		} catch (...) {
			console.pass();
			return;
		}
	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.fail();
}

void tester7() {
	const int MAXC = MAXN / 2;
	TestCore console("Copy constructure testing...", 7, MAXN + MAXC + 2 * (MAXN - MAXC));
	console.init();
	auto ret = generator(MAXN);
	try{
		std::map<IntA, IntB, Compare> stdmap;
		sjtu::map<IntA, IntB, Compare> srcmap;
		for (int i = 0; i < (int)ret.size(); i++) {
			auto x = ret[i];
			IntB tmp = IntB(rand());
			stdmap.insert(std::map<IntA, IntB, Compare>::value_type(x, tmp));
			srcmap.insert(sjtu::map<IntA, IntB, Compare>::value_type(x, tmp));
			console.showProgress();
		}
		std::map<IntA, IntB, Compare> tmp1(stdmap);
		sjtu::map<IntA, IntB, Compare> tmp2(srcmap);
		std::random_shuffle(ret.begin(), ret.end());
		for (int i = 0; i < MAXC; i++) {
			if (stdmap.find(ret[i]) != stdmap.end()) {
				srcmap.erase(srcmap.find(ret[i]));
				stdmap.erase(stdmap.find(ret[i]));
			}
			console.showProgress();
		}
		auto itB = srcmap.begin();
		for (auto itA = stdmap.begin(); itA != stdmap.end(); ++itA, ++itB) {
			if ((itA -> first).val != (itA -> first).val || (itB -> first).val != (itB -> first).val) {
				console.fail();
				return;
			}
			console.showProgress();
		}
		
		itB = tmp2.begin();
		for (auto itA = tmp1.begin(); itA != tmp1.end(); ++itA, ++itB) {
			if ((itA -> first).val != (itA -> first).val || (itB -> first).val != (itB -> first).val) {
				console.fail();
				return;
			}
			console.showProgress();
		}
	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.pass();
}

void tester8() {
	const int MAXC = MAXN / 2;
	TestCore console("Operator = testing...", 8, MAXN + MAXC + 2 * (MAXN - MAXC));
	console.init();
	auto ret = generator(MAXN);
	try{
		std::map<IntA, IntB, Compare> stdmap;
		sjtu::map<IntA, IntB, Compare> srcmap;
		for (int i = 0; i < (int)ret.size(); i++) {
			auto x = ret[i];
			IntB tmp = IntB(rand());
			stdmap.insert(std::map<IntA, IntB, Compare>::value_type(x, tmp));
			srcmap.insert(sjtu::map<IntA, IntB, Compare>::value_type(x, tmp));
			console.showProgress();
		}
		std::map<IntA, IntB, Compare> tmp1;
		tmp1 = stdmap;
		sjtu::map<IntA, IntB, Compare> tmp2;
		tmp2 = srcmap;
		std::random_shuffle(ret.begin(), ret.end());
		for (int i = 0; i < MAXC; i++) {
			if (stdmap.find(ret[i]) != stdmap.end()) {
				srcmap.erase(srcmap.find(ret[i]));
				stdmap.erase(stdmap.find(ret[i]));
			}
			console.showProgress();
		}
		auto itB = srcmap.cbegin();
		for (auto itA = stdmap.begin(); itA != stdmap.end(); ++itA, ++itB) {
			if ((itA -> first).val != (itA -> first).val || (itB -> first).val != (itB -> first).val) {
				console.fail();
				return;
			}
			console.showProgress();
		}
		
		itB = tmp2.cbegin();
		for (auto itA = tmp1.begin(); itA != tmp1.end(); ++itA, ++itB) {
			if ((itA -> first).val != (itA -> first).val || (itB -> first).val != (itB -> first).val) {
				console.fail();
				return;
			}
			console.showProgress();
		}
	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.pass();
}

void tester9() {
	TestCore console("At function testing...", 9, 2 * MAXN);
	console.init();
	auto ret = generator(MAXN);
	try{
		std::map<IntA, IntB, Compare> stdmap;
		sjtu::map<IntA, IntB, Compare> srcmap;
		for (int i = 0; i < (int)ret.size(); i++) {
			auto x = ret[i];
			IntB tmp = IntB(rand());
			stdmap[x] = tmp;
			srcmap[x] = tmp;
			for (int c = 0; c < 10; c++) {
				int p = rand() % (i + 1);
				if (stdmap.at(ret[p]) != srcmap.at(ret[p])) {
					console.fail();
					return;
				}
				tmp = IntB(rand());
				stdmap.at(ret[p]) = tmp;
				srcmap.at(ret[p]) = tmp;
			}
			console.showProgress();
		}
		auto itB = srcmap.cbegin();
		for (auto itA = stdmap.begin(); itA != stdmap.end(); ++itA, ++itB) {
			if ((itA -> first).val != (itA -> first).val || (itB -> first).val != (itB -> first).val) {
				console.fail();
				return;
			}
			console.showProgress();
		}
	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.pass();
}

void tester10() {
	TestCore console("Objects' independence testing...", 10, 6 * MAXN);
	console.init();
	auto ret = generator(MAXN);
	try{
		std::map<IntA, IntB, Compare> stdmap;
		sjtu::map<IntA, IntB, Compare> srcmap;
		for (int i = 0; i < (int)ret.size(); i++) {
			auto x = ret[i];
			IntB tmp = IntB(rand());
			stdmap.insert(std::map<IntA, IntB, Compare>::value_type(x, tmp));
			srcmap.insert(sjtu::map<IntA, IntB, Compare>::value_type(x, tmp));
			console.showProgress();
		}
		std::map<IntA, IntB, Compare> std1(stdmap), std2;
		std2 = std1 = std1;
		sjtu::map<IntA, IntB, Compare> src1(srcmap), src2;
		src2 = src1 = src1;
		for (int i = 0; i < (int)ret.size(); i++) {
			if (stdmap.find(ret[i]) != stdmap.end()) {
				srcmap.erase(srcmap.find(ret[i]));
				stdmap.erase(stdmap.find(ret[i]));
			}
			console.showProgress();
		}
		ret = generator(MAXN);
		for (int i = 0; i < (int)ret.size(); i++) {
			auto x = ret[i];
			IntB tmp = IntB(rand());
			std1.insert(std::map<IntA, IntB, Compare>::value_type(x, tmp));
			src1.insert(sjtu::map<IntA, IntB, Compare>::value_type(x, tmp));
			console.showProgress();
		}
		
		auto itB = srcmap.begin();
		for (auto itA = stdmap.begin(); itA != stdmap.end(); ++itA, ++itB) {
			if ((itA -> first).val != (itA -> first).val || (itB -> first).val != (itB -> first).val) {
				console.fail();
				return;
			}
			console.showProgress();
		}
		
		itB = src1.begin();
		for (auto itA = std1.begin(); itA != std1.end(); ++itA, ++itB) {
			if ((itA -> first).val != (itA -> first).val || (itB -> first).val != (itB -> first).val) {
				console.fail();
				return;
			}
			console.showProgress();
		}
		
		itB = src2.begin();
		for (auto itA = std2.begin(); itA != std2.end(); ++itA, ++itB) {
			if ((itA -> first).val != (itA -> first).val || (itB -> first).val != (itB -> first).val) {
				console.fail();
				return;
			}
			console.showProgress();
		}
	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.pass();
}

void tester11() {
	const int MAXN = 100001;
	TestCore console("Comprehensive testing...", 11, 3 * MAXN);
	console.init();
	auto ret = generator(MAXN);
	try{
		std::map<IntA, IntB, Compare> stdmap;
		sjtu::map<IntA, IntB, Compare> srcmap;
		for (int i = 0, cnt = 0; i < (int)ret.size(); i++, cnt++) {
			int tmp = rand();
			auto retA = stdmap.insert(std::map<IntA, IntB, Compare>::value_type(IntA(ret[i]), IntB(tmp)));
			auto retB = srcmap.insert(sjtu::map<IntA, IntB, Compare>::value_type(IntA(ret[i]), IntB(tmp)));
			console.showProgress();
			if (!retA.second) {
				cnt--;
				ret[i] = -1;
				console.showProgress();
				continue;
			}
			if (rand() % 100 < 12 && cnt > 0) {
				int p = 0;
				while (ret[p] < 0) {
					p = rand() % (i + 1);
				}
				stdmap.erase(stdmap.find(ret[p]));
				srcmap.erase(srcmap.find(ret[p]));
				ret[p] = -1;
				cnt++;
				console.showProgress();
			}
			if (stdmap.size() != srcmap.size()) {
				console.fail();
				return;
			}
		}
		auto itB = srcmap.cbegin();
		for (auto itA = stdmap.begin(); itA != stdmap.end(); ++itA, ++itB) {
			if ((itA -> first).val != (itA -> first).val || (itB -> first).val != (itB -> first).val) {
				console.fail();
				return;
			}
			console.showProgress();
		}
		
		const auto stdtmp(stdmap);
		const auto srctmp(srcmap);
		
		std::map<IntA, IntB, Compare>::const_iterator citA = stdtmp.cbegin();
		sjtu::map<IntA, IntB, Compare>::const_iterator citB = srctmp.cbegin();
		
		stdtmp.size();
		srctmp.size();
		
		for (auto x : ret) {
			if (x >= 0) {
				if (stdmap.at(x) != srcmap.at(x)) {
					console.fail();
					return;
				}
				if (srctmp.count(x) == 0) {
					console.fail();
					return;
				}
			}
			console.showProgress();
		}
	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.pass();
}

int main() {
#ifdef SPECIAL
	puts("AATree-Map Checker Version 1.2");
#endif
	tester1();
	tester2();
	tester3();
	tester4();
	tester5();
	tester6();
	tester7();
	tester8();
	tester9();
	tester10();
	tester11();
	return 0;
}
