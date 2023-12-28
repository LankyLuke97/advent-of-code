#pragma once
#include <cassert>
#include <queue>
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

	int lineNum = -1, currentLine = 0, col = -1, currentCol = 0;
	for (std::string line : input) {
		if (line.empty()) break;

		for (char c : line) {
			if (c == 'S') {
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

	int direction = -1;
	int lineSize = input[0].size();

	/*
	Directions:
		0
	3	X	1
		2
	*/

	if (lineNum > 0) {
		if (input[lineNum - 1][col] == '7' || input[lineNum - 1][col] == '|' || input[lineNum - 1][col] == 'F') direction = 0;
	}
	if (lineNum < input.size() - 2 && direction == -1) {
		if (input[lineNum + 1][col] == 'J' || input[lineNum + 1][col] == '|' || input[lineNum + 1][col] == 'L') direction = 2;
	}
	if (col < input[lineNum].size() - 2 && direction == -1) {
		if (input[lineNum][col + 1] == 'J' || input[lineNum][col + 1] == '-' || input[lineNum][col + 1] == '7') direction = 1;
	}
	if (col > 0 && direction == -1) {
		if (input[lineNum][col - 1] == 'L' || input[lineNum][col - 1] == '-' || input[lineNum][col - 1] == 'F') direction = 3;
	}

	int exitDirection = direction;
	bool end = false;
	std::vector<std::vector<char>> cleaned(input.size() - 1, std::vector<char>(input[0].size(), '.'));
	int loopSegments = 0;

	while (!end) {
		loopSegments++;

		switch (direction) {
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
			if (direction == 1 || direction == 3) {
				std::cout << "Can only enter | from above or below: (" << col << "," << lineNum << ")" << std::endl;
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
			if (direction == 2) direction = 1;
			else direction = 0;
			break;
		case 'J':
			if (direction == 0 || direction == 3) {
				std::cout << "Can only enter J from above or the left: (" << col << "," << lineNum << ")" << std::endl;
				assert(false);
			}
			if (direction == 2) direction = 3;
			else direction = 0;
			break;
		case '7':
			if (direction == 2 || direction == 3) {
				std::cout << "Can only enter 7 from below or the left: (" << col << "," << lineNum << ")" << std::endl;
				assert(false);
			}
			if (direction == 0) direction = 3;
			else direction = 2;
			break;
		case 'F':
			if (direction == 2 || direction == 1) {
				std::cout << "Can only enter F from below or the right: (" << col << "," << lineNum << ")" << std::endl;
				assert(false);
			}
			if (direction == 0) direction = 1;
			else direction = 2;
			break;
		case 'S':
			char replacement;
			if (direction == 0) {
				if (exitDirection == 0) replacement = '|';
				else if (exitDirection == 1) replacement = 'F';
				else replacement = '7';
			} else if(direction == 1) {
				if (exitDirection == 0) replacement = 'J';
				else if (exitDirection == 1) replacement = '-';
				else replacement = '7';			
			} else if(direction == 2) {
				if (exitDirection == 1) replacement = 'L';
				else if (exitDirection == 2) replacement = '|';
				else replacement = 'J';			
			} else {
				if (exitDirection == 0) replacement = 'L';
				else if (exitDirection == 2) replacement = 'F';
				else replacement = '-';			
			}
			current = replacement;

			end = true;
			break;
		}
		cleaned[lineNum][col] = current;
	}

	std::vector<char> enlarged;

	for(std::vector<char> cleanedLine : cleaned) {
		std::vector<char> line1;
		std::vector<char> line2;
		std::vector<char> line3;

		for (char c : cleanedLine) {
			switch (c) {
			case '.':
				line1.push_back('.');
				line1.push_back('.');
				line1.push_back('.');
				line2.push_back('.');
				line2.push_back('.');
				line2.push_back('.');
				line3.push_back('.');
				line3.push_back('.');
				line3.push_back('.');
				break;
			case '|':
				line1.push_back('.');
				line1.push_back('#');
				line1.push_back('.');
				line2.push_back('.');
				line2.push_back('#');
				line2.push_back('.');
				line3.push_back('.');
				line3.push_back('#');
				line3.push_back('.');
				break;
			case '-':
				line1.push_back('.');
				line1.push_back('.');
				line1.push_back('.');
				line2.push_back('#');
				line2.push_back('#');
				line2.push_back('#');
				line3.push_back('.');
				line3.push_back('.');
				line3.push_back('.');
				break;
			case 'L':
				line1.push_back('.');
				line1.push_back('#');
				line1.push_back('.');
				line2.push_back('.');
				line2.push_back('#');
				line2.push_back('#');
				line3.push_back('.');
				line3.push_back('.');
				line3.push_back('.');
				break;
			case 'J':
				line1.push_back('.');
				line1.push_back('#');
				line1.push_back('.');
				line2.push_back('#');
				line2.push_back('#');
				line2.push_back('.');
				line3.push_back('.');
				line3.push_back('.');
				line3.push_back('.');
				break;
			case '7':
				line1.push_back('.');
				line1.push_back('.');
				line1.push_back('.');
				line2.push_back('#');
				line2.push_back('#');
				line2.push_back('.');
				line3.push_back('.');
				line3.push_back('#');
				line3.push_back('.');
				break;
			case 'F':
				line1.push_back('.');
				line1.push_back('.');
				line1.push_back('.');
				line2.push_back('.');
				line2.push_back('#');
				line2.push_back('#');
				line3.push_back('.');
				line3.push_back('#');
				line3.push_back('.');
				break;
			}
		}

		for (char c : line1) enlarged.push_back(c);
		for (char c : line2) enlarged.push_back(c);
		for (char c : line3) enlarged.push_back(c);

		/*
		// Uncomment for display purposes
		for (char c : line1) std::cout << c;
		std::cout << std::endl;
		for (char c : line2) std::cout << c;
		std::cout << std::endl;
		for (char c : line3) std::cout << c;
		std::cout << std::endl;
		*/
	}

	std::queue<int> searchQueue;
	searchQueue.push(0);
	int enlargedLineSize = lineSize * 3;

	while(!searchQueue.empty()) {
		int index = searchQueue.front();
		searchQueue.pop();
		if (enlarged[index] == '.') enlarged[index] = 'O';
		else continue;

		if (index - enlargedLineSize > 0) {
			if(enlarged[index - enlargedLineSize] == '.') {
				searchQueue.push(index - enlargedLineSize);
			}
		}
		if (index + enlargedLineSize < enlarged.size() - 1) {
			if (enlarged[index + enlargedLineSize] == '.') {
				searchQueue.push(index + enlargedLineSize);
			}
		}
		if (index % enlargedLineSize > 0) {
			if (enlarged[index - 1] == '.') {
				searchQueue.push(index - 1);
			}
		}
		if (index % enlargedLineSize < enlargedLineSize - 1) {
			if (enlarged[index + 1] == '.') {
				searchQueue.push(index + 1);
			}
		}
	}

	/*
	// Uncomment for display purposes
	int count = 0;
	for (char c : enlarged) {
		std::cout << c;

		if (++count == enlargedLineSize) {
			count = 0;
			std::cout << std::endl;
		}
	}
	*/
	bool inside = true;

	for (int i = 0; i < input.size() - 1; i++) {
		for (int j = 0; j < input[0].size(); j++) {
			for (int k = 0; k < 3; k++) {
				for (int l = 0; l < 3; l++) {
					if (enlarged[(((i * 3 + k) * enlargedLineSize) + (j * 3) + l)] != '.') {
						inside = false;
						break;
					}
				}
				if (!inside) break;
			}

			if (inside) answer++;
			inside = true;
		}
	}

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
	assert(calculatePuzzle2(Reader::readFile(testFile2_1)) == 4);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 10 part 2 test 1 passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	assert(calculatePuzzle2(Reader::readFile(testFile2_2)) == 4);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 10 part 2 test 2 passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	assert(calculatePuzzle2(Reader::readFile(testFile2_3)) == 8);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 10 part 2 test 3 passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	assert(calculatePuzzle2(Reader::readFile(testFile2_4)) == 10);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 10 part 2 test 4 passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}