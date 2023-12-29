#pragma once
#include "Reader.h"

class Day11 {
private:
	const std::string testFile1 = "inputs/day11_part1_test.txt";
	const std::string testFile2 = "inputs/day11_part2_test.txt";
	const std::string puzzleFile = "inputs/day11.txt";
	int calculatePuzzle1(std::vector<std::string> input);
	int calculatePuzzle2(std::vector<std::string> input);
public:
	void puzzle1();
	void puzzle2();
	void test();
};