#pragma once
#include <cassert>
#include <sstream>
#include <Windows.h>
#include "Day11.h"

int Day11::calculatePuzzle1(std::vector<std::string> input) {
	int answer = 0;

	std::vector<int> columnsWithout;
	std::vector<int> rowsWithout;
	std::vector<std::pair<int, int>> galaxies;

	for (int i = 0; i < input.size() - 1; i++) rowsWithout.push_back(i);
	for (int i = 0; i < input[0].size() - 1; i++) columnsWithout.push_back(i);

	int col = 0, row = 0;
	for (std::string line : input) {
		if (line.empty()) break;

		for(char c : line) {
			if (c == '#') {
				galaxies.push_back(std::make_pair(col, row));

				auto erase = std::find(columnsWithout.begin(), columnsWithout.end(), col);
				if (erase != columnsWithout.end()) columnsWithout.erase(erase);

				erase = std::find(rowsWithout.begin(), rowsWithout.end(), row);
				if (erase != rowsWithout.end()) rowsWithout.erase(erase);
			}
			col++;
		}

		col = 0, row++;
	}

	for (int i = 0; i < galaxies.size() - 1; i++) {
		for (int j = i + 1; j < galaxies.size(); j++) {
			int leftX = min(galaxies[i].first, galaxies[j].first);
			int rightX = max(galaxies[i].first, galaxies[j].first);
			int topY = min(galaxies[i].second, galaxies[j].second);
			int bottomY = max(galaxies[i].second, galaxies[j].second);
			int xExpansion = 0;
			int yExpansion = 0;

			for (int k : columnsWithout) {
				if (k < leftX) continue;
				if (k > rightX) break;
				xExpansion++;
			}

			for (int k : rowsWithout) {
				if (k < topY) continue;
				if (k > bottomY) break;
				yExpansion++;
			}

			answer += (rightX - leftX + xExpansion) + (bottomY - topY + yExpansion);
		}
	}

	return answer;
}

int Day11::calculatePuzzle2(std::vector<std::string> input) {
	int answer = 0;

	return answer;
}

void Day11::puzzle1() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "First puzzle: " << calculatePuzzle1(input) << std::endl;
}

void Day11::puzzle2() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "Second puzzle: " << calculatePuzzle2(input) << std::endl;
}

void Day11::test() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	assert(calculatePuzzle1(Reader::readFile(testFile1)) == 374);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 11 part 1 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 0);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 11 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}