#pragma once
#include "Reader.h"

struct Hail {
	long double x, y, z, vx, vy, vz, a, b, c;

	Hail(long double _x, long double _y, long double _z, long double _vx, long double _vy, long double _vz) : x(_x), y(_y), z(_z), vx(_vx), vy(_vy), vz(_vz), a(0), b(0), c(0) {}
};

class Day24 {
private:
	const std::string testFile1 = "inputs/day24_part1_test.txt";
	const std::string testFile2 = "inputs/day24_part2_test.txt";
	const std::string puzzleFile = "inputs/day24.txt";
	int calculatePuzzle1(std::vector<std::string> input, int64_t minRange, int64_t maxRange);
	int calculatePuzzle2(std::vector<std::string> input);
	std::vector<std::vector<long double>> findInverse(const std::vector<std::vector<long double>>& matrix);
public:
	void puzzle1();
	void puzzle2();
	void test();
};