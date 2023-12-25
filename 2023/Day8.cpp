#pragma once
#include <cassert>
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
	while(true) {
		answer++;
		char direction = *it++;
		if (direction == 'L') currentNode = map[currentNode].first;
		else currentNode = map[currentNode].second;
		if (currentNode == "ZZZ") break;
		if (it == directions.end())it = directions.begin();
	}

	return answer;
}

int Day8::calculatePuzzle2(std::vector<std::string> input) {
	int answer = 0;

	
	return answer;
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
	assert(calculatePuzzle1(Reader::readFile(testFile1)) == 6);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 8 part 1 test passed" << std::endl;
	SetConsoleTextAttribute(h, 8);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 0);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 8 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 8);
}