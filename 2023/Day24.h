#pragma once
#include "Reader.h"

struct Hail {
	int64_t x, y, z;
	float vx, vy, vz, a, b, c;

	Hail(int64_t _x, int64_t _y, int64_t _z, float _vx, float _vy, float _vz) : x(_x), y(_y), z(_z), vx(_vx), vy(_vy), vz(_vz), a(0), b(0), c(0) {}
};

class Day24 {
private:
	const std::string testFile1 = "inputs/day24_part1_test.txt";
	const std::string testFile2 = "inputs/day24_part2_test.txt";
	const std::string puzzleFile = "inputs/day24.txt";
	int calculatePuzzle1(std::vector<std::string> input, int64_t minRange, int64_t maxRange);
	int calculatePuzzle2(std::vector<std::string> input);
public:
	void puzzle1();
	void puzzle2();
	void test();
};