#pragma once
#include <unordered_map>
#include "Reader.h"

struct GraphNode {
	bool end;
	int pos;
	std::unordered_map<int, int> connectedTo;

	GraphNode(int _pos) : pos(_pos), end(false) {}

	bool operator == (int pos) {
		return pos == this->pos;
	}
};

class Day23 {
private:
	const std::string testFile1 = "inputs/day23_part1_test.txt";
	const std::string testFile2 = "inputs/day23_part2_test.txt";
	const std::string puzzleFile = "inputs/day23.txt";
	int calculatePuzzle1(std::vector<std::string> input);
	int calculatePuzzle2(std::vector<std::string> input);
public:
	void puzzle1();
	void puzzle2();
	void test();
};