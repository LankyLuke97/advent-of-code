#pragma once
#include <cassert>
#include <sstream>
#include <Windows.h>
#include "Day18.h"

int Day18::calculatePuzzle1(std::vector<std::string> input) {
	int answer = 0;

	std::vector<std::pair<int, int>> coordinates{ std::make_pair(0,0) };

	for (std::string line : input) {
		if (line.empty()) break;

		std::istringstream iss(line);
		std::string token;
		iss >> token;
		int direction = -1;

		switch (token[0]) {
		case 'U':
			direction = 0;
			break;
		case 'R':
			direction = 1;
			break;
		case 'D':
			direction = 2;
			break;
		case 'L':
			direction = 3;
			break;
		}

		iss >> token;

		int dist = std::stoi(token);
		std::pair<int, int> lastCoords = coordinates.back();
		switch (direction) {
		case 0:
			coordinates.push_back(std::make_pair(lastCoords.first, lastCoords.second - dist));
			break;
		case 1:
			coordinates.push_back(std::make_pair(lastCoords.first + dist, lastCoords.second));
			break;
		case 2:
			coordinates.push_back(std::make_pair(lastCoords.first, lastCoords.second + dist));
			break;
		case 3:
			coordinates.push_back(std::make_pair(lastCoords.first - dist, lastCoords.second));
			break;
		}

		answer += dist; // Adding all perimiters to the area
	}

	int j = 0;
	for (int i = coordinates.size() - 2; i > -1; i--) {
		answer += (coordinates[j].first + coordinates[i].first) * (coordinates[j].second - coordinates[i].second); // Shoelace formula/algorithm for the area
		j = i;
	}

	return (answer / 2) + 1; 
	// This +1 was dumb luck from me, but is part of Pick's Theorem
	// A = i + b / 2 + 1. We've calculated internal points (i) using
	// the shoelace forumala, added the boundary (both need to be divided
	// by 2 so that's done at the end, then add 1. I did not know this,
	// I just saw that my test was 1 out, added 1, it worked for the 
	// main problem. Sometimes, Lady Luck is feeling generous.
}

int Day18::calculatePuzzle2(std::vector<std::string> input) {
	int answer = 0;

	return answer;
}

void Day18::puzzle1() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "First puzzle: " << calculatePuzzle1(input) << std::endl;
}

void Day18::puzzle2() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "Second puzzle: " << calculatePuzzle2(input) << std::endl;
}

void Day18::test() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle1(Reader::readFile(testFile1)) == 62);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 18 part 1 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 0);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 18 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}