#pragma once
#include <cassert>
#include <sstream>
#include <unordered_map>
#include <Windows.h>
#include "Day5.h"

int Day5::calculatePuzzle1(std::vector<std::string> input) {
	/* 
	* 0: seed to soil
	* 1: soil to fertiliser
	* 2: fertiliser to water
	* 3: water to light
	* 4: light to temperature
	* 5: temperature to humidity
	* 6: humidity to location
	*/
	std::vector<std::vector<std::vector<int64_t>>> mappings(7);
	std::vector<int64_t> seeds;
	std::istringstream seedsStream(input[0]);
	std::string token;
	seedsStream >> token;

	while(seedsStream >> token) {
		seeds.push_back(std::stoll(token));
	}

	int currentMapping = -1;

	for (int i = 1; i < input.size() - 1; i++) {
		std::string line = input[i];
		if(line.empty()) continue;

		std::istringstream iss(line);

		int64_t start = -1, mapping = -1, range = -1;

		while(iss >> token) {
			try {
				int64_t num = std::stoll(token);

				if (mapping == -1) mapping = num;
				else if (start == -1) start = num;
				else range = num;

				if (start == -1 || mapping == -1 || range == -1) continue;

				mappings[currentMapping].push_back(std::vector<int64_t>{start, mapping, range});
			} catch (std::invalid_argument const& ex) {
				currentMapping++;
				break;
			}
		}
	}

	int64_t closestLocation = LLONG_MAX;

	for (int64_t seed : seeds) {
		int64_t location = seed;
		for(int i = 0; i < mappings.size(); i++) {
			for(int j = 0; j < mappings[i].size(); j++) {
				int64_t start = mappings[i][j][0], mapping = mappings[i][j][1], range = mappings[i][j][2];
				if(location < start) continue;
				if(location >= start + range) continue;
				location = (location - start) + mapping;
				break;
			}
		}
		if(location < closestLocation) closestLocation = location;
	}

	return closestLocation;
}

int Day5::calculatePuzzle2(std::vector<std::string> input) {
	/*
	* 0: seed to soil
	* 1: soil to fertiliser
	* 2: fertiliser to water
	* 3: water to light
	* 4: light to temperature
	* 5: temperature to humidity
	* 6: humidity to location
	*/
	std::vector<std::vector<std::vector<int64_t>>> mappings(7);
	std::istringstream seedsStream(input[0]);
	std::string token;
	seedsStream >> token;

	int currentMapping = -1;

	for (int i = 1; i < input.size() - 1; i++) {
		std::string line = input[i];
		if (line.empty()) continue;

		std::istringstream iss(line);

		int64_t start = -1, mapping = -1, range = -1;

		while (iss >> token) {
			try {
				int64_t num = std::stoll(token);

				if (mapping == -1) mapping = num;
				else if (start == -1) start = num;
				else range = num;

				if (start == -1 || mapping == -1 || range == -1) continue;

				mappings[currentMapping].push_back(std::vector<int64_t>{start, mapping, range});
			}
			catch (std::invalid_argument const& ex) {
				currentMapping++;
				break;
			}
		}
	}

	int64_t closestLocation = LLONG_MAX;

	bool range = false;
	int64_t start = -1;
	while (seedsStream >> token) {
		int64_t inp = std::stoll(token);

		if (start == -1) {
			start = inp;
			continue;
		}
		else range = true;

		if (!range) continue;

		for (int64_t i = 0; i < inp; i++) {
			int64_t location = start + i;
			for (int i = 0; i < mappings.size(); i++) {
				for (int j = 0; j < mappings[i].size(); j++) {
					int64_t start = mappings[i][j][0], mapping = mappings[i][j][1], range = mappings[i][j][2];
					if (location < start) continue;
					if (location >= start + range) continue;
					location = (location - start) + mapping;
					break;
				}
			}
			if (location < closestLocation) closestLocation = location;
		}		
			
		range = false;
		start = -1;
	}

	return closestLocation;
}


void Day5::puzzle1() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "First puzzle: " << calculatePuzzle1(input) << std::endl;
}

void Day5::puzzle2() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "Second puzzle: " << calculatePuzzle2(input) << std::endl;
}

void Day5::test() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	assert(calculatePuzzle1(Reader::readFile(testFile1)) == 35);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 5 part 1 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 46);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 5 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}