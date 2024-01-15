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

uint64_t Day19::calculatePuzzle2(std::vector<std::string> input) {
	uint64_t answer = 0;

	std::unordered_map<std::string, Workflow> workflows;

	for (std::string line : input) {
		if (line.empty()) break;

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

		Workflow workflow;
		std::string key;
		iss >> key;

		while (iss >> token) {
			if (token.size() == 1) {
				if (token == "A") {
					workflow.flowInstructions.push_back(-1);
					workflow.flowVals.push_back(-1);
					workflow.flowOut.push_back("-1");
				}
				else if (token == "R") {
					workflow.flowInstructions.push_back(-2);
					workflow.flowVals.push_back(-2);
					workflow.flowOut.push_back("-2");
				}

				break;
			}

			std::string instruction(token.begin(), token.begin() + 2);

			if (instruction == "x<") {
				workflow.flowInstructions.push_back(0);
			}
			else if (instruction == "x>") {
				workflow.flowInstructions.push_back(1);
			}
			else if (instruction == "m<") {
				workflow.flowInstructions.push_back(2);
			}
			else if (instruction == "m>") {
				workflow.flowInstructions.push_back(3);
			}
			else if (instruction == "a<") {
				workflow.flowInstructions.push_back(4);
			}
			else if (instruction == "a>") {
				workflow.flowInstructions.push_back(5);
			}
			else if (instruction == "s<") {
				workflow.flowInstructions.push_back(6);
			}
			else if (instruction == "s>") {
				workflow.flowInstructions.push_back(7);
			}
			else {
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

	std::vector<Part_2> parts;
	parts.push_back(Part_2());
	std::vector<Part_2>::iterator it = parts.begin() + 0;
	int index = 0;
	std::vector<std::vector<std::pair<int, int>>> ranges(4, std::vector<std::pair<int, int>>());

	while (it != parts.end()) {
		Part_2 part = *it;
		Workflow workflow = workflows[part.currentWorkflow];
		int instruction = workflow.flowInstructions[part.currentStep];
		int val = workflow.flowVals[part.currentStep];
		std::string out = workflow.flowOut[part.currentStep];

		if (instruction < 0) {
			if (instruction == -3) {
				part.currentStep = 0;
				part.currentWorkflow = out;
				parts[index] = part;
				continue;
			}

			if (instruction == -1) {
				ranges[0].push_back(part.x);
				ranges[1].push_back(part.m);
				ranges[2].push_back(part.a);
				ranges[3].push_back(part.s);
			}
			index++;
			it = parts.begin() + index;
			continue;
		}

		if (instruction == 0) {
			if (part.x.second < val) {
				part.currentWorkflow = out;
				part.currentStep = 0;
				continue;
			}

			part.currentStep++;

			if (part.x.first >= val) continue;

			Part_2 newPart(part, out);
			part.x.first = val;
			newPart.x.second = val - 1;
			parts[index] = part;
			parts.push_back(newPart);
		}
		else if (instruction == 1) {
			if (part.x.first > val) {
				part.currentWorkflow = out;
				part.currentStep = 0;
				continue;
			}

			part.currentStep++;

			if (part.x.second <= val) continue;

			Part_2 newPart(part, out);
			part.x.second = val;
			newPart.x.first = val + 1;
			parts[index] = part;
			parts.push_back(newPart);
		}
		else if (instruction == 2) {
			if (part.m.second < val) {
				part.currentWorkflow = out;
				part.currentStep = 0;
				continue;
			}

			part.currentStep++;

			if (part.m.first >= val) continue;

			Part_2 newPart(part, out);
			part.m.first = val;
			newPart.m.second = val - 1;
			parts[index] = part;
			parts.push_back(newPart);
		}
		else if (instruction == 3) {
			if (part.m.first > val) {
				part.currentWorkflow = out;
				part.currentStep = 0;
				continue;
			}

			part.currentStep++;

			if (part.m.second <= val) continue;

			Part_2 newPart(part, out);
			part.m.second = val;
			newPart.m.first = val + 1;
			parts[index] = part;
			parts.push_back(newPart);
		}
		else if (instruction == 4) {
			if (part.a.second < val) {
				part.currentWorkflow = out;
				part.currentStep = 0;
				continue;
			}

			part.currentStep++;

			if (part.a.first >= val) continue;

			Part_2 newPart(part, out);
			part.a.first = val;
			newPart.a.second = val - 1;
			parts[index] = part;
			parts.push_back(newPart);
		}
		else if (instruction == 5) {
			if (part.a.first > val) {
				part.currentWorkflow = out;
				part.currentStep = 0;
				continue;
			}

			part.currentStep++;

			if (part.a.second <= val) continue;

			Part_2 newPart(part, out);
			part.a.second = val;
			newPart.a.first = val + 1;
			parts[index] = part;
			parts.push_back(newPart);
		}
		else if (instruction == 6) {
			if (part.s.second < val) {
				part.currentWorkflow = out;
				part.currentStep = 0;
				continue;
			}

			part.currentStep++;

			if (part.s.first >= val) continue;

			Part_2 newPart(part, out);
			part.s.first = val;
			newPart.s.second = val - 1;
			parts[index] = part;
			parts.push_back(newPart);
		}
		else if (instruction == 7) {
			if (part.s.first > val) {
				part.currentWorkflow = out;
				part.currentStep = 0;
				continue;
			}

			part.currentStep++;

			if (part.s.second <= val) continue;

			Part_2 newPart(part, out);
			part.s.second = val;
			newPart.s.first = val + 1;
			parts[index] = part;
			parts.push_back(newPart);
		}

		it = parts.begin() + index;
	}

	for (int i = 0; i < ranges[0].size(); i++) {
		answer += uint64_t(ranges[0][i].second - ranges[0][i].first + 1) * uint64_t(ranges[1][i].second - ranges[1][i].first + 1) * uint64_t(ranges[2][i].second - ranges[2][i].first + 1) * uint64_t(ranges[3][i].second - ranges[3][i].first + 1);
	}

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
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 167409079868000);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 19 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}