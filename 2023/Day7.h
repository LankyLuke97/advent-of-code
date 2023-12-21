#pragma once
#include <unordered_map>
#include "Reader.h"

class Day7 {
private:
	const std::string testFile1 = "inputs/day7_part1_test.txt";
	const std::string testFile2 = "inputs/day7_part2_test.txt";
	const std::string puzzleFile = "inputs/day7.txt";
	int calculatePuzzle1(std::vector<std::string> input);
	int calculatePuzzle2(std::vector<std::string> input);
public:
	void puzzle1();
	void puzzle2();
	void test();
};

struct Hand {
	std::string cards;
	int value;
	std::unordered_map<char, int> mappings{ {'A', 14}, {'K', 13}, {'Q', 12}, {'J', 11}, {'T', 10}, {'9', 9}, {'8', 8}, {'7', 7}, {'6', 6}, {'5', 5}, {'4', 4}, {'3', 3}, {'2', 2} };

	friend bool operator < (Hand const& l, Hand const& r) {
		if(l.value < r.value) return true;
		if(l.value > r.value) return false;

		for(int i = 0; i < l.cards.size(); i++) {
			if(l.mappings[char(l.cards[i])] < r.mappings[char(r.cards[i])]) return true;
			if(l.mappings[char(l.cards[i])] > r.mappings[char(r.cards[i])]) return false;
		}
	}

	friend bool operator <= (Hand const& l, Hand const& r) {

	}

	friend bool operator > (Hand const& l, Hand const& r) {

	}

	friend bool operator >= (Hand const& l, Hand const& r) {

	}

	int calculateHand() {

	}
};