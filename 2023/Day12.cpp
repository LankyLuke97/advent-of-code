#pragma once
#include <algorithm>
#include <cassert>
#include <sstream>
#include <Windows.h>
#include "Day12.h"

int Day12::calculatePuzzle1(std::vector<std::string> input) {
	int answer = 0;

	std::vector<int> contiguous;

	for (std::string line : input) {
		if (line.empty()) break;

		contiguous.clear();
		std::replace(line.begin(), line.end(), ',', ' ');
		std::istringstream iss(line);
		std::string data;
		std::string token;

		iss >> data;

		while (iss >> token) contiguous.push_back(std::stoi(token));
		std::vector<std::vector<char>> prevArrangements;

		if (data[0] == '.') prevArrangements.push_back({ '.' });
		else if (data[0] == '#') prevArrangements.push_back({ '#' });
		else {
			prevArrangements.push_back({ '.' });
			prevArrangements.push_back({ '#' });
		}

		std::vector<std::vector<char>> arrangements;

		for (int i = 1; i < data.size(); i++) {
			char c = data[i];
			arrangements.clear();

			for (std::vector<char> prev : prevArrangements) {
				int currentContiguous = 0;
				int contiguousIndex = -1;
				bool brokenBlock = false;

				for (char prevC : prev) {
					if (prevC == '.') {
						if (!brokenBlock) continue;
						currentContiguous = 0;
						brokenBlock = false;
					}
					else {
						if (!brokenBlock) {
							contiguousIndex++;
							brokenBlock = true;
						}
						currentContiguous++;
					}
				}

				if (c == '.' || c == '?') {
					std::vector<char> newArrangement = prev;
					newArrangement.push_back('.');
					if (!brokenBlock) arrangements.push_back(newArrangement);
					else if (currentContiguous == contiguous[contiguousIndex]) arrangements.push_back(newArrangement);
				}

				if (c == '#' || c == '?') {
					std::vector<char> newArrangement = prev;
					newArrangement.push_back('#');
					if (!brokenBlock) {
						if (++contiguousIndex < contiguous.size()) arrangements.push_back(newArrangement);
					}
					else if (++currentContiguous <= contiguous[contiguousIndex]) arrangements.push_back(newArrangement);
				}
			}

			prevArrangements = arrangements;
		}

		for (std::vector<char> arrangement : arrangements) {
			int currentContiguous = 0;
			int contiguousIndex = -1;
			int lastContiguous = 0;
			bool brokenBlock = false;

			for (char c : arrangement) {
				if (c == '.') {
					if (!brokenBlock) continue;
					currentContiguous = 0;
					brokenBlock = false;
				}
				else {
					if (!brokenBlock) {
						contiguousIndex++;
						brokenBlock = true;
					}
					currentContiguous++;
					lastContiguous = currentContiguous;
				}
			}

			if (contiguousIndex == contiguous.size() - 1 && lastContiguous == *(contiguous.end() - 1)) answer++;
		}
	}

	return answer;
}

int Day12::calculatePuzzle2(std::vector<std::string> input) {
	int64_t answer = 0;

	return answer;
}

void Day12::puzzle1() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "First puzzle: " << calculatePuzzle1(input) << std::endl;
}

void Day12::puzzle2() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "Second puzzle: " << calculatePuzzle2(input) << std::endl;
}

void Day12::test() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); 
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle1(Reader::readFile(testFile1)) == 21);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 12 part 1 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 0);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 12 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}