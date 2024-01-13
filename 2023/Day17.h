#pragma once
#include "Reader.h"

struct Node {
	bool visited;
	int position;
	int prevStep;
	int weight;
	int distFromSource;
	int originalPosition;
	std::vector<int> connectedNodes;

	Node(int _pos, int _prevStep, int _origPos) : position(_pos), prevStep(_prevStep), visited(false), originalPosition(_origPos), distFromSource(INT_MAX), weight(-1) {}
	
	friend bool operator < (Node const& l, Node const& r) {
		return l.distFromSource > r.distFromSource; // This is reversed to implement a min heap for const look up in D's algo
	}
};

class Day17 {
private:
	const std::string testFile1 = "inputs/day17_part1_test.txt";
	const std::string testFile2 = "inputs/day17_part2_test.txt";
	const std::string puzzleFile = "inputs/day17.txt";
	int calculatePuzzle1(std::vector<std::string> input);
	int calculatePuzzle2(std::vector<std::string> input);
public:
	void puzzle1();
	void puzzle2();
	void test();
};