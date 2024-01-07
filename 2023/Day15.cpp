#pragma once
#include <cassert>
#include <sstream>
#include <unordered_map>
#include <Windows.h>
#include "Day15.h"

int Day15::calculatePuzzle1(std::vector<std::string> input) {
	int answer = 0;

	int current = 0;
	for (char c : input[0]) {
		if (c == ',') {
			answer += current;
			current = 0;
			continue;
		}

		current += int(c);
		current *= 17;
		current = current % 256;
	}
	answer += current;

	return answer;
}

int Day15::calculatePuzzle2(std::vector<std::string> input) {
	int answer = 0;

	std::vector<std::vector<Lens>> boxes(256, std::vector<Lens>());
	std::string label = "";

	int current = 0;
	for (int i = 0; i < input[0].size(); i++) {
		char c = input[0][i];

		if (c == '=') {
			int focalLength = input[0][++i] - '0';
			Lens newLens(label, focalLength);
			std::vector<Lens>::iterator existing = std::find(boxes[current].begin(), boxes[current].end(), newLens);

			if (existing == boxes[current].end())boxes[current].push_back(newLens);
			else *existing = newLens;

			current = 0;
			label = "";
			i++;
			continue;
		}

		if (c == '-') {
			int l = 0;
			for (l = 0; l < boxes[current].size(); l++) if (boxes[current][l].label == label) break;
			if (l < boxes[current].size()) boxes[current].erase(boxes[current].begin() + l);

			current = 0;
			label = "";
			i++;
			continue;
		}

		label += c;
		current += int(c);
		current *= 17;
		current = current % 256;
	}

	for (int i = 0; i < 256; i++) for (int j = 0; j < boxes[i].size(); j++) answer += (i + 1) * (j + 1) * boxes[i][j].focalLength;

	return answer;
}

void Day15::puzzle1() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "First puzzle: " << calculatePuzzle1(input) << std::endl;
}

void Day15::puzzle2() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "Second puzzle: " << calculatePuzzle2(input) << std::endl;
}

void Day15::test() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle1(Reader::readFile(testFile1)) == 1320);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 15 part 1 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 145);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 15 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}