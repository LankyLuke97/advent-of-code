#pragma once
#include <unordered_map>
#include "Reader.h"

struct Module {
	std::string name;
	int type; // 0 for flip-flop, 1 for conjuction, 2 for test/null endpoints
	int state; // 0 for flip-flop off, 1 for flip-flop on
	std::unordered_map<std::string, bool> inputStates; // conjunction input states - 0 for low pulse, 1 for high pulse
	std::vector<std::string> outputs;

	Module() {
		std::string name = "TESTONLY";
		type = 2;
		state = -1;

	}

	Module(std::string _name, int _type) : name(_name), type(_type), state(0) {}

	std::string toString() {
		if (type == 0) return name + "_" + std::to_string(state);

		std::string retVal = name + "_";

		for (auto kv : inputStates) retVal += "_ " + kv.first + "_" + std::to_string(kv.second);
		return retVal;
	}
};

struct Pulse {
	std::string from;
	std::string to;
	bool high;

	Pulse(std::string _from, std::string _to, bool _high) : from(_from), to(_to), high(_high) {}

	std::string toString() {
		return from + (high ? " -high->" : " -low-> ") + to;
	}
};

class Day20 {
private:
	const std::string testFile1_1 = "inputs/day20_part1_test1.txt";
	const std::string testFile1_2 = "inputs/day20_part1_test2.txt";
	const std::string testFile2 = "inputs/day20_part2_test.txt";
	const std::string puzzleFile = "inputs/day20.txt";
	uint64_t calculatePuzzle1(std::vector<std::string> input);
	int calculatePuzzle2(std::vector<std::string> input);
public:
	void puzzle1();
	void puzzle2();
	void test();
};