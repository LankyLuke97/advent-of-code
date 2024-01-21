#pragma once
#include <cassert>
#include <sstream>
#include <Windows.h>
#include "Day23.h"

int Day23::calculatePuzzle1(std::vector<std::string> input) {
	int answer = 0;

	int horizontalSize = input[0].size(), verticalSize = input.size() - 1;
	int start = 0, end = (verticalSize - 1) * horizontalSize;
	std::vector<char> flattened;
	std::vector<std::vector<int>> paths;

	for (std::string line : input) {
		if (line.empty()) break;

		for (char c : line) flattened.push_back(c);
	}

	for (char c : input[0]) {
		if (c == '.') break;
		start++;
	}
	for (char c : input[input.size() - 2]) {
		if (c == '.') break;
		end++;
	}

	int currentPath = 0;
	paths.push_back(std::vector<int>{start, start + horizontalSize});

	while (currentPath < paths.size()) {
		int pos = paths[currentPath].back();

		int up = pos - horizontalSize, right = pos + 1, down = pos + horizontalSize, left = pos - 1;
		if (flattened[pos] == '^') {
			if (std::find(paths[currentPath].begin(), paths[currentPath].end(), up) != paths[currentPath].end()) currentPath++;
			else paths[currentPath].push_back(up);
		} else if (flattened[pos] == '>') {
			if (std::find(paths[currentPath].begin(), paths[currentPath].end(), right) != paths[currentPath].end()) currentPath++;
			else paths[currentPath].push_back(right);
		} else if (flattened[pos] == 'v') {
			if (std::find(paths[currentPath].begin(), paths[currentPath].end(), down) != paths[currentPath].end()) currentPath++;
			else paths[currentPath].push_back(down);
		} else if (flattened[pos] == '<') {
			if (std::find(paths[currentPath].begin(), paths[currentPath].end(), left) != paths[currentPath].end()) currentPath++;
			else paths[currentPath].push_back(left);
		} else {
			int newPaths = 0;
			bool continuesUp = (flattened[up] != '#' && std::find(paths[currentPath].begin(), paths[currentPath].end(), up) == paths[currentPath].end());
			bool continuesRight = (flattened[right] != '#' && std::find(paths[currentPath].begin(), paths[currentPath].end(), right) == paths[currentPath].end());
			bool continuesDown = (down < flattened.size() && flattened[down] != '#' && std::find(paths[currentPath].begin(), paths[currentPath].end(), down) == paths[currentPath].end());
			bool continuesLeft = (flattened[left] != '#' && std::find(paths[currentPath].begin(), paths[currentPath].end(), left) == paths[currentPath].end());

			if (continuesUp) newPaths++;
			if (continuesRight) newPaths++;
			if (continuesDown) newPaths++;
			if (continuesLeft) newPaths++;

			if (newPaths == 0) {
				currentPath++;
				continue;
			}
			if (newPaths == 1) {
				if (continuesUp) paths[currentPath].push_back(up);
				if (continuesRight) paths[currentPath].push_back(right);
				if (continuesDown) paths[currentPath].push_back(down);
				if (continuesLeft) paths[currentPath].push_back(left);
				continue;
			}
			std::vector<int> pathToNow = paths[currentPath];

			if (continuesUp) {
				std::vector<int> path = pathToNow;
				path.push_back(up);
				paths.push_back(path);
			}

			if (continuesRight) {
				std::vector<int> path = pathToNow;
				path.push_back(right);
				paths.push_back(path);
			}

			if (continuesDown) {
				std::vector<int> path = pathToNow;
				path.push_back(down);
				paths.push_back(path);
			}

			if (continuesLeft) {
				std::vector<int> path = pathToNow;
				path.push_back(left);
				paths.push_back(path);
			}

			currentPath++;
		}
	}

	for (std::vector<int> path : paths) {
		if (path.back() == end && (path.size() - 1) > answer) answer = path.size() - 1;
	}

	return answer;
}

int Day23::calculatePuzzle2(std::vector<std::string> input) {
	int answer = 0;

	return answer;
}

void Day23::puzzle1() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "First puzzle: " << calculatePuzzle1(input) << std::endl;
}

void Day23::puzzle2() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "Second puzzle: " << calculatePuzzle2(input) << std::endl;
}

void Day23::test() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle1(Reader::readFile(testFile1)) == 94);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 23 part 1 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 0);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 23 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}