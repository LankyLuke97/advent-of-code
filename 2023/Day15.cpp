#pragma once
#include <cassert>
#include <sstream>
#include <unordered_map>
#include <Windows.h>
#include "Day15.h"

int Day15::calculatePuzzle1(std::vector<std::string> input) {
	int answer = 0;

	int current = 0;
	for (char c : input[0]) {
		if (c == ',') {
			answer += current;
			current = 0;
			continue;
		}

		current += int(c);
		current *= 17;
		current = current % 256;
	}
	answer += current;

	return answer;
}

int Day15::calculatePuzzle2(std::vector<std::string> input) {
	int answer = 0;

	return answer;
}

void Day15::puzzle1() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "First puzzle: " << calculatePuzzle1(input) << std::endl;
}

void Day15::puzzle2() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "Second puzzle: " << calculatePuzzle2(input) << std::endl;
}

void Day15::test() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle1(Reader::readFile(testFile1)) == 1320);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 15 part 1 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 0);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 15 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}