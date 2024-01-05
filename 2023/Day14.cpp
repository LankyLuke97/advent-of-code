#pragma once
#include <cassert>
#include <sstream>
#include <Windows.h>
#include "Day14.h"

int Day14::calculatePuzzle1(std::vector<std::string> input) {
	int answer = 0;

	std::vector<int> currentEmpty(input[0].size(), 0);
	int size = input.size() - 1;
	
	for (int i = 0; i < input.size(); i++) {
		if (input[i].empty()) break;

		std::string line = input[i];

		for(int cInd = 0; cInd < line.size(); cInd++) {
			char c = line[cInd];
			if (c == '.') continue;
			if (c == '#') {
				currentEmpty[cInd] = i + 1;
				continue;
			}
			answer += size - currentEmpty[cInd]++;
		}
	}

	return answer;
}

int Day14::calculatePuzzle2(std::vector<std::string> input) {
	int answer = 0;

	return answer;
}

void Day14::puzzle1() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "First puzzle: " << calculatePuzzle1(input) << std::endl;
}

void Day14::puzzle2() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "Second puzzle: " << calculatePuzzle2(input) << std::endl;
}

void Day14::test() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle1(Reader::readFile(testFile1)) == 136);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 14 part 1 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 0);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 14 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}