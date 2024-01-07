#pragma once
#include "Reader.h"

class Day16 {
private:
	const std::string testFile1 = "inputs/day16_part1_test.txt";
	const std::string testFile2 = "inputs/day16_part2_test.txt";
	const std::string puzzleFile = "inputs/day16.txt";
	int calculatePuzzle1(std::vector<std::string> input);
	int calculatePuzzle2(std::vector<std::string> input);
public:
	void puzzle1();
	void puzzle2();
	void test();
};

struct Beam {
	int position;
	int direction;

	Beam(int pos, int dir) : position(pos), direction(dir) {}

	friend bool operator == (Beam const& l, Beam const& r) {
		return (l.position == r.position) && (l.direction == r.direction);
	}
};