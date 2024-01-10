#pragma once
#include "Reader.h"

struct Node {
	int position;
	int weight;
	int prevStep;
	std::vector<Node> connectedNodes;

	Node(int _pos, int _prevStep) : position(_pos), prevStep(_prevStep), connectedNodes(std::vector<Node>(12)) {}
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