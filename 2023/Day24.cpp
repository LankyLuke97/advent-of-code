#pragma once
#include <algorithm>
#include <cassert>
#include <sstream>
#include <Windows.h>
#include "Day24.h"

int Day24::calculatePuzzle1(std::vector<std::string> input, int64_t minRange, int64_t maxRange) {
	int answer = 0;

	std::vector<Hail> hailstones;

	for (std::string line : input) {
		if (line.empty()) break;

		std::replace(line.begin(), line.end(), ',', ' ');
		std::replace(line.begin(), line.end(), '@', ' ');

		std::istringstream iss(line);
		std::string token;

		iss >> token;
		long double x = std::stod(token);
		iss >> token;
		long double y = std::stod(token);
		iss >> token;
		long double z = std::stod(token);
		iss >> token;
		long double vx = std::stod(token);
		iss >> token;
		long double vy = std::stod(token);
		iss >> token;
		long double vz = std::stod(token);
		
		Hail hail(x, y, z, vx, vy, vz);

		hail.a = vy;
		hail.b = -vx;
		hail.c = (vy * x) - (vx * y);
		hailstones.push_back(hail);
	}

	for (int i = 0; i < hailstones.size() - 1; i++) {
		Hail h1 = hailstones[i];
		for (int j = i + 1; j < hailstones.size(); j++) {
			Hail h2 = hailstones[j];
			if (h1.a * h2.b == h2.a * h1.b) continue;

			float x = ((h1.c * h2.b) - (h2.c * h1.b)) / ((h1.a * h2.b) - (h2.a * h1.b));
			if (x < minRange || x > maxRange) continue;
			float y = ((h1.a * h2.c) - (h2.a * h1.c)) / ((h1.a * h2.b) - (h2.a * h1.b));
			if (y < minRange || y > maxRange) continue;

			if ((x - h1.x) * h1.vx < 0) continue;
			if ((x - h2.x) * h2.vx < 0) continue;
			if ((y - h1.y) * h1.vy < 0) continue;
			if ((y - h2.y) * h2.vy < 0) continue;

			answer++;
		}
	}

	return answer;
}

int Day24::calculatePuzzle2(std::vector<std::string> input) {
	int answer = 0;
	std::vector<Hail> hailstones;

	for (std::string line : input) {
		if (line.empty()) break;

		std::replace(line.begin(), line.end(), ',', ' ');
		std::replace(line.begin(), line.end(), '@', ' ');

		std::istringstream iss(line);
		std::string token;

		iss >> token;
		long double x = std::stod(token);
		iss >> token;
		long double y = std::stod(token);
		iss >> token;
		long double z = std::stod(token);
		iss >> token;
		long double vx = std::stod(token);
		iss >> token;
		long double vy = std::stod(token);
		iss >> token;
		long double vz = std::stod(token);

		Hail hail(x, y, z, vx, vy, vz);

		hail.a = vy;
		hail.b = -vx;
		hail.c = (vy * x) - (vx * y);
		hailstones.push_back(hail);

		//if (hailstones.size() == 4) break;
	}

	/*  From https://topaz.github.io/paste/#XQAAAQANDAAAAAAAAAArmUAGM0NwXMLp2PQFNgRmh8ezkFKvEQd5obzMZwooEj1R498QeYDSxeTiF400W5Ml85PHQXQ/t4JmA7LkXWLwCOuXjTUZ9cIX/jhhvcP8EwiigBA3i2aj2uwkTmPRUpEAhQcV3gFGRBZdv0QomIXupqptd/ZH+3xPKdlV6/b5otDSX93R82DTUevMK4ls0CJH7GExO62B4wsmGGLkWmUKpcUGjlRc6tnITVvD3GlONpMJeiLCP4CkT3fijH+LNeuijMoQO9curNNpIl/taPOLl36w+BZ4vroViny70gkz/pW1oV6mMkc5X+TUg+iszuafPivIAvsNmi5rdnobza5b1zLS1gG5VRBQm0xqlQ2ssvgQWD4pmrDVt0CUbQDnYN9SOUWUQhf9dH8Ih/78LE0mtSkUEX8yaTWqZkM1teONYoil2yC0gv2CcSKAAyBrWAqyiJ1IytGAMFpEnHnkWQBQHECQeQDBQwMV185CJMVXVJZvdbd673BNadRSmbY1tVaQo2Y2TAoqhglSQ2R+6vnl8a4kChB5XIMh/Rzf5Lre58IQ01Lu/EiJd7pe2ceM4U29XjhEmSUB4iQGLx3piB84WA8ixC0XLYEzjIfOKumlGMmoB2OtcBeio+MsLjBN8PdoUfiYX7EzBxv++JnFikhGKiJVDy6JWJPZgBYhYmHRVyz21u3NKwMqy4ET8shjXmT5UYh8MBQ/VHrKOF7YqDPkCvs2mm4PqRwjjMYbGmhmVXxU0emhxicM2H8XljNGsOmPk/EEziz6S3i8FDVIcFpkQkoQPLHhlI59Rg+ZePfiFn9zGbFQFfAXhiER+uKCuwndMY5ePfKhQIvdYTVVcjR5Hwhv8zMuAyAQeqHnyrce6XpPIBp5tpAvCmFTbUCDqJez5ONUX50z6gFcgtGOwM1DLOD8YAYZZdXQ03BPgcw53VdrCvdVxypRrGxPBQTHnu260g8PSSAT7oejUZC/Mx3KfPOrkThbZfylM4nijiNDi+JrReW8UeLEX3M/j7uz9r+lE6m1YnE9BYa0G6B/qdCU2QBct/lf1i5rgd2iwy63angdaCDRBNRNflV8MFBLox94kezB0lwMvussr6bSkkr52hHjcWGMwShj+URNOmkTEEEnB/Ik5HAi+BZBq8vG5LvOkWDCQRn2+x5un8XIAHjP24dzCcS/VAFtLA6CNs4nt9EtlqtS6FvEU8eI7Kx628WHFF/7l83TS4vhWMtwCqh+jr6BEna3YOoTMjkMMfibN5St+5/2dLGxUqN4vVP4p0CTqGQYH9ku+C+szbAPICIxaTjkJNZm6Ix+vJod/j0Gug==
	
		We can create first three equations from the fact that the hailstone 0 and our rock will meet at t0
		1) px0 + vx0 * t0 = pxr + vxr * t0
		2) py0 + vy0 * t0 = pyr + vyr * t0
		3) py0 + vz0 * t0 = pzr + vzr * t0

		We edit the three equations to isolate t0 because we don't really care about it
		1) t0 = (pxr - px0) / (vx0 - vxr)
		2) t0 = (pyr - py0) / (vy0 - vyr)
		3) t0 = (pzr - pz0) / (vz0 - vzr)

		Now we can create two equations eliminating t0 from the system
		1) (pxr - px0) / (vx0 - vxr) = (pyr - py0) / (vy0 - vyr)
		2) (pxr - px0) / (vx0 - vxr) = (pzr - pz0) / (vz0 - vzr)

		We edit the two new equations to so that we get ready to expand them
		1) (pxr - px0)* (vy0 - vyr) = (pyr - py0) * (vx0 - vxr)
		2) (pxr - px0)* (vz0 - vzr) = (pzr - pz0) * (vx0 - vxr)

		And now we expand the equations
		1) pxr* vy0 - pxr * vyr - px0 * vy0 + px0 * vyr = pyr * vx0 - pyr * vxr - py0 * vx0 + py0 * vxr
		2) pxr* vz0 - pxr * vzr - px0 * vz0 + px0 * vzr = pzr * vx0 - pzr * vxr - pz0 * vx0 + pz0 * vxr

		We know that those equations are true actually for any hailstone, not just hailstone 0
		So now we add two new equations for hailstone N which are identical to the two above
		3) pxr* vyN - pxr * vyr - pxN * vyN + pxN * vyr = pyr * vxN - pyr * vxr - pyN * vxN + pyN * vxr
		4) pxr* vzN - pxr * vzr - pxN * vzN + pxN * vzr = pzr * vxN - pzr * vxr - pzN * vxN + pzN * vxr

		Now we can substract equations 1 & 3 and substract 2 & 4
		It will help us to get rid of those pxr * vyr, pyr * vxr and so on
		We really don't want them because for cramer rule we need a linear equation a1*x+a2*y+...=c
		1 - 3) pxr* (vy0 - vyN) + pyr * (vxN - vx0) + vxr * (pyN - py0) + vyr * (px0 - pxN) = px0 * vy0 - py0 * vx0 - pxN * vyN + pyN * vxN
		2 - 4) pxr* (vz0 - vzN) + pzr * (vxN - vx0) + vxr * (pzN - pz0) + vzr * (px0 - pxN) = px0 * vz0 - pz0 * vx0 - pxN * vzN + pzN * vxN

		Now let's just add any missing variables to the two new equations
		1) pxr* (vy0 - vyN) + pyr * (vxN - vx0) + pzr * (0) + vxr * (pyN - py0) + vyr * (px0 - pxN) + vzr * (0) = px0 * vy0 - py0 * vx0 - pxN * vyN + pyN * vxN
		2) pxr* (vz0 - vzN) + pyr * (0) + pzr * (vxN - vx0) + vxr * (pzN - pz0) + vyr * (0) + vzr * (px0 - pxN) = px0 * vz0 - pz0 * vx0 - pxN * vzN + pzN * vxN

		That's it now we have two equations with constant coefficients for our six variables (pxr, pyr, pzr, vxr, vyr, vzr)
		It means that we can choose any three hailstones(1 to N) and have six equations linear system.

		vy0 - vy1    vx1 - vx0    0            py1 - py0    px0 - px1    0			= px0 * vy0 - py0 * vx0 - px1 * vy1 + py1 * vx1
		vz0 - vz1    0            vx1 - vx0    pz1 - pz0    0            px0 - px1	= px0 * vz0 - pz0 * vx0 - px1 * vz1 + pz1 * vx1
		vy0 - vy2    vx2 - vx0    0            py2 - py0    px0 - px2    0			= px0 * vy0 - py0 * vx0 - px2 * vy2 + py2 * vx2
		vz0 - vz2    0            vx2 - vx0    pz2 - pz0    0            px0 - px2	= px0 * vz0 - pz0 * vx0 - px2 * vz2 + pz2 * vx2
		vy0 - vy3    vx3 - vx0    0            py3 - py0    px0 - px3    0			= px0 * vy0 - py0 * vx0 - px3 * vy3 + py3 * vx3
		vz0 - vz3    0            vx3 - vx0    pz3 - pz0    0            px0 - px3	= px0 * vz0 - pz0 * vx0 - px3 * vz3 + pz3 * vx3

		Feed this matrix into Cramer's rule and we have our result
	*/

	Hail hs0 = hailstones[0], hs1 = hailstones[1], hs2 = hailstones[2];

	std::vector<std::vector<long double>> origMatrix = {
		{hs0.vy - hs1.vy, hs1.vx - hs0.vx,				 0, hs1.y - hs0.y, hs0.x - hs1.x,			  0},
		{hs0.vy - hs2.vy, hs2.vx - hs0.vx,				 0, hs2.y - hs0.y, hs0.x - hs2.x,			  0},
		{hs1.vz - hs0.vz,				0, hs0.vx - hs1.vx, hs0.z - hs1.z, 			   0, hs1.x - hs0.x},
		{hs2.vz - hs0.vz,				0, hs0.vx - hs2.vx, hs0.z - hs2.z,			   0, hs2.x - hs0.x},
		{			   0, hs0.vz - hs1.vz, hs1.vy - hs0.vy, 			0, hs1.z - hs0.z, hs0.y - hs1.y},
		{			   0, hs0.vz - hs2.vz, hs2.vy - hs0.vy, 			0, hs2.z - hs0.z, hs0.y - hs2.y},
	};

	std::vector<long double> col = {
		((hs1.y * hs1.vx) - (hs1.x * hs1.vy)) - ((hs0.y * hs0.vx) - (hs0.x * hs0.vy)),
		((hs2.y * hs2.vx) - (hs2.x * hs2.vy)) - ((hs0.y * hs0.vx) - (hs0.x * hs0.vy)),
		((hs1.x * hs1.vz) - (hs1.z * hs1.vx)) - ((hs0.x * hs0.vz) - (hs0.z * hs0.vx)),
		((hs1.x * hs2.vz) - (hs2.z * hs2.vx)) - ((hs0.x * hs0.vz) - (hs0.z * hs0.vx)),
		((hs1.z * hs1.vy) - (hs1.y * hs1.vz)) - ((hs0.z * hs0.vy) - (hs0.y * hs0.vz)),
		((hs2.z * hs2.vy) - (hs2.y * hs2.vz)) - ((hs0.z * hs0.vy) - (hs0.y * hs0.vz))
	};

	std::vector<std::vector<long double>> inverse = findInverse(origMatrix);

	std::cout << "Base" << std::endl;
	for (int i = 0; i < 6; i++) {
		std::cout << "{";
		for (int j = 0; j < 6; j++) {
			std::cout << origMatrix[i][j] << ", ";
		}
		std::cout << "}" << std::endl;
	}

	std::cout << "Inverse" << std::endl;
	for (int i = 0; i < 6; i++) {
		std::cout << "{";
		for (int j = 0; j < 6; j++) {
			std::cout << inverse[i][j] << ", ";
		}
		std::cout << "}," << std::endl;
	}

	int numRows = inverse.size();
	int numCols = inverse[0].size();

	// Check if the dimensions are valid for multiplication
	if (numCols != col.size()) {
		std::cerr << "Invalid dimensions for matrix-vector multiplication!" << std::endl;
		return answer;
	}

	// Perform matrix-vector multiplication
	std::vector<long double> result(numRows, 0.0);
	for (int i = 0; i < numRows; ++i) {
		for (int j = 0; j < numCols; ++j) {
			result[i] += inverse[i][j] * col[j];
		}
	}
	std::cout << "{";
	for (long double c : col) std::cout << c << ", ";
	std::cout << "}" << std::endl;

	std::cout << result[0] << ", " << result[1] << ", " << result[2] << std::endl;

	return answer;
}

std::vector<std::vector<long double>> Day24::findInverse(const std::vector<std::vector<long double>>& matrix) {
	int n = matrix.size();

	// Augment the matrix with the identity matrix
	std::vector<std::vector<long double>> augmentedMatrix(n, std::vector<long double>(2 * n, 0.0));
	for (int i = 0; i < n; ++i) {
		augmentedMatrix[i][i + n] = 1.0;
		for (int j = 0; j < n; ++j) {
			augmentedMatrix[i][j] = matrix[i][j];
		}
	}

	// Perform Gauss-Jordan elimination
	for (int i = 0; i < n; ++i) {
		double pivot = augmentedMatrix[i][i];

		// Normalize the row
		for (int j = 0; j < 2 * n; ++j) {
			augmentedMatrix[i][j] /= pivot;
		}

		// Eliminate other rows
		for (int k = 0; k < n; ++k) {
			if (k != i) {
				double factor = augmentedMatrix[k][i];
				for (int j = 0; j < 2 * n; ++j) {
					augmentedMatrix[k][j] -= factor * augmentedMatrix[i][j];
				}
			}
		}
	}

	// Extract the inverse from the augmented matrix
	std::vector<std::vector<long double>> inverse(n, std::vector<long double>(n, 0.0));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			inverse[i][j] = augmentedMatrix[i][j + n];
		}
	}

	return inverse;
}

void Day24::puzzle1() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "First puzzle: " << calculatePuzzle1(input, 200000000000000, 400000000000000) << std::endl;
}

void Day24::puzzle2() {
	std::vector<std::string> input = Reader::readFile(puzzleFile);
	std::cout << "Second puzzle: " << calculatePuzzle2(input) << std::endl;
}

void Day24::test() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle1(Reader::readFile(testFile1), 7, 27) == 2);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 24 part 1 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
	SetConsoleTextAttribute(h, 4);
	assert(calculatePuzzle2(Reader::readFile(testFile2)) == 47);
	SetConsoleTextAttribute(h, 2);
	std::cout << "Day 24 part 2 test passed" << std::endl;
	SetConsoleTextAttribute(h, 7);
}