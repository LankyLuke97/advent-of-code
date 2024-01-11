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

	// Graph construction
	for (int i = 0; i < verticalSize; i++) {
		if (input[i].empty()) break;

		for (int j = 0; j < horizontalSize; j++) {
			for (int k = 0; k < 12; k++) {
				int pos = (i * horizontalSize) + (j * 12) + k;
				if (i > 0 && graph[pos].prevStep != 8) {
					int weight1 = input[i - 1][j];
					graph[pos - (12 * verticalSize) + 0].weight = weight1;
					graph[pos].connectedNodes.push_back(graph[pos - (12 * verticalSize)+ 0]);

					if (i > 1 && graph[pos].prevStep != 4) {
						int weight2 = input[i - 2][j] + weight1;
						graph[pos - (24 * verticalSize) + 4].weight = weight2;
						graph[pos].connectedNodes.push_back(graph[pos - (24 * verticalSize) + 4]);

						if (i > 2 && graph[pos].prevStep != 0) {
							int weight3 = input[i - 3][j] + weight2;
							graph[pos - (36 * verticalSize) + 8].weight = weight3;
							graph[pos].connectedNodes.push_back(graph[pos - (36 * verticalSize) + 8]);
						}
					}
				}

				if (j < horizontalSize - 1 && graph[pos].prevStep != 9) {
					int weight1 = input[i][j + 1];
					graph[pos + 12 + 1].weight = weight1;
					graph[pos].connectedNodes.push_back(graph[pos + 12 + 1]);

					if (j < horizontalSize - 2 && graph[pos].prevStep != 5) {
						int weight2 = input[i][j + 2] + weight1;
						graph[pos + 24 + 5].weight = weight2;
						graph[pos].connectedNodes.push_back(graph[pos + 24 + 5]);

						if (j < horizontalSize - 3 && graph[pos].prevStep != 1) {
							int weight3 = input[i][j + 3] + weight2;
							graph[pos + 36 + 9].weight = weight3;
							graph[pos].connectedNodes.push_back(graph[pos + 36 + 9]);
						}
					}
				}
				
				if (i < verticalSize - 1 && graph[pos].prevStep != 10) {
					int weight1 = input[i + 1][j];
					graph[pos + (12 * verticalSize) + 2].weight = weight1;
					graph[pos].connectedNodes.push_back(graph[pos + (12 * verticalSize) + 2]);

					if (i < verticalSize - 2 && graph[pos].prevStep != 6) {
						int weight2 = input[i + 2][j] + weight1;
						graph[pos + (24 * verticalSize) + 6].weight = weight2;
						graph[pos].connectedNodes.push_back(graph[pos + (24 * verticalSize) + 6]);

						if (i < verticalSize - 3 && graph[pos].prevStep != 2) {
							int weight3 = input[i + 3][j] + weight2;
							graph[pos + (36 * verticalSize) + 10].weight = weight3;
							graph[pos].connectedNodes.push_back(graph[pos + (36 * verticalSize) + 10]);
						}
					}
				}

				if (j > 0 && graph[pos].prevStep != 11) {
					int weight1 = input[i][j - 1];
					graph[pos - 12 + 3].weight = weight1;
					graph[pos].connectedNodes.push_back(graph[pos - 12 + 1]);

					if (j > 1 && graph[pos].prevStep != 7) {
						int weight2 = input[i][j - 2] + weight1;
						graph[pos - 24 + 7].weight = weight2;
						graph[pos].connectedNodes.push_back(graph[pos - 24 + 5]);

						if (j > 2 && graph[pos].prevStep != 3) {
							int weight3 = input[i][j - 3] + weight2;
							graph[pos - 36 + 11].weight = weight3;
							graph[pos].connectedNodes.push_back(graph[pos - 36 + 9]);
						}
					}
				}
			}
		}
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