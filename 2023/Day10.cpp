#pragma once
#include <cassert>
#include <sstream>
#include <Windows.h>
#include "Day10.h"

int Day10::calculatePuzzle1(std::vector<std::string> input) {
	int answer = 0;

	int lineNum = -1, currentLine = 0, col = -1, currentCol = 0;
	for(std::string line : input) {
		if(line.empty()) break;

		for(char c : line) {
			if(c == 'S') {
				lineNum = currentLine;
				col = currentCol;

				break;
			}
			currentCol++;
		}
		if (lineNum > -1 && col > -1) break;
		currentLine++;
		currentCol = 0;
	}

	int steps = 0;
	int direction = -1;
	int lineSize = input[0].size();

	/*
	Directions:
		0
	3	X	1
		2
	*/

	if(lineNum > 0) {
		if(input[lineNum - 1][col] == '7' || input[lineNum - 1][col] == '|' || input[lineNum - 1][col] == 'F') direction = 0;
	}
	if(lineNum < input.size() - 2 && direction == -1) {
		if (input[lineNum + 1][col] == 'J' || input[lineNum + 1][col] == '|' || input[lineNum + 1][col] == 'L') direction = 2;
	}
	if(col < input[lineNum].size() - 2 && direction == -1) {
		if(input[lineNum][col + 1] == 'J' || input[lineNum][col + 1] == '-' || input[lineNum][col + 1] == '7') direction = 1;
	}
	if(col > 0 && direction == -1) {
		if(input[lineNum][col - 1] == 'L' || input[lineNum][col - 1] == '-' || input[lineNum][col - 1] == 'F') direction = 3;
	}

	bool end = false;

	while(!end) {
		steps++;

		switch(direction) {
		case 0:
			lineNum--;
			break;
		case 1:
			col++;
			break;
		case 2:
			lineNum++;
			break;
		case 3:
			col--;
			break;
		}

		char current = input[lineNum][col];
		switch (current) {
		case '.':
			std::cout << "Shouldn't encounter ground" << std::endl;
			assert(false);
			break;
		case '|':
			if(direction == 1 || direction == 3) {
				std::cout << "Can only enter | from above or below: (" << col << "," <<lineNum<< ")" << std::endl;
				assert(false);
			}
			break;
		case '-':
			if (direction == 0 || direction == 2) {
				std::cout << "Can only enter - from the side (" << col << "," << lineNum << ")" << std::endl;
				assert(false);
			}
			break;
		case 'L':
			if (direction == 0 || direction == 1) {
				std::cout << "Can only enter L from above or the right: (" << col << "," << lineNum << ")" << std::endl;
				assert(false);
			}
			if(direction == 2) direction = 1;
			else direction = 0;
			break;
		case 'J':
			if (direction == 0 || direction == 3) {
				std::cout << "Can only enter J from above or the left: (" << col << "," << lineNum << ")" << std::endl;
				assert(false);
			}
			if(direction == 2) direction = 3;
			else direction = 0;
			break;
		case '7':
			if (direction == 2 || direction == 3) {
				std::cout << "Can only enter 7 from below or the left: (" << col << "," << lineNum << ")" << std::endl;
				assert(false);
			}
			if(direction == 0) direction = 3;
			else direction = 2;
			break;
		case 'F':
			if (direction == 2 || direction == 1) {
				std::cout << "Can only enter F from below or the right: (" << col << "," << lineNum << ")" << std::endl;
				assert(false);
			}
			if(direction == 0) direction = 1;
			else direction = 2;
			break;
		case 'S':
			end = true;
			break;
		}
	}

	answer = (steps / 2) + steps % 2;

	return answer;
}

int Day10::calculatePuzzle2(std::vector<std::string> input) {
	int answer = 0;

	return answer;
}

void Day10::puzzle1() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "First puzzle: " << calculatePuzzle1(input) << std::endl;
}

void Day10::puzzle2() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "Second puzzle: " << calculatePuzzle2(input) << std::endl;
}

void Day10::test() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	assert(calculatePuzzle1(Reader::readFile(testFile1_1)) == 4);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 10 part 1 test 1 passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	assert(calculatePuzzle1(Reader::readFile(testFile1_2)) == 4);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 10 part 1 test 2 passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	assert(calculatePuzzle1(Reader::readFile(testFile1_3)) == 8);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 10 part 1 test 3 passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	assert(calculatePuzzle1(Reader::readFile(testFile1_4)) == 8);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 10 part 1 test 4 passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 0);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 10 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}