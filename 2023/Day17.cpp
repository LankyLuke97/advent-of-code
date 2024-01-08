#pragma once
#include <cassert>
#include <sstream>
#include <Windows.h>
#include "Day17.h"

std::unordered_map<std::string, int> Day17::costs;

int Day17::calculatePuzzle1(std::vector<std::string> input) {
	int answer = 0;
	Day17::costs.clear();

	int horizontalSize = input[0].size(), verticalSize = input.size() - 1;
	
	std::string flattened = "";
	for (std::string line : input) {
		if (line.empty())break;
		flattened += line;
	}

	answer = min(recursePuzzle1(flattened, std::vector<Step>{Step(0, 1)}, horizontalSize, verticalSize), recursePuzzle1(flattened, std::vector<Step>{Step(0, 2)}, horizontalSize, verticalSize));

	std::cout << "ANSWER: " << answer << std::endl;

	return answer;
}

int Day17::calculatePuzzle2(std::vector<std::string> input) {
	int answer = 0;


	return answer;
}

int Day17::recursePuzzle1(const std::string& input, std::vector<Step> steps, int horizontalSize, int verticalSize) {
	int cost = INT_MAX;

	if (steps.size() == 0) return cost;

	Step lastStep = steps[steps.size() - 1];
	auto search = std::find_if(
		Day17::costs.begin(), Day17::costs.end(),
		[lastStep](const auto& element) {
			return element.first == lastStep.toString();
		}
	);

	if (search != Day17::costs.end()) return search->second;

	if (lastStep.position == input.size() - 1) {
		Day17::costs.emplace(lastStep.toString(), *(input.end() - 1));
		return *(input.end() - 1);
	}

	for (int dir = 0; dir < 4; dir++) {
		bool crash = true;
		for (int i = 2; i < 5; i++) {
			int index = steps.size() - i;
			if (index < 0) {
				crash = false;
				break;
			}
			if (steps[index].direction != lastStep.direction) crash = false;
		}
		if (crash) continue;

		std::vector<Step> newSteps;
		bool added = false;

		switch (dir) {
		case 0: {
			if (lastStep.position < horizontalSize || lastStep.direction == 2) break;
			newSteps = steps;
			Step newStep(lastStep.position - horizontalSize, dir);
			if (std::find(steps.begin(), steps.end(), newStep) != steps.end()) break;
			added = true;
			newSteps.push_back(newStep);
			break;
		}
		case 1: {
			if ((lastStep.position % horizontalSize) >= horizontalSize - 1 || lastStep.direction == 3) break;
			newSteps = steps;
			Step newStep(lastStep.position + 1, dir);
			if (std::find(steps.begin(), steps.end(), newStep) != steps.end()) break;
			added = true;
			newSteps.push_back(newStep);
			break;
		}
		case 2: {
			if (lastStep.position >= (verticalSize - 1) * horizontalSize || lastStep.direction == 0) break;
			newSteps = steps;
			Step newStep(lastStep.position + horizontalSize, dir);
			if (std::find(steps.begin(), steps.end(), newStep) != steps.end()) break;
			added = true;
			newSteps.push_back(newStep);
			break;
		}
		case 3: {
			if ((lastStep.position % horizontalSize) <= 0 || lastStep.direction == 1) break;
			newSteps = steps;
			Step newStep(lastStep.position - 1, dir);
			if (std::find(steps.begin(), steps.end(), newStep) != steps.end()) break;
			added = true;
			newSteps.push_back(newStep);
			break;
		}
		}

		if(added) cost = min(cost, input[lastStep.position] + recursePuzzle1(input, newSteps, horizontalSize, verticalSize));
	}

	Day17::costs.emplace(lastStep.toString(), cost);
	return cost;
}

void Day17::puzzle1() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "First puzzle: " << calculatePuzzle1(input) << std::endl;
}

void Day17::puzzle2() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "Second puzzle: " << calculatePuzzle2(input) << std::endl;
}

void Day17::test() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle1(Reader::readFile(testFile1)) == 102);
	calculatePuzzle1(Reader::readFile(testFile1));
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 17 part 1 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 0);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 17 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}