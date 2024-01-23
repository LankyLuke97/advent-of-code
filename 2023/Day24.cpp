#pragma once
#include <algorithm>
#include <cassert>
#include <sstream>
#include <Windows.h>
#include "Day24.h"

int Day24::calculatePuzzle1(std::vector<std::string> input, int64_t minRange, int64_t maxRange) {
	std::cout << minRange << std::endl;
	std::cout << maxRange << std::endl;
	int answer = 0;

	std::vector<Hail> hailstones;

	for (std::string line : input) {
		if (line.empty()) break;

		std::replace(line.begin(), line.end(), ',', ' ');
		std::replace(line.begin(), line.end(), '@', ' ');

		std::istringstream iss(line);
		std::string token;

		iss >> token;
		int64_t x = std::stoll(token);
		iss >> token;
		int64_t y = std::stoll(token);
		iss >> token;
		int64_t z = std::stoll(token);
		iss >> token;
		float vx = std::stof(token);
		iss >> token;
		float vy = std::stof(token);
		iss >> token;
		float vz = std::stof(token);
		
		Hail hail(x, y, z, vx, vy, vz);

		hail.a = vy;
		hail.b = -vx;
		hail.c = (vy * x) - (vx * y);
		hailstones.push_back(hail);
	}

	for (int i = 0; i < hailstones.size() - 1; i++) {
		Hail h1 = hailstones[i];
		for (int j = i + 1; j < hailstones.size(); j++) {
			Hail h2 = hailstones[j];
			if (h1.a * h2.b == h2.a * h1.b) continue;

			int64_t x = ((h1.c * h2.b) - (h2.c * h1.b)) / ((h1.a * h2.b) - (h2.a * h1.b));
			if (x < minRange || x > maxRange) continue;
			int64_t y = ((h1.a * h2.c) - (h2.a * h1.c)) / ((h1.a * h2.b) - (h2.a * h1.b));
			if (y < minRange || y > maxRange) continue;
			answer++;
		}
	}



	return answer;
}

int Day24::calculatePuzzle2(std::vector<std::string> input) {
	int answer = 0;

	return answer;
}

void Day24::puzzle1() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "First puzzle: " << calculatePuzzle1(input, 200000000000000, 400000000000000) << std::endl;
}

void Day24::puzzle2() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "Second puzzle: " << calculatePuzzle2(input) << std::endl;
}

void Day24::test() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle1(Reader::readFile(testFile1), 7, 27) == 2);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 24 part 1 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 0);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 24 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}