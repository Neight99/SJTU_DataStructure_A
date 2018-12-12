#include "map.hpp"
#include <iostream>
#include <cassert>
#include <string>

class Integer {
public:
	static int counter;
	int val;
	
	Integer(int val) : val(val) {
		counter++;
	}

	Integer(const Integer &rhs) {
		val = rhs.val;
		counter++;
	}

	Integer& operator = (const Integer &rhs) {
		assert(false);
	}

	~Integer() {
		counter--;
	}
};

int Integer::counter = 0;

class Compare {
public:
	bool operator () (const Integer &lhs, const Integer &rhs) const {
		return lhs.val < rhs.val;
	}
};

void tester(void) {
	//	test: constructor
	sjtu::map<Integer, std::string, Compare> map;
	//	test: empty(), size()
	assert(map.empty() && map.size() == 0);
	//	test: operator[], insert()
	for (int i = 0; i < 10000; ++i) {
		std::string string = "";
		for (int number = i; number; number /= 10) {
			char digit = '0' + number % 10;
			string = digit + string;
		}
		if (i & 1) {
			map[Integer(i)] = string;
			auto result = map.insert(sjtu::pair<Integer, std::string>(Integer(i), string));
			assert(!result.second);
		} else {
			auto result = map.insert(sjtu::pair<Integer, std::string>(Integer(i), string));
			assert(result.second);
		}
	}
	//	test: count(), find(), erase()
	for (int i = 0; i < 10000; ++i) {
		if (i > 1896 && i <= 2016) {
			continue;
		}
		assert(map.count(Integer(i)) == 1);
		assert(map.find(Integer(i)) != map.end());
		map.erase(map.find(Integer(i)));
	}
	//	test: constructor, operator=, clear();
	for (int i = 0; i < (int)map.size(); ++i) {
		sjtu::map<Integer, std::string, Compare> copy(map);
		map.clear();
		std::cout << map.size() << " " << copy.size() << " ";
		map = copy;
		copy.clear();
		std::cout << map.size() << " " << copy.size() << " ";
		copy = map;
		map.clear();
		std::cout << map.size() << " " << copy.size() << " ";
		map = copy;
		copy.clear();
		std::cout << map.size() << " " << copy.size() << " ";
	}
	std::cout << std::endl;
	//	test: const_iterator, cbegin(), cend(), operator++, at()
	sjtu::map<Integer, std::string, Compare>::const_iterator const_iterator;
	const_iterator = map.cbegin();
	while (const_iterator != map.cend()) {
		const Integer integer(const_iterator->first);
		const_iterator++;
		std::cout << map.at(integer) << " ";
	}
	std::cout << std::endl;
	//	test: iterator, operator--, operator->
	sjtu::map<Integer, std::string, Compare>::iterator iterator;
	iterator = map.end();
	while (true) {
		sjtu::map<Integer, std::string, Compare>::iterator peek = iterator;
		if (peek == map.begin()) {
			std::cout << std::endl;
			break;
		}
		std::cout << (--iterator)->second << " ";
	}
	//	test: erase()
	while (map.begin() != map.end()) {
		map.erase(map.begin());
	}
	assert(map.empty() && map.size() == 0);
	//	test: operator[]
	for (int i = 0; i < 10000; ++i) {
		std::cout << map[Integer(i)];
	}
	std::cout << map.size() << std::endl;
}

int main(void) {
	tester();
	std::cout << Integer::counter << std::endl;
}
