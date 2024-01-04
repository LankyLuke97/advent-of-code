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

int64_t Day13::calculatePuzzle2(std::vector<std::string> input) {
	int64_t answer = 0;

	std::vector<int64_t> columnHashes, rowHashes;
	int64_t row = 0;
	int pattern = 0;
	int empties = 0;

	for (std::string line : input) {
		// std::cout << "Processing line " << line << std::endl;
		if (line.empty()) {
			// std::cout << "COLS: ";
			// for (int64_t c : columnHashes) // std::cout << c << ", ";
			// std::cout << std::endl;
			// std::cout << "ROWS: ";
			// for (int64_t r : rowHashes) // std::cout << r << ", ";
			// std::cout << std::endl;

			// std::cout << ++empties << " empties" << std::endl;
			bool reflected = true;
			bool smudgeCorrected = true;
			for (int64_t i = 1; i < rowHashes.size(); i++) {
				// std::cout << "CHECKING ROWS" << std::endl;
				reflected = true;
				smudgeCorrected = false;
				for (int64_t j = 0; j < i; j++) {
					int64_t r = (i * 2) - j - 1;
					if (r >= rowHashes.size()) continue;
					// std::cout << "COMPARING " << j << " WITH " << r << std::endl;
					if(rowHashes[j] != rowHashes[r]) {
						// std::cout << "DIFFERENCE BETWEEN " << j << " AND " << r << ": " << (rowHashes[j] - rowHashes[r]) << std::endl;
						if (smudgeCorrected) {
							// std::cout << "WOULD BE SMUDGE ROW " << j << ", " << r << std::endl;
							reflected = false;
							break;
						}

						int64_t s = 1;
						for (int64_t smudgeShift = 0; smudgeShift < 32; smudgeShift++) {
							// std::cout << "S here : " << s << std::endl;
							if (rowHashes[j] - s == rowHashes[r] || rowHashes[j] + s == rowHashes[r]) {
								// std::cout << "SMUDGE ROW " << j << ", " << r << ": " << s << std::endl;
								smudgeCorrected = true;
							}
							if (smudgeCorrected) break;
							s *= 2;
						}


						if (!smudgeCorrected) {
							reflected = false;
							break;
						}
					}
				}

				if (reflected && smudgeCorrected) {
					answer += i * 100;
					std::cout << ++pattern << ". Reflection along row " << (i*100) << std::endl;
					break;
				} else reflected = false;
			}

			if (!reflected) {
				// std::cout << "CHECKING COLUMNS" << std::endl;
				for (int64_t i = 1; i < columnHashes.size(); i++) {
					reflected = true;
					smudgeCorrected = false;
					for (int64_t j = 0; j < i; j++) {
						int64_t r = (i * 2) - j - 1;
						if (r >= columnHashes.size()) continue;
						// std::cout << "COMPARING " << j << " WITH " << r << std::endl;
						if (columnHashes[j] != columnHashes[r]) {
							// std::cout << "DIFFERENCE BETWEEN " << j << " AND " << r << ": " << (columnHashes[j] - columnHashes[r]) << std::endl;
							if (smudgeCorrected) {
								// std::cout << "WOULD BE SMUDGE COLUMN " << j << ", " << r << std::endl;
								reflected = false;
								break;
							}

							int64_t s = 1;
							for (int64_t smudgeShift = 0; smudgeShift < 32; smudgeShift++) {

								// std::cout << "S here : " << s << std::endl;
								if (columnHashes[j] - s == columnHashes[r] || columnHashes[j] + s == columnHashes[r]) {
									// std::cout << "SMUDGE COLUMN " << j << ", " << r << ": " << s << std::endl;
									smudgeCorrected = true;
								}
								if (smudgeCorrected) break;
								s *= 2;
							}

							if (!smudgeCorrected) {
								reflected = false;
								break;
							}
						}
					}

					if (reflected && smudgeCorrected) {
						answer += (i * 1);
						std::cout << ++pattern << ". Reflection along column " << i << std::endl;
						break;
					}
				}
			}

			columnHashes.clear();
			rowHashes.clear();
			row = 0;
			continue;
		}

		for (int64_t i = 0; i < line.size(); i++) {
			if (i >= columnHashes.size()) columnHashes.push_back(1);
			if (row >= rowHashes.size()) rowHashes.push_back(1);
			int64_t hash = line[i] == '#' ? 1 : 0;
			columnHashes[i] = (columnHashes[i] * 2) + hash;
			rowHashes[row] = (rowHashes[row] * 2) + hash;
		}

		row++;
	}

	// std::cout << "ANSWER: " << answer << std::endl;

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