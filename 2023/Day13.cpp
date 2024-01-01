#pragma once
#include <cassert>
#include <sstream>
#include <Windows.h>
#include "Day13.h"

int Day13::calculatePuzzle1(std::vector<std::string> input) {
	int answer = 0;

	std::vector<int> columnHashes, rowHashes;
	int row = 0;
	int lineNum = 0;
	for (std::string line : input) {
		if(line.empty()) {
			bool reflected = true;
			for (int i = 1; i < columnHashes.size() - 1; i++) {
				reflected = true;
				for (int j = 0; j <= i; j++) {
					int r = (i * 2) - j - 1;
					if(r >= columnHashes.size()) continue;
					if (columnHashes[j] != columnHashes[r]) {
						reflected = false;
						break;
					}
				}

				if (reflected) {
					answer += i;
					break;
				}
			}

			if (!reflected) {
				for (int i = 1; i < rowHashes.size() - 1; i++) {
					reflected = true;
					for (int j = 0; j <= i; j++) {
						int r = (i * 2) - j - 1;
						if (r >= rowHashes.size()) continue;
						if (rowHashes[j] != rowHashes[r]) {
							reflected = false;
							break;
						}
					}

					if (reflected) {
						answer += (i * 100);
						break;
					}
				}
			}

			if (!reflected) {
				std::cout << lineNum << std::endl;
			}

			columnHashes.clear();
			rowHashes.clear();
			row = 0;
			continue;
		}

		for (int i = 0; i < line.size(); i++) {
			if (i >= columnHashes.size()) columnHashes.push_back(0);
			if (row >= rowHashes.size()) rowHashes.push_back(0);
			int hash = line[i] == '#' ? 2 : 1;
			columnHashes[i] = (columnHashes[i] << 1) + hash;
			rowHashes[row] = (rowHashes[row] << 1) + hash;
		}
		row++;
		lineNum++;
	}

	return answer;
}

int Day13::calculatePuzzle2(std::vector<std::string> input) {
	int answer = 0;

	return answer;
}

void Day13::puzzle1() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "First puzzle: " << calculatePuzzle1(input) << std::endl;
}

void Day13::puzzle2() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "Second puzzle: " << calculatePuzzle2(input) << std::endl;
}

void Day13::test() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle1(Reader::readFile(testFile1)) == 405);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 13 part 1 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 0);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 13 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}