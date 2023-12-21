#pragma once
#include <cassert>
#include <cmath>
#include <sstream>
#include "Day6.h"

int Day6::calculatePuzzle1(std::vector<std::string> input) {
	int answer = 1;

	std::vector<int> times;
	std::vector<int> distances;

	std::istringstream timeStream(input[0]);
	std::istringstream distanceStream(input[1]);

	std::string token;
	timeStream >> token;
	distanceStream >> token;

	while (timeStream >> token) times.push_back(std::stoi(token));
	while (distanceStream >> token) distances.push_back(std::stoi(token));

	for(int i = 0; i < times.size(); i++) {
		int solution1 = (times[i] + std::sqrt(std::pow(times[i], 2) - (4 * distances[i]))) / 2;
		int solution2 = (times[i] - std::sqrt(std::pow(times[i], 2) - (4 * distances[i]))) / 2;
		int range = solution1 - solution2;

		if((times[i] - solution1) * solution1 <= distances[i]) range--;

		answer *= range;
	}

	return answer;
}

int Day6::calculatePuzzle2(std::vector<std::string> input) {
	return 0;
}


void Day6::puzzle1() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "First puzzle: " << calculatePuzzle1(input) << std::endl;
}

void Day6::puzzle2() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "Second puzzle: " << calculatePuzzle2(input) << std::endl;
}

void Day6::test() {
	assert(calculatePuzzle1(Reader::readFile(testFile1)) == 288);
	std::cout << "Day 6 part 1 test passed" << std::endl;
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 0);
	std::cout << "Day 6 part 2 test passed" << std::endl;
}