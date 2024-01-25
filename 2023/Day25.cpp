#pragma once
#include <algorithm>
#include <cassert>
#include <Eigen/Dense>
#include <sstream>
#include <unordered_map>
#include <Windows.h>
#include "Day25.h"

int Day25::calculatePuzzle1(std::vector<std::string> input) {
	int answer = 0;

	
	std::unordered_map<std::string, int> key;
	int id = 0;

	for (std::string line : input) {
		if (line.empty()) break;

		std::replace(line.begin(), line.end(), ':', ' ');

		std::istringstream iss(line);
		std::string token;

		while (iss >> token) if (key.find(token) == key.end()) { key.emplace(token, id++); }//std::cout << id << ": " << token << std::endl;}
	}

	std::vector<std::vector<int>> adjacencyMatrix(key.size(), std::vector<int>(key.size(), 0));
	std::vector<std::vector<int>> degreeMatrix(key.size(), std::vector<int>(key.size(), 0));

	for (std::string line : input) {
		if (line.empty()) break;

		std::replace(line.begin(), line.end(), ':', ' ');

		std::istringstream iss(line);
		std::string token;

		iss >> token;
		int lhs_key = key.find(token)->second;

		while (iss >> token) {
			int rhs_key = key.find(token)->second;

			adjacencyMatrix[lhs_key][rhs_key] = 1;
			adjacencyMatrix[rhs_key][lhs_key] = 1;
			degreeMatrix[lhs_key][lhs_key]++;
			degreeMatrix[rhs_key][rhs_key]++;
		}
	}

	std::cout << "Create laplacian matrix..." << std::endl;

	Eigen::MatrixXd laplaceMatrix(adjacencyMatrix.size(), adjacencyMatrix[0].size());
	for (int i = 0; i < adjacencyMatrix.size(); ++i) {
		for (int j = 0; j < adjacencyMatrix[0].size(); ++j) {
			laplaceMatrix(i, j) = static_cast<double>(degreeMatrix[i][j] - adjacencyMatrix[i][j]);
		}
	}

	std::cout << "Finished creating laplacian matrix" << std::endl;

	// Compute eigenvectors and eigenvalues
	Eigen::EigenSolver<Eigen::MatrixXd> solver(laplaceMatrix);

	// Get eigenvectors and eigenvalues
	Eigen::VectorXd eigenvalues = solver.eigenvalues().real();
	Eigen::MatrixXd eigenvectors = solver.eigenvectors().real();

	std::cout << "Solved eigenvectors/values" << std::endl;

	int secondSmallestIndex = 1; // Assuming the eigenvalues are sorted in ascending order
	for (int i = 2; i < eigenvalues.size(); ++i) if (eigenvalues(i) < eigenvalues(secondSmallestIndex)) secondSmallestIndex = i;

	std::cout << "Found second smallest: "<<secondSmallestIndex << std::endl;

	double secondSmallestEigenvalue = eigenvalues(secondSmallestIndex);
	Eigen::VectorXd secondSmallestEigenvector = eigenvectors.col(secondSmallestIndex);

	std::cout << "Selected second smallest" << std::endl;

	int part1 = 0, part2 = 0;

	for (double i : secondSmallestEigenvector) {
		part1 += (i < 0.0);
		part2 += (i >= 0.0);
	}

	std::cout << part1 << "," << part2 << std::endl;

	return part1 * part2;
}

int Day25::calculatePuzzle2(std::vector<std::string> input) {
	int answer = 0;

	return answer;
}

void Day25::puzzle1() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "First puzzle: " << calculatePuzzle1(input) << std::endl;
}

void Day25::puzzle2() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "Second puzzle: " << calculatePuzzle2(input) << std::endl;
}

void Day25::test() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle1(Reader::readFile(testFile1)) == 54);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 25 part 1 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 0);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 25 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}