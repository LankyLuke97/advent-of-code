#pragma once
#include <unordered_map>
#include "Reader.h"

struct Step {
	int direction;
	int position;

	Step(int _pos, int _dir) : position(_pos), direction(_dir) {}

	friend bool operator == (Step const& l, Step const& r) {
		return l.direction == r.direction && l.position == r.position;
	}

	std::string toString() const {
		return std::to_string(position) + "," + std::to_string(direction);
	}
};

class Day17 {
private:
	static std::unordered_map<std::string, int> costs;
	static std::vector<Step> visitedSteps;
	const std::string testFile1 = "inputs/day17_part1_test.txt";
	const std::string testFile2 = "inputs/day17_part2_test.txt";
	const std::string puzzleFile = "inputs/day17.txt";
	int calculatePuzzle1(std::vector<std::string> input);
	int calculatePuzzle2(std::vector<std::string> input);
	int recursePuzzle1(const std::string& input, std::vector<Step> steps, int horizontalSize, int verticalSize);
public:
	void puzzle1();
	void puzzle2();
	void test();
};