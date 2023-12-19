#pragma once
#include <cassert>
#include <regex>
#include <sstream>
#include <unordered_map>
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
		std::regex_search(line, results, specialCharExpr);
		std::cout << results.size() << " results of special chars" << std::endl;

		for(int i = 0; i < results.size(); i++) {
			partSignifyingPositions.push_back(results.position(i) + (lineNum * lineLength));
		}

		std::regex_search(line, results, digitExpr);
		std::cout << results.size() << " results of digits" << std::endl;

		for(std::sregex_iterator it(line.begin(), line.end(), digitExpr); it != std::sregex_iterator(); ++it) {
			int startPos = it->position();
			////std::cout << "results[" <<  << "] = " << results[i] << ", results.position(" << i << ") = " << results.position(i) << std::endl;
			std::cout << "EMPLACING - " << (startPos + (lineNum * lineLength)) << ": " << std::stoi(it->str()) << std::endl;
			numberPositions.emplace(startPos + (lineNum * lineLength), std::stoi(it->str()));

			for(int posInd = 0; posInd < it->str().size(); posInd++) {
				numberMappings.emplace(startPos + posInd + (lineNum * lineLength), startPos + (lineNum * lineLength));
			}
		}
	}

	std::cout << "ALL LINES DONE" << std::endl;

	for(int partPos : partSignifyingPositions) {
		std::vector<int> offsets = { -lineLength - 1, -lineLength, -lineLength + 1, -1, 0, 1, lineLength + 1, lineLength, lineLength + 1 };

		for(int offset : offsets) {
			auto mappingsSearch = numberMappings.find(partPos + offset);
			if(mappingsSearch == numberMappings.end()) continue;
			auto partSearch = numberPositions.find(mappingsSearch->second);
			if(partSearch == numberPositions.end()) continue;
			answer += partSearch->second;
			std::cout << "ADDING " << partSearch->second << std::endl;
			numberMappings.erase(mappingsSearch);
			numberPositions.erase(partSearch);
		}
	}

	return answer;
}

int Day3::calculatePuzzle2(std::vector<std::string> input) {
	int answer = 0;

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
	assert(calculatePuzzle1(Reader::readFile(testFile1)) == 4361);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 0);
}