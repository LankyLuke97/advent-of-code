#pragma once
#include <cassert>
#include <Windows.h>
#include "Day1.h"

int Day1::calculatePuzzle1(std::vector<std::string> input) {
	int answer = 0;

	for(std::string line : input) {
		if (line.empty()) break;
		std::string::iterator firstNum = line.begin();
		std::string::iterator lastNum = line.end() - 1;

		while(firstNum < line.end()) {
			if(*firstNum <= '9' && *firstNum >= '0') break;
			firstNum++;
		}

		while (lastNum > line.begin()) {
			if(*lastNum <= '9' && *lastNum >= '0') break;
			lastNum--;
		}

		answer += ((*firstNum - '0') * 10) + (*lastNum - '0');
	}

	return answer;
}

int Day1::calculatePuzzle2(std::vector<std::string> input) {
	int answer = 0;

	std::vector<std::string> wordsForward = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	std::vector<std::string> wordsBackward = { "orez", "eno", "owt", "eerht", "ruof", "evif", "xis", "neves", "thgie", "enin" };

	for (std::string line : input) {
		if (line.empty()) break;
		std::string::iterator firstPtr = line.begin();
		std::string::iterator lastPtr = line.end() - 1;

		while (firstPtr < line.end()) {
			if (*firstPtr <= '9' && *firstPtr >= '0') break;
			firstPtr++;
		}

		while (lastPtr > line.begin()) {
			if (*lastPtr <= '9' && *lastPtr >= '0') break;
			lastPtr--;
		}

		if (firstPtr == line.end()) firstPtr = line.end() - 1;

		int firstIndex = firstPtr - line.begin();
		int lastIndex = lastPtr - line.begin();
		int firstNum = -1;
		int lastNum = -1;
		std::string before = line.substr(0, firstIndex);
		std::string after = line.substr(lastIndex, line.end() - lastPtr);
		std::reverse(after.begin(), after.end());

		for (int i = 0; i < wordsForward.size(); i++) {
			auto pos = before.find(wordsForward[i]);
			if (pos == std::string::npos) continue;

			if (pos < firstIndex) {
				firstIndex = (int)pos;
				firstNum = i;
			}

			if (firstIndex == 0) break;
		}

		for (int i = 0; i < wordsBackward.size(); i++) {
			auto pos = after.find(wordsBackward[i]);
			if (pos == std::string::npos) continue;

			if (line.size() - pos > lastIndex) {
				lastIndex = line.size() - (int)pos;
				lastNum = i;
			}

			if (lastIndex == 0) break;
		}

		if (firstNum == -1) firstNum = *firstPtr - '0';
		if (lastNum == -1) lastNum = *lastPtr - '0';

		answer += (firstNum * 10) + lastNum;
	}
	return answer;
}


void Day1::puzzle1() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "First puzzle: " << calculatePuzzle1(input) << std::endl;
}

void Day1::puzzle2() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "Second puzzle: " << calculatePuzzle2(input) << std::endl;
}

void Day1::test() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle1(Reader::readFile(testFile1)) == 142);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 1 part 1 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 281);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 1 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}