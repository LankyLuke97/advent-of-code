#pragma once
#include <cassert>
#include <sstream>
#include <Windows.h>
#include "Day17.h"

int Day17::calculatePuzzle1(std::vector<std::string> input) {
	int answer = 0;
	int horizontalSize = input[0].size(), verticalSize = input.size() - 1;
	std::vector<Node> graph(12 * (verticalSize * horizontalSize));

	for (int i = 0; i < verticalSize;i++) {
		if (input[i].empty()) break;
		for (int j = 0; j < horizontalSize; j++)
			for(int k = 0; k < 12; k++)
				graph.push_back(Node((i * horizontalSize) + (j * 12) + k, k));
	}

	/*
	0 - up one
	1 - right one
	2 - down one
	3 - left one
	4..7 - two
	8..11 - three
	*/

	for (int i = 0; i < verticalSize; i++) {
		if (input[i].empty()) break;

		for (int j = 0; j < horizontalSize; j++) {
			for (int k = 0; k < 12; k++) {
				int pos = (i * horizontalSize) + (j * 12) + k;
				if (i > 0 && graph[pos].prevStep != 8) {
					graph[pos - (12 * verticalSize)].weight = input[i - 1][j];
					graph[pos].connectedNodes.push_back(graph[pos - (12 * verticalSize)]);

					if (i > 1 && graph[pos].prevStep != 4) {
						graph[pos - (24 * verticalSize)].weight = input[i - 2][j];
						graph[pos].connectedNodes.push_back(graph[pos - (24 * verticalSize)]);

						if (i > 2 && graph[pos].prevStep != 0) {
							graph[pos - (36 * verticalSize)].weight = input[i - 3][j];
							graph[pos].connectedNodes.push_back(graph[pos - (36 * verticalSize)]);
						}
					}
				}

				if (j > 0) {

				}
				if (j > 1) {

				}
				if (j > 2) {

				}

				if (i < verticalSize - 1) {

				}
				if (i < verticalSize - 2) {

				}
				if (i < verticalSize - 3) {

				}

				if (j < verticalSize - 1) {

				}
				if (j < verticalSize - 2) {

				}
				if (j < verticalSize - 3) {

				}
			}
		}
	}

	std::string flattened = "";
	for (std::string line : input) {
		if (line.empty()) break;
		flattened += line;
	}

	std::vector<int> costs(flattened.size(), INT_MAX);
	costs[0] = 0;
	std::vector<int> visitedNodes{0};
	std::vector<int> unvisitedNodes;
	int currentNode = 0;

	for (int i = 1; i < flattened.size(); i++) {
		unvisitedNodes.push_back(i);
	}

	while (!unvisitedNodes.empty()) {

	}

	return answer;
}

int Day17::calculatePuzzle2(std::vector<std::string> input) {
	int answer = 0;

	return answer;
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