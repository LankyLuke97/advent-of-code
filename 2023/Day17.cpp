#pragma once
#include <cassert>
#include <queue>
#include <sstream>
#include <Windows.h>
#include "Day17.h"

int Day17::calculatePuzzle1(std::vector<std::string> input) {
	int answer = INT_MAX;
	int horizontalSize = input[0].size(), verticalSize = input.size() - 1;
	std::vector<Node> graph;

	for (int i = 0; i < verticalSize; i++) {
		if (input[i].empty()) break;
		for (int j = 0; j < horizontalSize; j++) {
			for (int k = 0; k < 12; k++) {
				Node node((12 * i * horizontalSize) + (j * 12) + k, k, (i * horizontalSize) + j);
				graph.push_back(node);
			}
		}
	}

	graph[0].distFromSource = 0;

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
				int pos = (i * horizontalSize * 12) + (j * 12) + k;
				int connectPos = -1;

				if (i > 0 && graph[pos].prevStep != 8 && graph[pos].prevStep % 2 != 0) {
					int weight1 = input[i - 1][j] - '0';
					connectPos = pos - k - (12 * horizontalSize) + 0;
					graph[connectPos].weight = weight1;
					graph[pos].connectedNodes.push_back(connectPos);

					if (i > 1 && graph[pos].prevStep != 4) {
						int weight2 = input[i - 2][j] - '0' + weight1;
						connectPos = pos - k - (24 * horizontalSize) + 4;
						graph[connectPos].weight = weight2;
						graph[pos].connectedNodes.push_back(connectPos);

						if (i > 2 && graph[pos].prevStep != 0) {
							int weight3 = input[i - 3][j] - '0' + weight2;
							connectPos = pos - k - (36 * horizontalSize) + 8;
							graph[connectPos].weight = weight3;
							graph[pos].connectedNodes.push_back(connectPos);
						}
					}
				}

				if (j < horizontalSize - 1 && graph[pos].prevStep != 9 && graph[pos].prevStep % 2 != 1) {
					int weight1 = input[i][j + 1] - '0';
					connectPos = pos - k + 12 + 1;
					graph[connectPos].weight = weight1;
					graph[pos].connectedNodes.push_back(connectPos);

					if (j < horizontalSize - 2 && graph[pos].prevStep != 5) {
						int weight2 = input[i][j + 2] - '0' + weight1;
						connectPos = pos - k + 24 + 5;
						graph[connectPos].weight = weight2;
						graph[pos].connectedNodes.push_back(connectPos);

						if (j < horizontalSize - 3 && graph[pos].prevStep != 1) {
							int weight3 = input[i][j + 3] - '0' + weight2;
							connectPos = pos - k + 36 + 9;
							graph[connectPos].weight = weight3;
							graph[pos].connectedNodes.push_back(connectPos);
						}
					}
				}

				if (i < verticalSize - 1 && graph[pos].prevStep != 10 && graph[pos].prevStep % 2 != 0) {
					int weight1 = input[i + 1][j] - '0';
					connectPos = pos - k + (12 * horizontalSize) + 2;
					graph[connectPos].weight = weight1;
					graph[pos].connectedNodes.push_back(connectPos);

					if (i < verticalSize - 2 && graph[pos].prevStep != 6) {
						int weight2 = input[i + 2][j] - '0' + weight1;
						connectPos = pos - k + (24 * horizontalSize) + 6;
						graph[connectPos].weight = weight2;
						graph[pos].connectedNodes.push_back(connectPos);

						if (i < verticalSize - 3 && graph[pos].prevStep != 2) {
							int weight3 = input[i + 3][j] - '0' + weight2;
							connectPos = pos - k + (36 * horizontalSize) + 10;
							graph[connectPos].weight = weight3;
							graph[pos].connectedNodes.push_back(connectPos);
						}
					}
				}

				if (j > 0 && graph[pos].prevStep != 11 && graph[pos].prevStep % 2 != 1) {
					int weight1 = input[i][j - 1] - '0';
					connectPos = pos - k - 12 + 3;
					graph[connectPos].weight = weight1;
					graph[pos].connectedNodes.push_back(connectPos);

					if (j > 1 && graph[pos].prevStep != 7) {
						int weight2 = input[i][j - 2] - '0' + weight1;
						connectPos = pos - k - 24 + 7;
						graph[connectPos].weight = weight2;
						graph[pos].connectedNodes.push_back(connectPos);

						if (j > 2 && graph[pos].prevStep != 3) {
							int weight3 = input[i][j - 3] - '0' + weight2;
							connectPos = pos - k - 36 + 11;
							graph[connectPos].weight = weight3;
							graph[pos].connectedNodes.push_back(connectPos);
						}
					}
				}
			}
		}
	}

	std::priority_queue<Node> priorityQueue;
	priorityQueue.push(graph[0]);

	while (!priorityQueue.empty()) {
		Node closest = priorityQueue.top();
		int minInd = closest.position;
		int minDist = closest.distFromSource;
		priorityQueue.pop();

		if (graph[minInd].visited) continue;
		graph[minInd].visited = true;

		for (int n : graph[minInd].connectedNodes) {
			if (graph[n].visited) continue;

			int newDist = minDist + graph[n].weight;
			if (newDist < graph[n].distFromSource) {
				graph[n].distFromSource = newDist;
				priorityQueue.push(graph[n]);
			}
		}
	}

	int currentNodeIndex = -1;

	for (Node n : graph) {
		if (n.originalPosition != horizontalSize * (verticalSize - 1) + horizontalSize - 1) continue;
		if (n.distFromSource < answer) {
			answer = n.distFromSource;
			currentNodeIndex = n.position;
		}
	}

	return answer;
}

int Day17::calculatePuzzle2(std::vector<std::string> input) {
	int answer = INT_MAX;
	int horizontalSize = input[0].size(), verticalSize = input.size() - 1;
	std::vector<Node> graph;
	const int expansionMult = 28;

	for (int i = 0; i < verticalSize; i++) {
		if (input[i].empty()) break;
		for (int j = 0; j < horizontalSize; j++) {
			for (int k = 0; k < expansionMult; k++) {
				Node node((expansionMult * i * horizontalSize) + (j * expansionMult) + k, k, (i * horizontalSize) + j);
				graph.push_back(node);
			}
		}
	}

	for(int i = 0; i < expansionMult; i++)
		graph[i].distFromSource = 0;

	/*
	*			four	five	six		seven	eight	nine	ten
	* up		0		4		8		12		16		20		24
	* right		1		5		9		13		17		21		25
	* down		2		6		10		14		18		22		26
	* left		3		7		11		15		19		23		27
	*/

	// Graph construction

	for (int i = 0; i < verticalSize; i++) {
		if (input[i].empty()) break;

		for (int j = 0; j < horizontalSize; j++) {
			for (int k = 0; k < expansionMult; k++) {
				int pos = (i * horizontalSize * expansionMult) + (j * expansionMult) + k;
				int connectPos = -1;

				if (i > 3 && graph[pos].prevStep % 2 != 0) {
					int weight = input[i - 1][j] + input[i - 2][j] + input[i - 3][j] + input[i - 4][j] - (4 * '0');
					connectPos = pos - k - ((4 * expansionMult) * horizontalSize) + 0;
					graph[connectPos].weight = weight;
					graph[pos].connectedNodes.push_back(connectPos);

					if (i > 4) {
						weight += input[i - 5][j] - '0';
						connectPos = pos - k - ((5 * expansionMult) * horizontalSize) + 4;
						graph[connectPos].weight = weight;
						graph[pos].connectedNodes.push_back(connectPos);

						if (i > 5) {
							weight += input[i - 6][j] - '0';
							connectPos = pos - k - ((6 * expansionMult) * horizontalSize) + 8;
							graph[connectPos].weight = weight;
							graph[pos].connectedNodes.push_back(connectPos);

							if (i > 6) {
								weight += input[i - 7][j] - '0';
								connectPos = pos - k - ((7 * expansionMult) * horizontalSize) + 12;
								graph[connectPos].weight = weight;
								graph[pos].connectedNodes.push_back(connectPos);

								if (i > 7) {
									weight += input[i - 8][j] - '0';
									connectPos = pos - k - ((8 * expansionMult) * horizontalSize) + 16;
									graph[connectPos].weight = weight;
									graph[pos].connectedNodes.push_back(connectPos);

									if (i > 8) {
										weight += input[i - 9][j] - '0';
										connectPos = pos - k - ((9 * expansionMult) * horizontalSize) + 20;
										graph[connectPos].weight = weight;
										graph[pos].connectedNodes.push_back(connectPos);

										if (i > 9) {
											weight += input[i - 10][j] - '0';
											connectPos = pos - k - ((10 * expansionMult) * horizontalSize) + 24;
											graph[connectPos].weight = weight;
											graph[pos].connectedNodes.push_back(connectPos);
										}
									}
								}
							}
						}
					}
				}

				if (j < horizontalSize - 4 && graph[pos].prevStep % 2 != 1) {
					int weight = input[i][j + 1] + input[i][j + 2] + input[i][j + 3] + input[i][j + 4] - (4 * '0');
					connectPos = pos - k + (4 * expansionMult) + 1;
					graph[connectPos].weight = weight;
					graph[pos].connectedNodes.push_back(connectPos);

					if (j < horizontalSize - 5) {
						weight += input[i][j + 5] - '0';
						connectPos = pos - k + (5 * expansionMult) + 5;
						graph[connectPos].weight = weight;
						graph[pos].connectedNodes.push_back(connectPos);

						if (j < horizontalSize - 6) {
							weight += input[i][j + 6] - '0';
							connectPos = pos - k + (6 * expansionMult) + 9;
							graph[connectPos].weight = weight;
							graph[pos].connectedNodes.push_back(connectPos);

							if (j < horizontalSize - 7) {
								weight += input[i][j + 7] - '0';
								connectPos = pos - k + (7 * expansionMult) + 13;
								graph[connectPos].weight = weight;
								graph[pos].connectedNodes.push_back(connectPos);

								if (j < horizontalSize - 8) {
									weight += input[i][j + 8] - '0';
									connectPos = pos - k + (8 * expansionMult) + 17;
									graph[connectPos].weight = weight;
									graph[pos].connectedNodes.push_back(connectPos);

									if (j < horizontalSize - 9) {
										weight += input[i][j + 9] - '0';
										connectPos = pos - k + (9 * expansionMult) + 21;
										graph[connectPos].weight = weight;
										graph[pos].connectedNodes.push_back(connectPos);

										if (j < horizontalSize - 10) {
											weight += input[i][j + 10] - '0';
											connectPos = pos - k + (10 * expansionMult) + 25;
											graph[connectPos].weight = weight;
											graph[pos].connectedNodes.push_back(connectPos);
										}
									}
								}
							}
						}
					}
				}

				if (i < verticalSize - 4 && graph[pos].prevStep % 2 != 0) {
					int weight = input[i + 1][j] + input[i + 2][j] + input[i + 3][j] + input[i + 4][j] - (4 * '0');
					connectPos = pos - k + ((4 * expansionMult) * horizontalSize) + 2;
					graph[connectPos].weight = weight;
					graph[pos].connectedNodes.push_back(connectPos);

					if (i < verticalSize - 5) {
						weight += input[i + 5][j] - '0';
						connectPos = pos - k + ((5 * expansionMult) * horizontalSize) + 6;
						graph[connectPos].weight = weight;
						graph[pos].connectedNodes.push_back(connectPos);

						if (i < verticalSize - 6) {
							weight += input[i + 6][j] - '0';
							connectPos = pos - k + ((6 * expansionMult) * horizontalSize) + 10;
							graph[connectPos].weight = weight;
							graph[pos].connectedNodes.push_back(connectPos);

							if (i < verticalSize - 7) {
								weight += input[i + 7][j] - '0';
								connectPos = pos - k + ((7 * expansionMult) * horizontalSize) + 14;
								graph[connectPos].weight = weight;
								graph[pos].connectedNodes.push_back(connectPos);

								if (i < verticalSize - 8) {
									weight += input[i + 8][j] - '0';
									connectPos = pos - k + ((8 * expansionMult) * horizontalSize) + 18;
									graph[connectPos].weight = weight;
									graph[pos].connectedNodes.push_back(connectPos);

									if (i < verticalSize - 9) {
										weight += input[i + 9][j] - '0';
										connectPos = pos - k + ((9 * expansionMult) * horizontalSize) + 22;
										graph[connectPos].weight = weight;
										graph[pos].connectedNodes.push_back(connectPos);

										if (i < verticalSize - 10) {
											weight += input[i + 10][j] - '0';
											connectPos = pos - k + ((10 * expansionMult) * horizontalSize) + 26;
											graph[connectPos].weight = weight;
											graph[pos].connectedNodes.push_back(connectPos);
										}
									}
								}
							}
						}
					}
				}

				if (j > 3 && graph[pos].prevStep % 2 != 1) {
					int weight = input[i][j - 1] + input[i][j - 2] + input[i][j - 3] + input[i][j - 4] - (4 * '0');
					connectPos = pos - k - (4 * expansionMult) + 3;
					graph[connectPos].weight = weight;
					graph[pos].connectedNodes.push_back(connectPos);

					if (j > 4) {
						weight += input[i][j - 5] - '0';
						connectPos = pos - k - (5 * expansionMult) + 7;
						graph[connectPos].weight = weight;
						graph[pos].connectedNodes.push_back(connectPos);

						if (j > 5) {
							weight += input[i][j - 6] - '0';
							connectPos = pos - k - (6 * expansionMult) + 11;
							graph[connectPos].weight = weight;
							graph[pos].connectedNodes.push_back(connectPos);

							if (j > 6) {
								weight += input[i][j - 7] - '0';
								connectPos = pos - k - (7 * expansionMult) + 15;
								graph[connectPos].weight = weight;
								graph[pos].connectedNodes.push_back(connectPos);

								if (j > 7) {
									weight += input[i][j - 8] - '0';
									connectPos = pos - k - (8 * expansionMult) + 19;
									graph[connectPos].weight = weight;
									graph[pos].connectedNodes.push_back(connectPos);

									if (j > 8) {
										weight += input[i][j - 9] - '0';
										connectPos = pos - k - (9 * expansionMult) + 23;
										graph[connectPos].weight = weight;
										graph[pos].connectedNodes.push_back(connectPos);

										if (j > 9) {
											weight += input[i][j - 10] - '0';
											connectPos = pos - k - (10 * expansionMult) + 27;
											graph[connectPos].weight = weight;
											graph[pos].connectedNodes.push_back(connectPos);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	std::priority_queue<Node> priorityQueue;
	for (int i = 0; i < expansionMult; i++)
		priorityQueue.push(graph[i]);

	while (!priorityQueue.empty()) {
		Node closest = priorityQueue.top();
		int minInd = closest.position;
		int minDist = closest.distFromSource;
		priorityQueue.pop();

		if (graph[minInd].visited) continue;
		graph[minInd].visited = true;

		for (int n : graph[minInd].connectedNodes) {
			if (graph[n].visited) continue;

			int newDist = minDist + graph[n].weight;
			if (newDist < graph[n].distFromSource) {
				graph[n].distFromSource = newDist;
				priorityQueue.push(graph[n]);
			}
		}
	}

	for (Node n : graph) {
		if (n.originalPosition != horizontalSize * (verticalSize - 1) + horizontalSize - 1) continue;
		if (n.distFromSource < answer) {
			answer = n.distFromSource;
		}
	}

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
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 17 part 1 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 94);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 17 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}