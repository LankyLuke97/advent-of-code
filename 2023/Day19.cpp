#pragma once
#include <algorithm>
#include <cassert>
#include <sstream>
#include <unordered_map>
#include <Windows.h>
#include "Day19.h"

int Day19::calculatePuzzle1(std::vector<std::string> input) {
	int answer = 0;

	bool parts = false;

	std::unordered_map<std::string, Workflow> workflows;

	for (std::string line : input) {
		if (line.empty()) {
			if (parts) break;
			parts = true;
			continue;
		}

		std::replace(line.begin(), line.end(), '{', ' ');
		std::replace(line.begin(), line.end(), '}', ' ');
		std::replace(line.begin(), line.end(), ',', ' ');
		std::replace(line.begin(), line.end(), ':', ' ');
		std::replace(line.begin(), line.end(), '=', ' ');

		std::istringstream iss(line);
		std::string token;

		Workflow accepted;
		Workflow rejected;

		accepted.flowInstructions.push_back(-1);
		accepted.flowVals.push_back(-1);
		accepted.flowOut.push_back("A");
		rejected.flowInstructions.push_back(-2);
		rejected.flowVals.push_back(-2);
		rejected.flowOut.push_back("R");

		workflows.emplace("A", accepted);
		workflows.emplace("R", rejected);

		if (parts) {
			std::vector<int> vals;
			while (iss >> token) {
				iss >> token;
				vals.push_back(std::stoi(token));
			}

			Part part(vals[0], vals[1], vals[2], vals[3]);
			bool finished = false;

			Workflow workflow = workflows["in"];
			while (!finished) {
				for (int i = 0; i < workflow.flowInstructions.size(); i++) {
					int instruction = workflow.flowInstructions[i];
					int val = workflow.flowVals[i];
					std::string out = workflow.flowOut[i];


					if (instruction < 0) {
						if (instruction == -3) {
							workflow = workflows[out];
							break;
						}

						if (instruction == -1) answer += part.value;
						finished = true;
						break;						
					}

					if (instruction == 0) {
						if (part.x < val) {
							workflow = workflows[out];
							break;
						}
					} else if (instruction == 1) {
						if (part.x > val) {
							workflow = workflows[out];
							break;
						}
					} else if (instruction == 2) {
						if (part.m < val) {
							workflow = workflows[out];
							break;
						}
					} else if (instruction == 3) {
						if (part.m > val) {
							workflow = workflows[out];
							break;
						}
					} else if (instruction == 4) {
						if (part.a < val) {
							workflow = workflows[out];
							break;
						}
					} else if (instruction == 5) {
						if (part.a > val) {
							workflow = workflows[out];
							break;
						}
					} else if (instruction == 6) {
						if (part.s < val) {
							workflow = workflows[out];
							break;
						}
					} else if (instruction == 7) {
						if (part.s > val) {
							workflow = workflows[out];
							break;
						}
					}
				}
			}
		} else {
			Workflow workflow;
			std::string key;
			iss >> key;
			
			while (iss >> token) {
				if (token.size() == 1) {
					if (token == "A") {
						workflow.flowInstructions.push_back(-1);
						workflow.flowVals.push_back(-1);
						workflow.flowOut.push_back("-1");
					} else if (token == "R") {
						workflow.flowInstructions.push_back(-2);
						workflow.flowVals.push_back(-2);
						workflow.flowOut.push_back("-2");
					}

					break;
				}

				std::string instruction(token.begin(), token.begin() + 2);
				
				if (instruction == "x<") {
					workflow.flowInstructions.push_back(0);
				} else if (instruction == "x>") {
					workflow.flowInstructions.push_back(1);
				} else if (instruction == "m<") {
					workflow.flowInstructions.push_back(2);
				} else if (instruction == "m>") {
					workflow.flowInstructions.push_back(3);
				} else if (instruction == "a<") {
					workflow.flowInstructions.push_back(4);
				} else if (instruction == "a>") {
					workflow.flowInstructions.push_back(5);
				} else if (instruction == "s<") {
					workflow.flowInstructions.push_back(6);
				} else if (instruction == "s>") {
					workflow.flowInstructions.push_back(7);
				} else {
					workflow.flowInstructions.push_back(-3);
					workflow.flowVals.push_back(-3);
					workflow.flowOut.push_back(token);
					break;
				}

				workflow.flowVals.push_back(std::stoi(std::string(token.begin() + 2, token.end())));
				iss >> token;
				workflow.flowOut.push_back(token);
			}
						

			workflows.emplace(key, workflow);
		}
	}

	return answer;
}

int Day19::calculatePuzzle2(std::vector<std::string> input) {
	int answer = 0;

	return answer;
}

void Day19::puzzle1() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "First puzzle: " << calculatePuzzle1(input) << std::endl;
}

void Day19::puzzle2() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "Second puzzle: " << calculatePuzzle2(input) << std::endl;
}

void Day19::test() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle1(Reader::readFile(testFile1)) == 19114);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 19 part 1 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 0);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 19 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}