#pragma once
#include "Reader.h"

class Day10 {
private:
	const std::string testFile1_1 = "inputs/day10_part1_test1.txt";
	const std::string testFile1_2 = "inputs/day10_part1_test2.txt";
	const std::string testFile1_3 = "inputs/day10_part1_test3.txt";
	const std::string testFile1_4 = "inputs/day10_part1_test4.txt";
	const std::string testFile2 = "inputs/day10_part2_test.txt";
	const std::string puzzleFile = "inputs/day10.txt";
	int calculatePuzzle1(std::vector<std::string> input);
	int calculatePuzzle2(std::vector<std::string> input);
public:
	void puzzle1();
	void puzzle2();
	void test();
};