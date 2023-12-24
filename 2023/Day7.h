#pragma once
#include <cmath>
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
	std::string hand;
	int value = 0;
	std::unordered_map<char, int> mappings{ {'A', 13}, {'K', 12}, {'Q', 11}, {'J', 10}, {'T', 9}, {'9', 8}, {'8', 7}, {'7', 6}, {'6', 5}, {'5', 4}, {'4', 3}, {'3', 2}, {'2', 1} };

	Hand(std::string _cards) : cards(_cards) {
		calculateValue();
	}

	friend bool operator < (Hand const& l, Hand const& r) {
		return(l.value < r.value);
	}

	friend bool operator <= (Hand const& l, Hand const& r) {
		return(l.value <= r.value);

	}

	friend bool operator > (Hand const& l, Hand const& r) {
		return(l.value > r.value);
	}

	friend bool operator >= (Hand const& l, Hand const& r) {
		return(l.value >= r.value);
	}

	void calculateValue() {
		std::unordered_map<char, int> cardTypes;

		for (int i = 0; i < cards.size(); i++) {
			char card = cards[i];
			value += mappings[card] * std::pow(14, cards.size() - i - 1);
			cardTypes.try_emplace(card, 0);
			cardTypes[card]++;
		}

		switch(cardTypes.size()) {
		case 1:
			value += 6000000;
			break;
		case 2:
			for(auto kv : cardTypes) {
				if(kv.second == 4 || kv.second == 1) value += 5000000;
				else value += 4000000;
				break;
			}
			break;
		case 3:
			for (auto kv : cardTypes) {
				if(kv.second == 3) {
					value += 3000000;
					break;
				}
				if(kv.second == 2) {
					value += 2000000;
					break;
				}
			}
			break;
		case 4:
			value += 1000000;
			break;
		default:
			break;
		}
	}
};