#pragma once
#include "Reader.h"

struct Part {
	int x, m, a, s, value;

	Part(int _x, int _m, int _a, int _s) : x(_x), m(_m), a(_a), s(_s) {
		value = _x + _m + _a + _s;
	}
};

struct Part_2 {
	std::pair<int, int> x, m, a, s;
	std::string currentWorkflow;
	int currentStep;
	Part_2() : x(std::make_pair(1, 4000)), m(std::make_pair(1, 4000)), a(std::make_pair(1, 4000)), s(std::make_pair(1, 4000)), currentWorkflow("in"), currentStep(0) {}
	Part_2(Part_2& other, std::string out) : x(other.x), m(other.m), a(other.a), s(other.s), currentWorkflow(out), currentStep(0) {}
};


struct Workflow {
	std::vector<int> flowInstructions;
	std::vector<int> flowVals;
	std::vector<std::string> flowOut;
};

class Day19 {
private:
	const std::string testFile1 = "inputs/day19_part1_test.txt";
	const std::string testFile2 = "inputs/day19_part2_test.txt";
	const std::string puzzleFile = "inputs/day19.txt";
	int calculatePuzzle1(std::vector<std::string> input);
	uint64_t calculatePuzzle2(std::vector<std::string> input);
public:
	void puzzle1();
	void puzzle2();
	void test();
};