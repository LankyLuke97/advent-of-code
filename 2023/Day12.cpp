#pragma once
#include <algorithm>
#include <cassert>
#include <sstream>
#include <Windows.h>
#include "Day12.h"

std::unordered_map<std::string, uint64_t> Day12::cache;

int Day12::calculatePuzzle1(std::vector<std::string> input) {
	int answer = 0;

	std::vector<int> contiguous;

	for (std::string line : input) {
		if (line.empty()) break;

		contiguous.clear();
		std::replace(line.begin(), line.end(), ',', ' ');
		std::istringstream iss(line);
		std::string data;
		std::string token;

		iss >> data;

		while (iss >> token) contiguous.push_back(std::stoi(token));
		std::vector<std::vector<char>> prevArrangements;

		if (data[0] == '.') prevArrangements.push_back({ '.' });
		else if (data[0] == '#') prevArrangements.push_back({ '#' });
		else {
			prevArrangements.push_back({ '.' });
			prevArrangements.push_back({ '#' });
		}

		std::vector<std::vector<char>> arrangements;

		for (int i = 1; i < data.size(); i++) {
			char c = data[i];
			arrangements.clear();

			for (std::vector<char> prev : prevArrangements) {
				int currentContiguous = 0;
				int contiguousIndex = -1;
				bool brokenBlock = false;

				for (char prevC : prev) {
					if (prevC == '.') {
						if (!brokenBlock) continue;
						currentContiguous = 0;
						brokenBlock = false;
					}
					else {
						if (!brokenBlock) {
							contiguousIndex++;
							brokenBlock = true;
						}
						currentContiguous++;
					}
				}

				if (c == '.' || c == '?') {
					std::vector<char> newArrangement = prev;
					newArrangement.push_back('.');
					if (!brokenBlock) arrangements.push_back(newArrangement);
					else if (currentContiguous == contiguous[contiguousIndex]) arrangements.push_back(newArrangement);
				}

				if (c == '#' || c == '?') {
					std::vector<char> newArrangement = prev;
					newArrangement.push_back('#');
					if (!brokenBlock) {
						if (++contiguousIndex < contiguous.size()) arrangements.push_back(newArrangement);
					}
					else if (++currentContiguous <= contiguous[contiguousIndex]) arrangements.push_back(newArrangement);
				}
			}

			prevArrangements = arrangements;
		}

		int part = 0;

		for (std::vector<char> arrangement : arrangements) {
			int currentContiguous = 0;
			int contiguousIndex = -1;
			int lastContiguous = 0;
			bool brokenBlock = false;

			for (char c : arrangement) {
				if (c == '.') {
					if (!brokenBlock) continue;
					currentContiguous = 0;
					brokenBlock = false;
				}
				else {
					if (!brokenBlock) {
						contiguousIndex++;
						brokenBlock = true;
					}
					currentContiguous++;
					lastContiguous = currentContiguous;
				}
			}

			if (contiguousIndex == contiguous.size() - 1 && lastContiguous == *(contiguous.end() - 1)) answer++;
		}
	}

	return answer;
}

uint64_t Day12::calculatePuzzle2(std::vector<std::string> input) {
	uint64_t answer = 0;
	for (std::string initialLine : input) {
		if (initialLine.empty()) break;

		std::vector<char> unfolded;
		unfolded.reserve(5 * (initialLine.size() + 1));
		std::string token;

		std::istringstream unfoldIss(initialLine);
		int unfoldMult = 5;

		unfoldIss >> token;
		for (int i = 0; i < unfoldMult; i++) {
			for (char c : token) unfolded.push_back(c);
			if (i < unfoldMult - 1) unfolded.push_back('?');
		}

		unfolded.push_back(' ');

		unfoldIss >> token;
		for (int i = 0; i < unfoldMult; i++) {
			for (char c : token) unfolded.push_back(c);
			if (i < unfoldMult - 1) unfolded.push_back(',');
		}

		std::string line(unfolded.begin(), unfolded.end());

		std::queue<int> contiguous; 
		std::replace(line.begin(), line.end(), ',', ' ');
		std::istringstream iss(line);
		std::string data;

		iss >> data;
		while (iss >> token) contiguous.push(std::stoi(token));

		answer += part2Recursion(data, contiguous);
	}

	return answer;
}

uint64_t Day12::part2Recursion(std::string& data, std::queue<int> groups) {
	std::string groupKey;
	std::queue<int> copy = groups;
	while (!copy.empty()) {
		groupKey += ',';
		groupKey += std::to_string(copy.front());
		copy.pop();
	}

	auto search = Day12::cache.find(data + groupKey);
	if (search != Day12::cache.end()) return search->second;

	if (data.size() == 0) return groups.size() == 0;
	if (groups.size() == 0) {
		for (char c : data) {
			if (c == '#') return 0;
		}
		return 1;
	}
	char c = data[0];
	std::string remainingData(data.begin() + 1, data.end());
	if (c == '.') {
		uint64_t val = part2Recursion(remainingData, groups);
		Day12::cache.try_emplace(remainingData + groupKey, val);
		Day12::cache.try_emplace(data + groupKey, val);
		return val;
	}
	if (c == '#') {
		int group = groups.front();

		if (data.size() < group) {
			Day12::cache.try_emplace(data + groupKey, 0);
			return 0;
		}

		for (int i = 0; i < group; i++) {
			if (data[i] == '.') {
				Day12::cache.try_emplace(data + groupKey, 0);
				return 0;
			}
		}

		if (data.size() > group && data[group] == '#') {
			Day12::cache.try_emplace(data + groupKey, 0);
			return 0;
		}

		auto afterGroup = group == data.size() ? data.end() : data.begin() + group + 1;
		std::string dataWithoutGroup(afterGroup, data.end());
		std::queue<int> popped(groups);
		popped.pop();
		uint64_t val = part2Recursion(dataWithoutGroup, popped);

		std::string poppedKey;
		std::queue<int> copy = popped;
		while (!copy.empty()) {
			poppedKey += ',';
			poppedKey += std::to_string(copy.front());
			copy.pop();
		}

		Day12::cache.try_emplace(dataWithoutGroup + poppedKey, val);
		Day12::cache.try_emplace(data + groupKey, val);

		return val;
	}

	std::string replacePeriod(data.begin(), data.end());
	std::string replaceHash(data.begin(), data.end());
	replacePeriod[0] = '.';
	replaceHash[0] = '#';

	uint64_t valPeriod = part2Recursion(replacePeriod, groups), valHash = part2Recursion(replaceHash, groups);
	Day12::cache.try_emplace(replacePeriod + groupKey, valPeriod);
	Day12::cache.try_emplace(replaceHash + groupKey, valHash);
	Day12::cache.try_emplace(data + groupKey, valPeriod + valHash);
	return valPeriod + valHash;
}

void Day12::puzzle1() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "First puzzle: " << calculatePuzzle1(input) << std::endl;
}

void Day12::puzzle2() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "Second puzzle: " << calculatePuzzle2(input) << std::endl;
}

void Day12::test() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); 
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle1(Reader::readFile(testFile1)) == 21);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 12 part 1 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 525152);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 12 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}