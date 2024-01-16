#pragma once
#include <algorithm>
#include <cassert>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <Windows.h>
#include "Day20.h"

uint64_t Day20::calculatePuzzle1(std::vector<std::string> input) {
	uint64_t lowPulses = 0, highPulses = 0;
	const int NUM_PULSES = 1000;
	std::queue<Pulse> pulses;
	std::vector<std::string> initial;
	std::unordered_map<std::string, Module> modules;

	for (std::string line : input) {
		if (line.empty()) break;

		std::replace(line.begin(), line.end(), ',', ' ');

		std::istringstream iss(line);
		std::string token;
		iss >> token;

		if (token == "broadcaster") {
			iss >> token;

			while (iss >> token) {
				initial.push_back(token);
			}

			continue;
		}

		Module module(std::string(token.begin() + 1, token.end()), token[0] == '%' ? 0 : 1);
		iss >> token;
		while (iss >> token) module.outputs.push_back(token);
		modules.emplace(module.name, module);
	}

	for (auto kv : modules) {
		std::vector<std::string> outputs = kv.second.outputs;
		for (std::string out : outputs) {
			Module m = modules[out];
			if (m.type == 0) continue;
			else if (m.type == 1) {
				m.inputStates.emplace(kv.first, false);
				modules[out] = m;
			}
		}
	}

	// I suspect part 2 will be too many pulses for a brute force approach and I'll need
	// to implement cycle detection, but 1000 times is little enough that I'm trying the 
	// brute force approach initially.
	for (int i = 0; i < NUM_PULSES; i++) {
		lowPulses++; // button to broadcast
		for (std::string init : initial) {
			Pulse pulse("broadcast", init, false);
			pulses.push(pulse);
		}

		while (!pulses.empty()) {
			Pulse pulse = pulses.front();
			pulses.pop();

			if (pulse.high) highPulses++;
			else lowPulses++;

			Module to = modules[pulse.to];
			if (to.type == 0) {
				if (pulse.high) continue;
				to.state ^= 1;
				for (std::string out : to.outputs) {
					Pulse pulse(to.name, out, to.state);
					pulses.push(pulse);
				}
			} else if (to.type == 1) {
				to.inputStates[pulse.from] = pulse.high;
				bool allHigh = true;
				for (auto kv : to.inputStates) {
					if (!kv.second) {
						allHigh = false;
						break;
					}
				}

				for (std::string out : to.outputs) {
					Pulse pulse(to.name, out, !allHigh);
					pulses.push(pulse);
				}
			}
			modules[to.name] = to;
		}
	}

	return lowPulses * highPulses;
}

int Day20::calculatePuzzle2(std::vector<std::string> input) {
	int answer = 0;

	return answer;
}

void Day20::puzzle1() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "First puzzle: " << calculatePuzzle1(input) << std::endl;
}

void Day20::puzzle2() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "Second puzzle: " << calculatePuzzle2(input) << std::endl;
}

void Day20::test() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle1(Reader::readFile(testFile1_1)) == 32000000);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 20 part 1 test 1 passed" << std::endl;
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle1(Reader::readFile(testFile1_2)) == 11687500);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 20 part 1 test 2 passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 0);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 20 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}