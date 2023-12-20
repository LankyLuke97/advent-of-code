#pragma once
#include "Reader.h"

class Day5 {
private:
	const std::string testFile1 = "inputs/day5_part1_test.txt";
	const std::string testFile2 = "inputs/day5_part2_test.txt";
	const std::string puzzleFile = "inputs/day5.txt";
	int calculatePuzzle1(std::vector<std::string> input);
	int calculatePuzzle2(std::vector<std::string> input);

public:
	void puzzle1();
	void puzzle2();
	void test();
};
