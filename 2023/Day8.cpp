#pragma once
#include <cassert>
#include <numeric>
#include <sstream>
#include <unordered_map>
#include <Windows.h>
#include "Day8.h"

int Day8::calculatePuzzle1(std::vector<std::string> input) {
	int answer = 0;

	std::string directions = input[0];
	std::unordered_map<std::string, std::pair<std::string, std::string>> map;
	std::string key, left, right;

	for(int i = 2; i < input.size(); i++) {
		std::string line = input[i];
		if (line.empty()) break;
		line.erase(std::remove(line.begin(), line.end(), ','));
		line.erase(std::remove(line.begin(), line.end(), '='));
		line.erase(std::remove(line.begin(), line.end(), '('));
		line.erase(std::remove(line.begin(), line.end(), ')'));
		
		std::istringstream iss(line);
		while (iss >> key) {
			iss >> left;
			iss >> right;

			map.try_emplace(key, std::make_pair(left, right));
		}
	}

	auto it = directions.begin();
	std::string currentNode = "AAA";
	while (true) {
		answer++;
		char direction = *it++;
		if (direction == 'L') currentNode = map[currentNode].first;
		else currentNode = map[currentNode].second;
		if (currentNode == "ZZZ") break;
		if (it == directions.end())it = directions.begin();
	}

	return answer;
}

int64_t Day8::calculatePuzzle2(std::vector<std::string> input) {
	int64_t answer = 0;

	std::string directions = input[0];
	std::unordered_map<std::string, std::pair<std::string, std::string>> map;
	std::vector<int> cycleDistances;
	std::vector<std::string> startingNodes;
	std::string key, left, right;

	for (int i = 2; i < input.size(); i++) {
		std::string line = input[i];
		if (line.empty()) break;
		line.erase(std::remove(line.begin(), line.end(), ','));
		line.erase(std::remove(line.begin(), line.end(), '='));
		line.erase(std::remove(line.begin(), line.end(), '('));
		line.erase(std::remove(line.begin(), line.end(), ')'));

		std::istringstream iss(line);
		while (iss >> key) {
			iss >> left;
			iss >> right;

			map.try_emplace(key, std::make_pair(left, right));
			if (*(key.end() - 1) == 'A') startingNodes.push_back(key);
		}
	}

	for(std::string node : startingNodes) {
		auto it = directions.begin();
		std::string currentNode = node;
		int steps = 0;
		while (true) {
			steps++;
			char direction = *it++;
			if (direction == 'L') currentNode = map[currentNode].first;
			else currentNode = map[currentNode].second;
			if (*(currentNode.end() - 1) == 'Z') break;
			if (it == directions.end())it = directions.begin();
		}

		cycleDistances.push_back(steps);
	}

	answer = 1;

	for(int dist : cycleDistances) {
		answer = lcm(answer, dist);
	}

	return answer;
}

int64_t Day8::lcm(int64_t x, int64_t y) {
	int64_t i, temp, l, s;
	if (x > y) {
		temp = x;
		x = y;
		y = temp;
	}

	l = y;
	s = x;
	i = l;

	while (true) {
		if (i % s == 0)
			return i;
		i = i + l;
	}
}


void Day8::puzzle1() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "First puzzle: " << calculatePuzzle1(input) << std::endl;
}

void Day8::puzzle2() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "Second puzzle: " << calculatePuzzle2(input) << std::endl;
}

void Day8::test() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle1(Reader::readFile(testFile1)) == 6);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 8 part 1 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 6);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 8 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}