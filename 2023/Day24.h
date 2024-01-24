#pragma once
#include "Reader.h"

struct Hail {
	double x, y, z, vx, vy, vz, a, b, c;

	Hail(double _x, double _y, double _z, double _vx, double _vy, double _vz) : x(_x), y(_y), z(_z), vx(_vx), vy(_vy), vz(_vz), a(0), b(0), c(0) {}
};

class Day24 {
private:
	const std::string testFile1 = "inputs/day24_part1_test.txt";
	const std::string testFile2 = "inputs/day24_part2_test.txt";
	const std::string puzzleFile = "inputs/day24.txt";
	int calculatePuzzle1(std::vector<std::string> input, int64_t minRange, int64_t maxRange);
	int calculatePuzzle2(std::vector<std::string> input);
	double determinant(std::vector<std::vector<double>>& matrix);
	std::vector<double> crossProduct(const std::vector<double>& v1, const std::vector<double>& v2);
public:
	void puzzle1();
	void puzzle2();
	void test();
};