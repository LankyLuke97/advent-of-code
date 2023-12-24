#pragma once
#include <cassert>
#include <map>
#include <sstream>
#include <Windows.h>
#include "Day7.h"

int Day7::calculatePuzzle1(std::vector<std::string> input) {
	int64_t answer = 0;

	std::map<Hand1, int> bids;
	std::string token;

	for(std::string line : input) {
		if(line.empty()) break;
		std::istringstream iss(line);
		if(iss >> token) {
			Hand1 hand(token);
			iss >> token;
			int bid = std::stoi(token);
			bids.emplace(hand, bid);
		}
	}

	int rank = 1;
	for(auto kv : bids) answer += kv.second * rank++;

	return answer;
}

int Day7::calculatePuzzle2(std::vector<std::string> input) {
	int64_t answer = 0;

	std::map<Hand2, int> bids;
	std::string token;

	for (std::string line : input) {
		if (line.empty()) break;
		std::istringstream iss(line);
		if (iss >> token) {
			Hand2 hand(token);
			iss >> token;
			int bid = std::stoi(token);
			bids.emplace(hand, bid);
		}
	}

	int rank = 1;
	for (auto kv : bids) answer += kv.second * rank++;
	//rank = 1;
	//for (auto kv : bids) std::cout << kv.first.cards << " is rank " << rank++ << " with a bid of " << kv.second << std::endl;

	return answer;
}


void Day7::puzzle1() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "First puzzle: " << calculatePuzzle1(input) << std::endl;
}

void Day7::puzzle2() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "Second puzzle: " << calculatePuzzle2(input) << std::endl;
}

void Day7::test() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	assert(calculatePuzzle1(Reader::readFile(testFile1)) == 6440);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 7 part 1 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 5905);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 7 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}