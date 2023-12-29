#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Reader {
public:
	static std::vector<std::string> readFile(std::string relativeFilePath) {
		std::ifstream inputFile(relativeFilePath);
		std::string line;
		std::vector<std::string> lines;

		if(inputFile.is_open()) {
			while (inputFile) {
				std::getline(inputFile, line);
				lines.push_back(line);
			}
		}
		else {
			std::cout << "Could not open " << relativeFilePath << std::endl;
		}

		inputFile.close();
		return lines;
	}

	static void view(const std::vector<std::vector<char>>& input) {
		for (std::vector<char> line : input) {
			if (line.empty()) break;
			for (char c : line) std::cout << c;
			std::cout << std::endl;
		}
	}

	static void view(const std::vector<std::string>& input) {
		for (std::string line : input) {
			if (line.empty())break;
			std::cout << line << std::endl;
		}
	}
};
