#pragma once
#include "Reader.h"

struct Brick {
	bool canDisintegrate;
	int id;
	int x1, x2, y1, y2, z1, z2;
	std::vector<int> balancedOn;

	Brick() : id(-1), x1(-1), x2(-1), y1(-1), y2(-1), z1(-1), z2(-1), canDisintegrate(false) {} // Can't decipher what's using this, but there's a build error without it :)

	Brick(int _id, int _x1, int _x2, int _y1, int _y2, int _z1, int _z2) : id(_id), x1(_x1), x2(_x2 + 1), y1(_y1), y2(_y2 + 1), z1(_z1), z2(_z2 + 1), canDisintegrate(true) {}

	friend bool operator < (Brick const& l, Brick const& r) {
		return l.z1 < r.z1;
	}
};

class Day22 {
private:
	const std::string testFile1 = "inputs/day22_part1_test.txt";
	const std::string testFile2 = "inputs/day22_part2_test.txt";
	const std::string puzzleFile = "inputs/day22.txt";
	int calculatePuzzle1(std::vector<std::string> input);
	int calculatePuzzle2(std::vector<std::string> input);
public:
	void puzzle1();
	void puzzle2();
	void test();
};