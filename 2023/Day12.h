#pragma once
#include <unordered_map>
#include <queue>
#include "Reader.h"

class Day12 {
private:
	static std::unordered_map<std::string, int> cache;
	const std::string testFile1 = "inputs/day12_part1_test.txt";
	const std::string testFile2 = "inputs/day12_part2_test.txt";
	const std::string puzzleFile = "inputs/day12.txt";
	int calculatePuzzle1(std::vector<std::string> input);
	int64_t calculatePuzzle2(std::vector<std::string> input);
	int64_t part2Recursion(std::string& data, std::queue<int> groups);
public:
	void puzzle1();
	void puzzle2();
	void test();
};