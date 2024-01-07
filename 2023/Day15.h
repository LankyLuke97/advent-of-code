#pragma once
#include "Reader.h"

class Day15 {
private:
	const std::string testFile1 = "inputs/day15_part1_test.txt";
	const std::string testFile2 = "inputs/day15_part2_test.txt";
	const std::string puzzleFile = "inputs/day15.txt";
	int calculatePuzzle1(std::vector<std::string> input);
	int calculatePuzzle2(std::vector<std::string> input);
public:
	void puzzle1();
	void puzzle2();
	void test();
};

struct Lens {
	std::string label;
	int focalLength;

	Lens(std::string _label, int _focalLength) : label(_label), focalLength(_focalLength) {
		
	}

	std::string toString() {
		return "[" + label + " " + std::to_string(focalLength) + "]";
	}

	friend bool operator == (Lens const& l, Lens const& r) {
		return (l.label == r.label);
	}
};