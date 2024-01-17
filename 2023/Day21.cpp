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
			if (c == 'S') prevPos.push_back((i * verticalSize) + j);
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

int Day21::calculatePuzzle2(std::vector<std::string> input) {
	int answer = 0;

	const int NUM_STEPS = 64;
	std::vector<int> plots;
	std::vector<std::vector<int>> currentPos(9, std::vector<int>());
	std::vector<std::vector<int>> prevPos(9, std::vector<int>());
	int horizontalSize = input[0].size(), verticalSize = input.size() - 1;
	std::vector<int> exit(12, -1);

	for (int i = 0; i < verticalSize; i++) {
		for (int j = 0; j < verticalSize; j++) {
			char c = input[i][j];
			plots.push_back(c == '#' ? 0 : 1);
			if (c == 'S') prevPos[4].push_back((i * verticalSize) + j);
		}
	}

	for (int i = 0; i < NUM_STEPS; i++) {
		for (int p = 0; p < prevPos.size(); p++) {
			for (int pos : prevPos[p]) {
				int up = pos - horizontalSize, right = pos + 1, down = pos + horizontalSize, left = pos - 1;
				if (up > -1 && plots[up] != 0 && std::find(currentPos[p].begin(), currentPos[p].end(), up) == currentPos[p].end()) currentPos[p].push_back(up);
				else if (up < 0 && p > 2 && std::find(currentPos[p - 3].begin(), currentPos[p - 3].end(), up) == currentPos[p - 3].end()) currentPos[p - 3].push_back(up + (verticalSize * horizontalSize));
				else if (up < 0 && p < 3) {
					if (p == 0 && exit[0] == -1) exit[0] = i;
					if (p == 1 && exit[1] == -1) exit[1] = i;
					if (p == 2 && exit[2] == -1) exit[2] = i;
				}

				if (right % horizontalSize != 0 && plots[right] != 0 && std::find(currentPos[p].begin(), currentPos[p].end(), right) == currentPos[p].end()) currentPos[p].push_back(right);
				else if (right % horizontalSize == 0 && p % 3 != 2 && std::find(currentPos[p + 1].begin(), currentPos[p + 1].end(), right) == currentPos[p + 1].end()) currentPos[p + 1].push_back(right + (verticalSize * horizontalSize));
				else if (right % horizontalSize == 0 && p % 3 == 2) {
					if (p == 2 && exit[4] == -1) exit[4] = i;
					if (p == 5 && exit[5] == -1) exit[5] = i;
					if (p == 8 && exit[6] == -1) exit[6] = i;
				}

				if (down < (verticalSize - 1) * horizontalSize && plots[down] != 0 && std::find(currentPos[p].begin(), currentPos[p].end(), down) == currentPos[p].end()) currentPos[p].push_back(down);
				else if (down >= (verticalSize - 1) * horizontalSize && p < 6 && std::find(currentPos[p + 3].begin(), currentPos[p + 3].end(), down) == currentPos[p + 3].end()) currentPos[p + 3].push_back(up - (verticalSize * horizontalSize));
				else if (down >= (verticalSize - 1) * horizontalSize && p > 5) {
					if (p == 6 && exit[9] == -1) exit[9] = i;
					if (p == 7 && exit[8] == -1) exit[8] = i;
					if (p == 8 && exit[7] == -1) exit[7] = i;
				}

				if (left + 1 % horizontalSize != 0 && plots[left] != 0 && std::find(currentPos[p].begin(), currentPos[p].end(), left) == currentPos[p].end()) currentPos[p].push_back(left);
				else if (left + 1 % horizontalSize == 0 && p % 3 == 0 && std::find(currentPos[p - 1].begin(), currentPos[p - 1].end(), left) == currentPos[p - 1].end()) currentPos[p - 1].push_back(right + (verticalSize * horizontalSize));
				else if (left + 1 % horizontalSize == 0 && p % 3 == 0) {
					if (p == 0 && exit[11] == -1) exit[4] = i;
					if (p == 1 && exit[10] == -1) exit[5] = i;
					if (p == 2 && exit[9] == -1) exit[6] = i;
				}
			}
		}

		prevPos = currentPos;
		for (int i = 0; i < currentPos.size(); i++) currentPos[i].clear();
	}

	for (std::vector<int> positions : prevPos) answer += positions.size();
	std::cout << answer << std::endl;

	return answer;
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
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 50);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 21 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}