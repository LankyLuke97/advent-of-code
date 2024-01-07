#pragma once
#include <cassert>
#include <sstream>
#include <Windows.h>
#include "Day16.h"

int Day16::calculatePuzzle1(std::vector<std::string> input) {
	std::string flattened = "";
	for (std::string line : input) {
		if (line.empty())break;
		flattened += line;
	}

	int xSize = input[0].size(), ySize = input.size()- 1;
	std::vector<int> energised{ 0 };
	std::vector<Beam> beams;
	std::vector<Beam> reviewed;
	beams.push_back(Beam(0, 1));
	int beamIndex = 0;

	while (beamIndex < beams.size()) {
		if (std::find(reviewed.begin(), reviewed.end(), beams[beamIndex]) != reviewed.end()) {
			beamIndex++;
			continue;
		}
		reviewed.push_back(beams[beamIndex]);
		int currentPos = beams[beamIndex].position, currentDirection = beams[beamIndex].direction;
		int newPos = -1;
		char c;
		switch (currentDirection) {
		case 0:
			if (currentPos < xSize) {
				beamIndex++;
				break;
			}
			newPos = currentPos - xSize;
			if (std::find(energised.begin(), energised.end(), newPos) == energised.end()) energised.push_back(newPos);
			c = flattened[newPos];
			if (c == '.' or c == '|') {
				beams[beamIndex].position = newPos;
			} else if (c == '-') {
				Beam left(newPos, 3), right(newPos, 1);
				if (std::find(beams.begin(), beams.end(), left) == beams.end()) beams.push_back(left);
				if (std::find(beams.begin(), beams.end(), right) == beams.end()) beams.push_back(right);
				beamIndex++;
			} else if(c ==  '/') {
				beams[beamIndex].position = newPos;
				beams[beamIndex].direction = 1;
			} else if (c == '\\') {
				beams[beamIndex].position = newPos;
				beams[beamIndex].direction = 3;
			}
			break;
		case 1:
			if (currentPos % xSize == (xSize - 1)) {
				beamIndex++;
				break;
			}
			newPos = currentPos + 1;
			if (std::find(energised.begin(), energised.end(), newPos) == energised.end()) energised.push_back(newPos);
			c = flattened[newPos]; 
			if (c == '.' or c == '-') {
				beams[beamIndex].position = newPos;
				break;
			} else if (c == '|') {
				Beam up(newPos, 0), down(newPos, 2);
				if (std::find(beams.begin(), beams.end(), up) == beams.end()) beams.push_back(up);
				if (std::find(beams.begin(), beams.end(), down) == beams.end()) beams.push_back(down);
				beamIndex++;
				break;
			} else if(c ==  '/') {
				beams[beamIndex].position = newPos;
				beams[beamIndex].direction = 0;
				break;
			} else if(c ==  '\\') {
				beams[beamIndex].position = newPos;
				beams[beamIndex].direction = 2;
				break;
			}
			break;
		case 2:
			if (currentPos >= (ySize - 1) * xSize) {
				beamIndex++;
				break;
			}
			newPos = currentPos + xSize;
			if (std::find(energised.begin(), energised.end(), newPos) == energised.end()) energised.push_back(newPos);
			c = flattened[newPos];
			if (c == '.' or c == '|') {
				beams[beamIndex].position = newPos;
			} else if (c == '-') {
				Beam left(newPos, 3), right(newPos, 1);
				if (std::find(beams.begin(), beams.end(), left) == beams.end()) beams.push_back(left);
				if (std::find(beams.begin(), beams.end(), right) == beams.end()) beams.push_back(right);
				beamIndex++;
			} else if (c == '/') {
				beams[beamIndex].position = newPos;
				beams[beamIndex].direction = 3;
			} else if (c == '\\') {
				beams[beamIndex].position = newPos;
				beams[beamIndex].direction = 1;
			}
			break;
		case 3:
			if (currentPos % xSize == 0) {
				beamIndex++;
				break;
			}
			newPos = currentPos - 1;
			if (std::find(energised.begin(), energised.end(), newPos) == energised.end()) energised.push_back(newPos);
			c = flattened[newPos];
			if (c == '.' or c == '-') {
				beams[beamIndex].position = newPos;
				break;
			
			} else if (c == '|') {
				Beam up(newPos, 0), down(newPos, 2);
				if (std::find(beams.begin(), beams.end(), up) == beams.end()) beams.push_back(up);
				if (std::find(beams.begin(), beams.end(), down) == beams.end()) beams.push_back(down);
				beamIndex++;
				break;
			
			} else if (c == '/') {
				beams[beamIndex].position = newPos;
				beams[beamIndex].direction = 2;
				break;
			
			} else if (c == '\\') {
				beams[beamIndex].position = newPos;
				beams[beamIndex].direction = 0;
				break;
			}
			break;
		default:
			break;
		}
	}

	return energised.size();
}

int Day16::calculatePuzzle2(std::vector<std::string> input) {
	int answer = 0;

	std::string flattened = "";
	for (std::string line : input) {
		if (line.empty())break;
		flattened += line;
	}

	int xSize = input[0].size(), ySize = input.size() - 1;
	std::vector<Beam> startingBeams;

	for (int i = 0; i < xSize; i++) {
		switch (flattened[i]) {
		case '.':
		case '|':
			startingBeams.push_back(Beam(i, 2));
			break;
		case '-':
			startingBeams.push_back(Beam(i, 1));
			startingBeams.push_back(Beam(i, 3));
			break;
		case '/':
			startingBeams.push_back(Beam(i, 3));
			break;
		case '\\':
			startingBeams.push_back(Beam(i, 1));
			break;
		}

		int pos = ((ySize - 1) * xSize) + i;

		switch (flattened[pos]) {
		case '.':
		case '|':
			startingBeams.push_back(Beam(pos, 2));
			break;
		case '-':
			startingBeams.push_back(Beam(pos, 1));
			startingBeams.push_back(Beam(pos, 3));
			break;
		case '/':
			startingBeams.push_back(Beam(pos, 3));
			break;
		case '\\':
			startingBeams.push_back(Beam(pos, 1));
			break;
		}
	}

	for (int i = 0; i < ySize; i++) {
		int pos = (xSize * i);
		switch (flattened[pos]) {
		case '.':
		case '-':
			startingBeams.push_back(Beam(pos, 1));
			break;
		case '|':
			startingBeams.push_back(Beam(pos, 0));
			startingBeams.push_back(Beam(pos, 2));
			break;
		case '/':
			startingBeams.push_back(Beam(pos, 0));
			break;
		case '\\':
			startingBeams.push_back(Beam(pos, 2));
			break;
		}

		pos = (xSize * (i + 1)) - 1;

		switch (flattened[pos]) {
		case '.':
		case '-':
			startingBeams.push_back(Beam(pos, 3));
			break;
		case '|':
			startingBeams.push_back(Beam(pos, 0));
			startingBeams.push_back(Beam(pos, 2));
			break;
		case '/':
			startingBeams.push_back(Beam(pos, 2));
			break;
		case '\\':
			startingBeams.push_back(Beam(pos, 0));
			break;
		}
	}

	for (Beam starting : startingBeams) {
		std::vector<int> energised{ starting.position };
		std::vector<Beam> beams{ starting };
		std::vector<Beam> reviewed;

		int beamIndex = 0;

		while (beamIndex < beams.size()) {
			if (std::find(reviewed.begin(), reviewed.end(), beams[beamIndex]) != reviewed.end()) {
				beamIndex++;
				continue;
			}
			reviewed.push_back(beams[beamIndex]);
			int currentPos = beams[beamIndex].position, currentDirection = beams[beamIndex].direction;
			int newPos = -1;
			char c;
			switch (currentDirection) {
			case 0:
				if (currentPos < xSize) {
					beamIndex++;
					break;
				}
				newPos = currentPos - xSize;
				if (std::find(energised.begin(), energised.end(), newPos) == energised.end()) energised.push_back(newPos);
				c = flattened[newPos];
				if (c == '.' or c == '|') {
					beams[beamIndex].position = newPos;
				}
				else if (c == '-') {
					Beam left(newPos, 3), right(newPos, 1);
					if (std::find(beams.begin(), beams.end(), left) == beams.end()) beams.push_back(left);
					if (std::find(beams.begin(), beams.end(), right) == beams.end()) beams.push_back(right);
					beamIndex++;
				}
				else if (c == '/') {
					beams[beamIndex].position = newPos;
					beams[beamIndex].direction = 1;
				}
				else if (c == '\\') {
					beams[beamIndex].position = newPos;
					beams[beamIndex].direction = 3;
				}
				break;
			case 1:
				if (currentPos % xSize == (xSize - 1)) {
					beamIndex++;
					break;
				}
				newPos = currentPos + 1;
				if (std::find(energised.begin(), energised.end(), newPos) == energised.end()) energised.push_back(newPos);
				c = flattened[newPos];
				if (c == '.' or c == '-') {
					beams[beamIndex].position = newPos;
					break;
				}
				else if (c == '|') {
					Beam up(newPos, 0), down(newPos, 2);
					if (std::find(beams.begin(), beams.end(), up) == beams.end()) beams.push_back(up);
					if (std::find(beams.begin(), beams.end(), down) == beams.end()) beams.push_back(down);
					beamIndex++;
					break;
				}
				else if (c == '/') {
					beams[beamIndex].position = newPos;
					beams[beamIndex].direction = 0;
					break;
				}
				else if (c == '\\') {
					beams[beamIndex].position = newPos;
					beams[beamIndex].direction = 2;
					break;
				}
				break;
			case 2:
				if (currentPos >= (ySize - 1) * xSize) {
					beamIndex++;
					break;
				} 
				newPos = currentPos + xSize;
				if (std::find(energised.begin(), energised.end(), newPos) == energised.end()) energised.push_back(newPos);
				c = flattened[newPos];
				if (c == '.' or c == '|') {
					beams[beamIndex].position = newPos;
				}
				else if (c == '-') {
					Beam left(newPos, 3), right(newPos, 1);
					if (std::find(beams.begin(), beams.end(), left) == beams.end()) beams.push_back(left);
					if (std::find(beams.begin(), beams.end(), right) == beams.end()) beams.push_back(right);
					beamIndex++;
				}
				else if (c == '/') {
					beams[beamIndex].position = newPos;
					beams[beamIndex].direction = 3;
				}
				else if (c == '\\') {
					beams[beamIndex].position = newPos;
					beams[beamIndex].direction = 1;
				}
				break;
			case 3:
				if (currentPos % xSize == 0) {
					beamIndex++;
					break;
				}
				newPos = currentPos - 1;
				if (std::find(energised.begin(), energised.end(), newPos) == energised.end()) energised.push_back(newPos);
				c = flattened[newPos];
				if (c == '.' or c == '-') {
					beams[beamIndex].position = newPos;
					break;

				}
				else if (c == '|') {
					Beam up(newPos, 0), down(newPos, 2);
					if (std::find(beams.begin(), beams.end(), up) == beams.end()) beams.push_back(up);
					if (std::find(beams.begin(), beams.end(), down) == beams.end()) beams.push_back(down);
					beamIndex++;
					break;

				}
				else if (c == '/') {
					beams[beamIndex].position = newPos;
					beams[beamIndex].direction = 2;
					break;

				}
				else if (c == '\\') {
					beams[beamIndex].position = newPos;
					beams[beamIndex].direction = 0;
					break;
				}
				break;
			default:
				break;
			}
		}
		answer = max(answer, energised.size());
	}

	return answer;
}

void Day16::puzzle1() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "First puzzle: " << calculatePuzzle1(input) << std::endl;
}

void Day16::puzzle2() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "Second puzzle: " << calculatePuzzle2(input) << std::endl;
}

void Day16::test() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle1(Reader::readFile(testFile1)) == 46);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 16 part 1 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 51);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 16 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}