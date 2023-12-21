#pragma once
#include <cassert>
#include <sstream>
#include <Windows.h>
#include "Day7.h"

int Day7::calculatePuzzle1(std::vector<std::string> input) {
	int answer = 0;

	std::vector<int> bids(input.size());

	for(std::string line : input) {

	}

	return answer;
}

int Day7::calculatePuzzle2(std::vector<std::string> input) {
	int answer = 0;

	return answer;
}


void Day7::puzzle1() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "First puzzle: " << calculatePuzzle1(input) << std::endl;
}

void Day7::puzzle2() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "Second puzzle: " << calculatePuzzle2(input) << std::endl;
}

void Day7::test() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	assert(calculatePuzzle1(Reader::readFile(testFile1)) == 6440);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 7 part 1 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 0);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 7 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}