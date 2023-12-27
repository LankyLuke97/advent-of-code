#pragma once
#include <cassert>
#include <sstream>
#include <Windows.h>
#include "Day9.h"

int Day9::calculatePuzzle1(std::vector<std::string> input) {
	int answer = 0;

	for(std::string line : input) {
		if(line.empty()) break;

		std::istringstream iss(line);
		std::string token;
		std::vector<std::vector<int>> sequences;

		std::vector<int> sequence;
		std::vector<int> prevSeq;

		while(iss >> token) sequence.push_back(std::stoi(token));;

		bool allZero = false;

		while (!allZero) {
			allZero = true;
			sequences.push_back(sequence);
			sequence.clear();
			prevSeq = sequences.back();

			for (int i = 1; i < prevSeq.size(); i++) {
				int diff = prevSeq[i] - prevSeq[i - 1];
				sequence.push_back(diff);
				allZero = allZero && (diff == 0);
			}
		}

		int add = 0;
		for(int i = sequences.size() - 1; i > -1; i--) {
			add += sequences[i].back();
		}

		answer += add;
	}

	return answer;
}

int Day9::calculatePuzzle2(std::vector<std::string> input) {
	int answer = 0;

	return answer;
}

void Day9::puzzle1() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "First puzzle: " << calculatePuzzle1(input) << std::endl;
}

void Day9::puzzle2() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "Second puzzle: " << calculatePuzzle2(input) << std::endl;
}

void Day9::test() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	assert(calculatePuzzle1(Reader::readFile(testFile1)) == 114);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 9 part 1 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 0);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 9 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}