#pragma once
#include <cassert>
#include <regex>
#include <sstream>
#include <unordered_map>
#include <Windows.h>
#include "Day3.h"

int Day3::calculatePuzzle1(std::vector<std::string> input) {
	int answer = 0;

	int lineLength = input[0].size();
	std::unordered_map<int, int> numberPositions;
	std::unordered_map<int, int> numberMappings;
	std::vector<int> partSignifyingPositions;
	std::regex specialCharExpr("([^0-9\.])");
	std::regex digitExpr("(\\d+)");
	
	for (int lineNum = 0; lineNum < input.size(); lineNum++) {
		std::string line = input[lineNum];
		if(line.empty()) break;

		std::match_results<std::string::const_iterator> results;

		for(std::sregex_iterator it(line.begin(), line.end(), specialCharExpr); it != std::sregex_iterator(); ++it) {
			partSignifyingPositions.push_back(it->position() + (lineNum * lineLength));
		}

		for(std::sregex_iterator it(line.begin(), line.end(), digitExpr); it != std::sregex_iterator(); ++it) {
			int startPos = it->position();
			numberPositions.emplace(startPos + (lineNum * lineLength), std::stoi(it->str()));

			for(int posInd = 0; posInd < it->str().size(); posInd++) {
				numberMappings.emplace(startPos + posInd + (lineNum * lineLength), startPos + (lineNum * lineLength));
			}
		}
	}

	for(int partPos : partSignifyingPositions) {
		std::vector<int> offsets = { -lineLength - 1, -lineLength, -lineLength + 1, -1, 1, lineLength - 1, lineLength, lineLength + 1 };

		for (int offset : offsets) {
			auto mappingsSearch = numberMappings.find(partPos + offset);
			if(mappingsSearch == numberMappings.end()) continue;
			auto partSearch = numberPositions.find(mappingsSearch->second);
			if(partSearch == numberPositions.end()) continue;
			answer += partSearch->second;
			numberMappings.erase(mappingsSearch);
			numberPositions.erase(partSearch);
		}
	}

	return answer;
}

int Day3::calculatePuzzle2(std::vector<std::string> input) {
	int answer = 0;

	int lineLength = input[0].size();
	std::unordered_map<int, int> numberPositions;
	std::unordered_map<int, int> numberMappings;
	std::vector<int> partSignifyingPositions;
	std::regex specialCharExpr("(\\*)");
	std::regex digitExpr("(\\d+)");

	for (int lineNum = 0; lineNum < input.size(); lineNum++) {
		std::string line = input[lineNum];
		if (line.empty()) break;

		std::match_results<std::string::const_iterator> results;

		for (std::sregex_iterator it(line.begin(), line.end(), specialCharExpr); it != std::sregex_iterator(); ++it) {
			partSignifyingPositions.push_back(it->position() + (lineNum * lineLength));
		}

		for (std::sregex_iterator it(line.begin(), line.end(), digitExpr); it != std::sregex_iterator(); ++it) {
			int startPos = it->position();
			numberPositions.emplace(startPos + (lineNum * lineLength), std::stoi(it->str()));

			for (int posInd = 0; posInd < it->str().size(); posInd++) {
				numberMappings.emplace(startPos + posInd + (lineNum * lineLength), startPos + (lineNum * lineLength));
			}
		}
	}

	for (int partPos : partSignifyingPositions) {
		std::vector<int> offsets = { -lineLength - 1, -lineLength, -lineLength + 1, -1, 1, lineLength - 1, lineLength, lineLength + 1 };
		std::vector<int> adjacentParts;

		for (int offset : offsets) {
			auto mappingsSearch = numberMappings.find(partPos + offset);
			if (mappingsSearch == numberMappings.end()) continue;
			auto partSearch = numberPositions.find(mappingsSearch->second);
			if (partSearch == numberPositions.end()) continue;
			adjacentParts.push_back(partSearch->second);
			numberMappings.erase(mappingsSearch);
			numberPositions.erase(partSearch);
		}

		if(adjacentParts.size() == 2) {
			answer += (adjacentParts[0] * adjacentParts[1]);
		}
	}

	return answer;
}


void Day3::puzzle1() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "First puzzle: " << calculatePuzzle1(input) << std::endl;
}

void Day3::puzzle2() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "Second puzzle: " << calculatePuzzle2(input) << std::endl;
}

void Day3::test() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	assert(calculatePuzzle1(Reader::readFile(testFile1)) == 4361);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 3 part 1 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 467835);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 3 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}