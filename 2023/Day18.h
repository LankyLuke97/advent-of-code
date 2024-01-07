#pragma once
#include "Reader.h"

class Day18 {
private:
	const std::string testFile1 = "inputs/day18_part1_test.txt";
	const std::string testFile2 = "inputs/day18_part2_test.txt";
	const std::string puzzleFile = "inputs/day18.txt";
	int calculatePuzzle1(std::vector<std::string> input);
	int calculatePuzzle2(std::vector<std::string> input);
public:
	void puzzle1();
	void puzzle2();
	void test();
};