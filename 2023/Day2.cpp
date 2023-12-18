#pragma once
#include <cassert>
#include <sstream>
#include "Day2.h"

int Day2::calculatePuzzle1(std::vector<std::string> input) {
	int answer = 0;
	int r = 12, g = 13, b = 14;

	for(std::string line : input) {
		if(line.empty()) break;
		line.erase(std::remove(line.begin(), line.end(), ','));
		line.erase(std::remove(line.begin(), line.end(), ';'));
		line.erase(std::remove(line.begin(), line.end(), ':'));
		bool add = true;

		std::string token;
		std::istringstream iss(line);

		iss >> token;
		iss >> token;
		int id;

		try {
			id = std::stoi(token);
		} catch (std::invalid_argument const& ex) {
			std::cout << "std::invalid_argument::what(): " << ex.what() << '\n';
		}

		int i;

		while(iss >> token) {
			try {
				i = std::stoi(token);
			} catch(std::invalid_argument const& ex) {
				if((token.substr(0, 3) == "red" && i > r) || (token.substr(0, 5) == "green" && i > g) || (token.substr(0, 4) == "blue" && i > b)) {
					add = false;
					break;
				}
			}
		}

		if (add) answer += id;
	}

	return answer;
}

int Day2::calculatePuzzle2(std::vector<std::string> input) {
	int answer = 0;

	for (std::string line : input) {
		if (line.empty()) break;
		int r = 0, g = 0, b = 0;
		line.erase(std::remove(line.begin(), line.end(), ','));
		line.erase(std::remove(line.begin(), line.end(), ';'));
		line.erase(std::remove(line.begin(), line.end(), ':'));

		std::string token;
		std::istringstream iss(line);

		iss >> token;
		iss >> token;

		int i;

		while (iss >> token) {
			try {
				i = std::stoi(token);
			} catch (std::invalid_argument const& ex) {
				if(token.substr(0, 3) == "red" && i > r) {
					r = i;
				} else if(token.substr(0, 5) == "green" && i > g) {
					g = i;
				} else if(token.substr(0, 4) == "blue" && i > b) {
					b = i;
				}
			}
		}

		answer += (r * g * b);
	}

	return answer;
}


void Day2::puzzle1() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "First puzzle: " << calculatePuzzle1(input) << std::endl;
}

void Day2::puzzle2() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "Second puzzle: " << calculatePuzzle2(input) << std::endl;
}

void Day2::test() {
	assert(calculatePuzzle1(Reader::readFile(testFile1)) == 8);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 2286);
}