#pragma once
#include <algorithm>
#include <cassert>
#include <sstream>
#include <unordered_map>
#include <Windows.h>
#include "Day22.h"

int Day22::calculatePuzzle1(std::vector<std::string> input) {
	int answer = 0;

	std::unordered_map<int, Brick> bricks;
	std::vector<Brick> orderedBricks;
	int minX = INT_MAX, maxX = INT_MIN, minY = INT_MAX, maxY = INT_MIN;
	int id = 0;

	for (std::string line : input) {
		if (line.empty()) break;
		std::replace(line.begin(), line.end(), ',', ' ');
		std::replace(line.begin(), line.end(), '~', ' ');

		std::istringstream iss(line);
		std::string token;
		std::vector<int> vals;
		while (iss >> token) {
			vals.push_back(std::stoi(token));
		}

		Brick brick(id++, min(vals[0], vals[3]), max(vals[0], vals[3]), min(vals[1], vals[4]), max(vals[1], vals[4]), min(vals[2], vals[5]), max(vals[2], vals[5]));
		orderedBricks.push_back(brick);
		if (brick.x1 < minX) minX = brick.x1;
		if (brick.x2 > maxX) maxX = brick.x2;
		if (brick.y1 < minY) minY = brick.y1;
		if (brick.y2 > maxY) maxY = brick.y2;
	}
	std::sort(orderedBricks.begin(), orderedBricks.end());

	std::vector<std::pair<int, int>> map((maxX - minX) * (maxY - minY), std::make_pair(-1, 0));

	for (int b = 0; b < orderedBricks.size(); b++) {
		Brick brick = orderedBricks[b];
		int maxHeight = -1;
		for (int i = brick.x1; i < brick.x2; i++) {
			for (int j = brick.y1; j < brick.y2; j++) {
				std::pair<int, int> mLoc = map[i * (maxY - minY) + j];
				if (mLoc.second < maxHeight) continue;
				if (mLoc.second == maxHeight && std::find(brick.balancedOn.begin(), brick.balancedOn.end(), mLoc.first) == brick.balancedOn.end()) brick.balancedOn.push_back(mLoc.first);
				if (mLoc.second > maxHeight) {
					maxHeight = mLoc.second;
					brick.balancedOn.clear();
					brick.balancedOn.push_back(mLoc.first);
				}
			}
		}

		int newHeight = maxHeight + brick.z2 - brick.z1;

		for (int i = 0; i < brick.x2 - brick.x1; i++) {
			for (int j = 0; j < brick.y2 - brick.y1; j++) {
				map[(i + brick.x1) * (maxY - minY) + (j + brick.y1)] = std::make_pair(brick.id, newHeight);
			}
		}

		orderedBricks[b] = brick;
		bricks.emplace(brick.id, brick);
	}

	for (auto it = bricks.begin(); it != bricks.end(); ++it) {
		Brick& brick = it->second;
		if (brick.balancedOn.size() == 1 && brick.balancedOn[0] != -1) bricks[brick.balancedOn[0]].canDisintegrate = false;
	}

	for (auto kv : bricks) if (kv.second.canDisintegrate) answer++;

	return answer;
}

int Day22::calculatePuzzle2(std::vector<std::string> input) {
	int answer = 0;

	return answer;
}

void Day22::puzzle1() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "First puzzle: " << calculatePuzzle1(input) << std::endl;
}

void Day22::puzzle2() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "Second puzzle: " << calculatePuzzle2(input) << std::endl;
}

void Day22::test() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle1(Reader::readFile(testFile1)) == 5);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 22 part 1 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 0);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 22 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}