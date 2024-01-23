#pragma once
#include <cassert>
#include <sstream>
#include <stack>
#include <Windows.h>
#include "Day23.h"

int Day23::calculatePuzzle1(std::vector<std::string> input) {
	int answer = 0;

	int horizontalSize = input[0].size(), verticalSize = input.size() - 1;
	int start = 0, end = (verticalSize - 1) * horizontalSize;
	std::vector<char> flattened;
	std::vector<std::vector<int>> paths;

	for (std::string line : input) {
		if (line.empty()) break;

		for (char c : line) flattened.push_back(c);
	}

	for (char c : input[0]) {
		if (c == '.') break;
		start++;
	}
	for (char c : input[input.size() - 2]) {
		if (c == '.') break;
		end++;
	}

	int currentPath = 0;
	paths.push_back(std::vector<int>{start, start + horizontalSize});

	while (currentPath < paths.size()) {
		int pos = paths[currentPath].back();

		int up = pos - horizontalSize, right = pos + 1, down = pos + horizontalSize, left = pos - 1;
		if (flattened[pos] == '^') {
			if (std::find(paths[currentPath].begin(), paths[currentPath].end(), up) != paths[currentPath].end()) currentPath++;
			else paths[currentPath].push_back(up);
		} else if (flattened[pos] == '>') {
			if (std::find(paths[currentPath].begin(), paths[currentPath].end(), right) != paths[currentPath].end()) currentPath++;
			else paths[currentPath].push_back(right);
		} else if (flattened[pos] == 'v') {
			if (std::find(paths[currentPath].begin(), paths[currentPath].end(), down) != paths[currentPath].end()) currentPath++;
			else paths[currentPath].push_back(down);
		} else if (flattened[pos] == '<') {
			if (std::find(paths[currentPath].begin(), paths[currentPath].end(), left) != paths[currentPath].end()) currentPath++;
			else paths[currentPath].push_back(left);
		} else {
			int newPaths = 0;
			bool continuesUp = (flattened[up] != '#' && std::find(paths[currentPath].begin(), paths[currentPath].end(), up) == paths[currentPath].end());
			bool continuesRight = (flattened[right] != '#' && std::find(paths[currentPath].begin(), paths[currentPath].end(), right) == paths[currentPath].end());
			bool continuesDown = (down < flattened.size() && flattened[down] != '#' && std::find(paths[currentPath].begin(), paths[currentPath].end(), down) == paths[currentPath].end());
			bool continuesLeft = (flattened[left] != '#' && std::find(paths[currentPath].begin(), paths[currentPath].end(), left) == paths[currentPath].end());

			if (continuesUp) newPaths++;
			if (continuesRight) newPaths++;
			if (continuesDown) newPaths++;
			if (continuesLeft) newPaths++;

			if (newPaths == 0) {
				currentPath++;
				continue;
			}
			if (newPaths == 1) {
				if (continuesUp) paths[currentPath].push_back(up);
				if (continuesRight) paths[currentPath].push_back(right);
				if (continuesDown) paths[currentPath].push_back(down);
				if (continuesLeft) paths[currentPath].push_back(left);
				continue;
			}
			std::vector<int> pathToNow = paths[currentPath];

			if (continuesUp) {
				std::vector<int> path = pathToNow;
				path.push_back(up);
				paths.push_back(path);
			}

			if (continuesRight) {
				std::vector<int> path = pathToNow;
				path.push_back(right);
				paths.push_back(path);
			}

			if (continuesDown) {
				std::vector<int> path = pathToNow;
				path.push_back(down);
				paths.push_back(path);
			}

			if (continuesLeft) {
				std::vector<int> path = pathToNow;
				path.push_back(left);
				paths.push_back(path);
			}

			currentPath++;
		}
	}

	for (std::vector<int> path : paths) {
		if (path.back() == end && (path.size() - 1) > answer) answer = path.size() - 1;
	}

	return answer;
}

int Day23::calculatePuzzle2(std::vector<std::string> input) {
	int answer = 0;

	int horizontalSize = input[0].size(), verticalSize = input.size() - 1;
	int start = 0, end = (verticalSize - 1) * horizontalSize;
	std::vector<char> flattened;
	std::vector<GraphNode> graph;

	for (std::string line : input) {
		if (line.empty()) break;

		for (char c : line) flattened.push_back(c);
	}

	for (char c : input[0]) {
		if (c == '.') break;
		start++;
	}

	for (char c : input[input.size() - 2]) {
		if (c == '.') break;
		end++;
	}

	GraphNode startNode(start);
	std::stack<int> latestPos, latestNode, latestDirection;
	std::vector<GraphNode> allNodes{ startNode };
	int currentWeight = 1;
	latestPos.push(start + horizontalSize);
	latestDirection.push(2);
	latestNode.push(start);

	while (!latestNode.empty()) {
		GraphNode currentNode = *std::find(allNodes.begin(), allNodes.end(), latestNode.top());
		latestNode.pop();
		int pos = latestPos.top();
		latestPos.pop();
		int dir = latestDirection.top();
		latestDirection.pop();
		currentWeight = 1;

		while (true) {
			int up = pos - horizontalSize, right = pos + 1, down = pos + horizontalSize, left = pos - 1;
			int newPaths = 0;
			bool continuesUp = flattened[up] != '#' && dir != 2;
			bool continuesRight = flattened[right] != '#' && dir != 3;
			bool continuesDown = down < flattened.size() && flattened[down] != '#' && dir != 0;
			bool continuesLeft = flattened[left] != '#' && dir != 1;

			if (continuesUp) newPaths++;
			if (continuesRight) newPaths++;
			if (continuesDown) newPaths++;
			if (continuesLeft) newPaths++;

			if (newPaths == 0) {
				GraphNode endNode(pos);
				endNode.connectedTo.emplace(currentNode.pos, currentWeight);
				currentNode.connectedTo.emplace(endNode.pos, currentWeight);
				endNode.end = true;
				allNodes.push_back(endNode);
				*std::find(allNodes.begin(), allNodes.end(), currentNode.pos) = currentNode;
				break;
			}
			if (newPaths == 1) {
				currentWeight++;
				if (continuesUp) {
					pos = up;
					dir = 0;
				}
				if (continuesRight) {
					pos = right;
					dir = 1;
				}
				if (continuesDown) {
					pos = down;
					dir = 2;
				}
				if (continuesLeft) {
					pos = left;
					dir = 3;
				}
				continue;
			}
			
			auto search = std::find(allNodes.begin(), allNodes.end(), pos);
			if (search != allNodes.end()) {
				GraphNode node = *search;
				node.connectedTo.emplace(currentNode.pos, currentWeight);
				*search = node;
				currentNode.connectedTo.emplace(node.pos, currentWeight);
				search = std::find(allNodes.begin(), allNodes.end(), currentNode.pos);
				*search = currentNode;
				break;
			}

			GraphNode newNode(pos);
			newNode.connectedTo.emplace(currentNode.pos, currentWeight);
			currentNode.connectedTo.emplace(newNode.pos, currentWeight);
			allNodes.push_back(newNode);
			*std::find(allNodes.begin(), allNodes.end(), currentNode.pos) = currentNode;

			if (continuesUp) {
				latestDirection.push(0);
				latestPos.push(up);
				latestNode.push(newNode.pos);
			}

			if (continuesRight) {
				latestDirection.push(1);
				latestPos.push(right);
				latestNode.push(newNode.pos);
			}

			if (continuesDown) {
				latestDirection.push(2);
				latestPos.push(down);
				latestNode.push(newNode.pos);
			}

			if (continuesLeft) {
				latestDirection.push(3);
				latestPos.push(left);
				latestNode.push(newNode.pos);
			}
			break;
		}
	}

	std::stack<std::vector<GraphNode>> paths{};
	paths.push(std::vector<GraphNode>{ *std::find(allNodes.begin(), allNodes.end(), start) });

	while (!paths.empty()) {
		GraphNode node = paths.top().back(); 
		std::vector<GraphNode> currentPath = paths.top();
		paths.pop();

		if (node.end) {
			int totalWeight = 0;
			GraphNode currentNode = currentPath[0];
			GraphNode prevNode = currentNode;
			for (int i = 1; i < currentPath.size(); i++) {
				currentNode = currentPath[i];
				totalWeight += prevNode.connectedTo[currentNode.pos];
				prevNode = currentNode;
			}
			if (totalWeight > answer) answer = totalWeight;
			continue;
		}

		for (auto kv : node.connectedTo) {
			if (std::find(currentPath.begin(), currentPath.end(), kv.first) != currentPath.end()) continue;
			std::vector<GraphNode> newPath = currentPath;
			newPath.push_back(*std::find(allNodes.begin(), allNodes.end(), kv.first));
			paths.push(newPath);
		}
	}

	return answer;
}

void Day23::puzzle1() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "First puzzle: " << calculatePuzzle1(input) << std::endl;
}

void Day23::puzzle2() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "Second puzzle: " << calculatePuzzle2(input) << std::endl;
}

void Day23::test() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle1(Reader::readFile(testFile1)) == 94);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 23 part 1 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 154);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 23 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}