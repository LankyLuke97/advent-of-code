#pragma once
#include "Reader.h"

class Day4 {
private:
	const std::string testFile1 = "inputs/day4_part1_test.txt";
	const std::string testFile2 = "inputs/day4_part2_test.txt";
	const std::string puzzleFile = "inputs/day4.txt";
	int calculatePuzzle1(std::vector<std::string> input);
	int calculatePuzzle2(std::vector<std::string> input);

public:
	void puzzle1();
	void puzzle2();
	void test();
};
