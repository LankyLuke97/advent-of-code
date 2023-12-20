#pragma once
#include <cassert>
#include <sstream>
#include <unordered_map>
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
	std::vector<std::unordered_map<int64_t, int64_t>> mappings(7, std::unordered_map<int64_t, int64_t>());
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
				int64_t num = std::stol(token);

				if (mapping == -1) mapping = num;
				else if (start == -1) start = num;
				else range = num;

				if (start == -1 || mapping == -1 || range == -1) continue;

				for (int64_t j = 0; j < range; j++) {
					mappings[currentMapping].emplace(start + j, mapping + j);
				}
			} catch (std::invalid_argument const& ex) {
				currentMapping++;
				break;
			}
		}
	}

	int64_t closestLocation = LLONG_MAX;

	for (int64_t seed : seeds) {
		int64_t location = -1;
		auto search = mappings[0].find(seed);
		if(search != mappings[0].end()) {
			location = search->second;
		} else {
			location = seed;
		}

		for(int i = 1; i < mappings.size() - 1; i++) {
			auto search = mappings[i].find(location);

			if (search != mappings[i].end()) location = search->second;
		}
		if(location < closestLocation) closestLocation = location;
	}

	return closestLocation;
}

int Day5::calculatePuzzle2(std::vector<std::string> input) {
	int answer = 0;

	return answer;
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
	assert(calculatePuzzle1(Reader::readFile(testFile1)) == 35);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 0);
}