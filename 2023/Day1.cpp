#pragma once
#include <cassert>
#include "Day1.h"

int Day1::calculatePuzzle1(std::vector<std::string> input) {
	int answer = 0;

	for(std::string line : input) {
		if (line.empty()) break;
		std::string::iterator firstNum = line.begin();
		std::string::iterator lastNum = line.end() - 1;

		int iterFrontCount = 0;
		int iterBackCount = line.size();

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
		if(line.empty()) break;
		std::string::iterator firstNum = line.begin();
		std::string::iterator lastNum = line.end() - 1;

		int iterFrontCount = 0;
		int iterBackCount = line.size();

		while (firstNum < line.end()) {
			if (*firstNum <= '9' && *firstNum >= '0') break;
			firstNum++;
		}

		while (lastNum > line.begin()) {
			if (*lastNum <= '9' && *lastNum >= '0') break;
			lastNum--;
		}

		for(std::string word : wordsForward
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
	assert(calculatePuzzle1(Reader::readFile(testFile1)) == 142);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 281);
}