#pragma once
#include <cassert>
#include <sstream>
#include <Windows.h>
#include "Day13.h"

int Day13::calculatePuzzle1(std::vector<std::string> input) {
	int answer = 0;

	std::vector<int> columnHashes, rowHashes;
	int row = 0;

	for (std::string line : input) {
		if(line.empty()) {
			bool reflected = true;
			
			for (int i = 1; i < columnHashes.size(); i++) {
				reflected = true;
				for (int j = 0; j <= i; j++) {
					int r = (i * 2) - j - 1;
					if (r >= columnHashes.size()) continue;
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
				for (int i = 1; i < rowHashes.size(); i++) {
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
	}

	return answer;
}

int Day13::calculatePuzzle2(std::vector<std::string> input) {
	int answer = 0;

	std::vector<int> columnHashes, rowHashes;
	int row = 0;

	for (std::string line : input) {
		if (line.empty()) {
			bool reflected = true;

			std::cout << "COLS: ";
			for (int c : columnHashes) std::cout << c << ", ";
			std::cout << std::endl;
			std::cout << "ROWS: ";
			for (int r : rowHashes) std::cout << r << ", ";
			std::cout << std::endl;

			bool smudgeCorrected = true;
			for (int i = 1; i < columnHashes.size(); i++) {
				std::cout << "CHECKING " << i << std::endl;
				reflected = true;
				smudgeCorrected = false;
				for (int j = 0; j <= i; j++) {
					int r = (i * 2) - j - 1;
					if (r >= columnHashes.size()) continue;
					if (columnHashes[j] != columnHashes[r]) {
						if (smudgeCorrected) {
							std::cout << columnHashes[j] << " (colHash[" << j << "]) differs from " << columnHashes[r] << " (colHash[" << r << "]) but already corrected a smudge this selection." << std::endl;
							reflected = false;
							break;
						}

						int s = 0;
						for (int smudgeShift = 0; smudgeShift < columnHashes.size(); smudgeShift++) {
							s = 1 << smudgeShift;
							if (columnHashes[j] - s == columnHashes[r] || columnHashes[j] + s == columnHashes[r]) {
								smudgeCorrected = true;
								std::cout << columnHashes[j] << " (colHash[" << j << "]) differs from " << columnHashes[r] << " (colHash[" << r << "]) by " << s << std::endl;
							}
						}
					}
				}

				if (reflected && smudgeCorrected) {
					answer += i;
					std::cout << "Reflection down column " << i << std::endl;
					break;
				}
			}

			if (!reflected) {
				for (int i = 1; i < rowHashes.size(); i++) {
					reflected = true;
					smudgeCorrected = false;
					for (int j = 0; j <= i; j++) {
						int r = (i * 2) - j - 1;
						if (r >= rowHashes.size()) continue;
						if (rowHashes[j] != rowHashes[r]) {
							if (smudgeCorrected) {
								std::cout << rowHashes[j] << " (rowHash[" << j << "]) differs from " << rowHashes[r] << " (rowHash[" << r << "]) but already corrected a smudge this selection." << std::endl;
								reflected = false;
								break;
							}

							int s = 0;
							for (int smudgeShift = 0; smudgeShift < rowHashes.size(); smudgeShift++) {
								s = 1 << smudgeShift;
								if (rowHashes[j] - s == rowHashes[r] || rowHashes[j] + s == rowHashes[r]) {
									smudgeCorrected = true;
									std::cout << rowHashes[j] << " (rowHash[" << j << "]) differs from " << rowHashes[r] << " (rowHash[" << r << "]) by " << s << std::endl;
								}
							}
						}
					}

					if (reflected) {
						answer += (i * 100);
						std::cout << "Reflection along row " << i << std::endl;
						break;
					}
				}
			}

			columnHashes.clear();
			rowHashes.clear();
			row = 0;
			continue;
		}

		for (int i = 0; i < line.size(); i++) {
			if (i >= columnHashes.size()) columnHashes.push_back(1);
			if (row >= rowHashes.size()) rowHashes.push_back(1);
			int hash = line[i] == '#' ? 1 : 0;
			columnHashes[i] = (columnHashes[i] << hash) + 1;
			rowHashes[row] = (rowHashes[row] << 1) + hash;
		}
		row++;
	}

	std::cout << "ANSWER: " << answer << std::endl;

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
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 400);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 13 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}