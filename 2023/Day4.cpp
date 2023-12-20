#pragma once
#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>
#include <sstream>
#include "Day4.h"

int Day4::calculatePuzzle1(std::vector<std::string> input) {
	int answer = 0;

	for (std::string line : input) {
		if (line.empty()) break;

		std::string token;
		std::istringstream iss(line);
		std::vector<int> winningNumbers;

		iss >> token;
		iss >> token;

		while(true) {
			iss >> token;
			try {
				winningNumbers.push_back(std::stoi(token));
			} catch (std::invalid_argument const& ex) {
				break;
			}
		}

		int winning = 0;
		while(iss >> token) {
			winning += (std::find(winningNumbers.begin(), winningNumbers.end(), std::stoi(token)) != winningNumbers.end());
		}

		answer += std::pow(2, winning - 1);
	}

	return answer;
}

int Day4::calculatePuzzle2(std::vector<std::string> input) {
	int lineNum = 0;
	std::vector<int> cardMembers(input.size() - 1, 1);

	for (std::string line : input) {
		if (line.empty()) break;

		std::string token;
		std::istringstream iss(line);
		std::vector<int> winningNumbers;

		iss >> token;
		iss >> token;

		while (true) {
			iss >> token;
			try {
				winningNumbers.push_back(std::stoi(token));
			}
			catch (std::invalid_argument const& ex) {
				break;
			}
		}

		int copyCard = lineNum + 1;
		int copyMultiplier = cardMembers[lineNum];
		while (iss >> token) {
			if(std::find(winningNumbers.begin(), winningNumbers.end(), std::stoi(token)) == winningNumbers.end()) continue;
			cardMembers[copyCard++] += copyMultiplier;
		}
		lineNum++;
	}

	return std::accumulate(cardMembers.begin(), cardMembers.end(), 0);
}


void Day4::puzzle1() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "First puzzle: " << calculatePuzzle1(input) << std::endl;
}

void Day4::puzzle2() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "Second puzzle: " << calculatePuzzle2(input) << std::endl;
}

void Day4::test() {
	assert(calculatePuzzle1(Reader::readFile(testFile1)) == 13);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 30);
}