#pragma once
#include "Reader.h"

class Day13 {
private:
	const std::string testFile1 = "inputs/day13_part1_test.txt";
	const std::string testFile2 = "inputs/day13_part2_test.txt";
	const std::string puzzleFile = "inputs/day13.txt";
	int calculatePuzzle1(std::vector<std::string> input);
	int64_t calculatePuzzle2(std::vector<std::string> input);
public:
	void puzzle1();
	void puzzle2();
	void test();
};