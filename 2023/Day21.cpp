#pragma once
#include <cassert>
#include <sstream>
#include <Windows.h>
#include "Day21.h"

int Day21::calculatePuzzle1(std::vector<std::string> input) {
	int answer = 0;

	const int NUM_STEPS = 64;
	std::vector<int> plots;
	std::vector<int> currentPos;
	std::vector<int> prevPos;
	int horizontalSize = input[0].size(), verticalSize = input.size() - 1;

	for (int i = 0; i < verticalSize; i++) {
		for (int j = 0; j < verticalSize; j++) {
			char c = input[i][j];
			plots.push_back(c == '#' ? 0 : 1);
			if (c == 'S') prevPos.push_back(i * horizontalSize + j);
		}
	}

	for (int i = 0; i < NUM_STEPS; i++) {
		for (int pos : prevPos) {
			int up = pos - horizontalSize, right = pos + 1, down = pos + horizontalSize, left = pos - 1;
			if (up > -1 && plots[up] != 0 && std::find(currentPos.begin(), currentPos.end(), up) == currentPos.end()) currentPos.push_back(up);
			if (right % horizontalSize != 0 && plots[right] != 0 && std::find(currentPos.begin(), currentPos.end(), right) == currentPos.end()) currentPos.push_back(right);
			if (down < (verticalSize - 1) * horizontalSize && plots[down] != 0 && std::find(currentPos.begin(), currentPos.end(), down) == currentPos.end()) currentPos.push_back(down);
			if (left + 1 % horizontalSize != 0 && plots[left] != 0 && std::find(currentPos.begin(), currentPos.end(), left) == currentPos.end()) currentPos.push_back(left);
		}

		prevPos = currentPos;
		currentPos.clear();
	}

	return prevPos.size();
}

uint64_t Day21::calculatePuzzle2(std::vector<std::string> input) {
	int answer = 0;

	const std::vector<int> NUM_STEPS {65, 196, 327, 64};
	const int MULT = 7;
	std::vector<int> plots;
	std::vector<int> currentPos;
	std::vector<int> prevPos;
	int horizontalSize = input[0].size() * MULT, verticalSize = (input.size() - 1) * MULT;

	for (int k1 = 0; k1 < MULT; k1++) {
		for (int i = 0; i < 131; i++) {
			for (int k2 = 0; k2 < MULT; k2++) {
				for (int j = 0; j < 131; j++) {
					char c = input[i][j];
					plots.push_back(c == '#' ? 0 : 1);
				}
			}
		}
	}

	std::vector<int> values;
	for (int n : NUM_STEPS) {
		prevPos.clear();
		prevPos.push_back(plots.size() / 2);
		currentPos.clear();
		for (int i = 0; i < n; i++) {
			for (int pos : prevPos) {
				int up = pos - horizontalSize, right = pos + 1, down = pos + horizontalSize, left = pos - 1;
				if (up > -1 && plots[up] != 0 && std::find(currentPos.begin(), currentPos.end(), up) == currentPos.end()) currentPos.push_back(up);
				if (right % horizontalSize != 0 && plots[right] != 0 && std::find(currentPos.begin(), currentPos.end(), right) == currentPos.end()) currentPos.push_back(right);
				if (down < (verticalSize - 1) * horizontalSize && plots[down] != 0 && std::find(currentPos.begin(), currentPos.end(), down) == currentPos.end()) currentPos.push_back(down);
				if (left + 1 % horizontalSize != 0 && plots[left] != 0 && std::find(currentPos.begin(), currentPos.end(), left) == currentPos.end()) currentPos.push_back(left);
			}

			prevPos = currentPos;
			currentPos.clear();
		}

		values.push_back(prevPos.size());
	}
	
	int halfStepsHorizontal = (input[0].size() - 1) / 2, halfStepsVertical = (input.size() - 1) / 2;
	uint64_t n = (26501365 - halfStepsHorizontal) / input[0].size();

	//Lagrange interpolation (I guess?)
	int a = values[0] / 2 - values[1] + values[2] / 2;
	int b = -3 * (values[0] / 2) + 2 * values[1] - values[2] / 2;
	int c = values[0];

	return (uint64_t(a) * n * n) + (uint64_t(b) * n) + uint64_t(c);
}

void Day21::puzzle1() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "First puzzle: " << calculatePuzzle1(input) << std::endl;
}

void Day21::puzzle2() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "Second puzzle: " << calculatePuzzle2(input) << std::endl;
}

void Day21::test() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle1(Reader::readFile(testFile1)) == 35);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 21 part 1 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 0);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 21 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}