#pragma once
#include <cassert>
#include <sstream>
#include <unordered_map>
#include <Windows.h>
#include "Day14.h"

int Day14::calculatePuzzle1(std::vector<std::string> input) {
	int answer = 0;

	std::vector<int> currentEmpty(input[0].size(), 0);
	int size = input.size() - 1;

	for (int i = 0; i < input.size(); i++) {
		if (input[i].empty()) break;

		std::string line = input[i];

		for (int cInd = 0; cInd < line.size(); cInd++) {
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

	std::unordered_map<std::string, int> hashes;
	std::vector<int> currentEmpty(input[0].size(), 0);
	int size = input.size() - 1;
	int cycles = 1000000000;
	int finishIndex = 0;

	for (int i = 0; i < cycles; i++) {
		cycle(input);
		std::string hash = "";
		for (std::string chars : input) hash += chars;
		std::unordered_map<std::string, int>::const_iterator search = hashes.find(hash);

		if (search == hashes.end()) {
			hashes.try_emplace(hash, i);
			continue;
		}

		int cycleLength = i - search->second;
		cycles -= i - 1;
		finishIndex = cycles % cycleLength;
		break;
	}

	for (int i = 0; i < input.size(); i++) {
		std::vector<int> currentEmpty(input[0].size(), 0);
		std::string line = input[i];
		for (int cInd = 0; cInd < line.size(); cInd++) {
			char c = line[cInd];
			if (c == '.') continue;
			if (c == '#') {
				currentEmpty[cInd] = i + 1;
				continue;
			}
			answer += size - currentEmpty[cInd]++;
		}
	}

	std::cout << "Answer " << answer << std::endl;

	return answer;
}

void Day14::cycle(std::vector<std::string>& input) {
	for (int direction = 0; direction < 4; direction++) {
		std::vector<int> currentEmpty(input[0].size(), 0);
		for (int i = 0; i < input.size(); i++) {
			if (input[i].empty()) break;
			std::string line = input[i];
			for (int cInd = 0; cInd < line.size(); cInd++) {
				char c = line[cInd];
				if (c == '.') continue;
				if (c == '#') {
					currentEmpty[cInd] = i + 1;
					continue;
				}
				input[i][cInd] = '.';
				input[currentEmpty[cInd]][cInd] = 'O';
				currentEmpty[cInd]++;
			}
		}
		std::vector<std::vector<char>> tempInput(input[0].size(), std::vector<char>(input.size() - 1, '.'));
		for (int i = 0; i < input.size(); i++) {
			if (input[i].empty()) break;
			for (int j = 0; j < input[0].size(); j++) {
				tempInput[j][input.size() - i - 2] = input[i][j];
			}
		}

		for (int i = 0; i < tempInput.size(); i++) input[i] = std::string(tempInput[i].begin(), tempInput[i].end());
	}
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
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 64);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 14 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}