#pragma once
#include "Reader.h"

class Day8 {
private:
	const std::string testFile1 = "inputs/day8_part1_test.txt";
	const std::string testFile2 = "inputs/day8_part2_test.txt";
	const std::string puzzleFile = "inputs/day8.txt";
	int calculatePuzzle1(std::vector<std::string> input);
	int64_t calculatePuzzle2(std::vector<std::string> input);
	static int64_t lcm(int64_t x, int64_t y);
public:
	void puzzle1();
	void puzzle2();
	void test();
};