
/*
Rank Part 1 : 595
Time Part 1 : 02 : 55 : 14

Rank Part 2 : 577
Time Part 2 : 03 : 00 : 00

Notes : This one was intense. The hardest (or perhaps most annoying) part of it was separating a 2D array into several smaller 2D arrays. 
Then COMBINING them back into one 2D array. Lots of grid management. Maybe I could have done it differently, with queues or with bool vectors, I don't know.
Part 2 takes a while to finish.

--- Day 21: Fractal Art ---
You find a program trying to generate some art. It uses a strange process that involves repeatedly enhancing the detail of an image through a set of rules.

The image consists of a two-dimensional square grid of pixels that are either on (#) or off (.). The program always begins with this pattern:

.#.
..#
###
Because the pattern is both 3 pixels wide and 3 pixels tall, it is said to have a size of 3.

Then, the program repeats the following process:

If the size is evenly divisible by 2, break the pixels up into 2x2 squares, and convert each 2x2 square into a 3x3 square by following the corresponding enhancement rule.
Otherwise, the size is evenly divisible by 3; break the pixels up into 3x3 squares, and convert each 3x3 square into a 4x4 square by following the corresponding enhancement rule.
Because each square of pixels is replaced by a larger one, the image gains pixels and so its size increases.

The artist's book of enhancement rules is nearby (your puzzle input); however, it seems to be missing rules. The artist explains that sometimes, one must rotate or flip the input pattern to find a match. (Never rotate or flip the output pattern, though.) Each pattern is written concisely: rows are listed as single units, ordered top-down, and separated by slashes. For example, the following rules correspond to the adjacent patterns:

../.#  =  ..
.#

.#.
.#./..#/###  =  ..#
###

#..#
#..#/..../#..#/.##.  =  ....
#..#
.##.
When searching for a rule to use, rotate and flip the pattern as necessary. For example, all of the following patterns match the same rule:

.#.   .#.   #..   ###
..#   #..   #.#   ..#
###   ###   ##.   .#.
Suppose the book contained the following two rules:

../.# => ##./#../...
.#./..#/### => #..#/..../..../#..#
As before, the program begins with this pattern:

.#.
..#
###
The size of the grid (3) is not divisible by 2, but it is divisible by 3. It divides evenly into a single square; the square matches the second rule, which produces:

#..#
....
....
#..#
The size of this enhanced grid (4) is evenly divisible by 2, so that rule is used. It divides evenly into four squares:

#.|.#
..|..
--+--
..|..
#.|.#
Each of these squares matches the same rule (../.# => ##./#../...), three of which require some flipping and rotation to line up with the rule. The output for the rule is the same in all four cases:

##.|##.
#..|#..
...|...
---+---
##.|##.
#..|#..
...|...
Finally, the squares are joined into a new grid:

##.##.
#..#..
......
##.##.
#..#..
......
Thus, after 2 iterations, the grid contains 12 pixels that are on.

How many pixels stay on after 5 iterations?

Your puzzle answer was 188.

--- Part Two ---
How many pixels stay on after 18 iterations?

Your puzzle answer was 2758764.

Both parts of this puzzle are complete! They provide two gold stars: **
*/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "CommonFunctions.h"

using namespace std;

vector<string> DivideSquares(string s, int size);
void RotateSquare(string &s);
void ReverseSquare(string &s);
void ChangeGrid(vector<string> &grid, map<string, string> &rules);
string CombineSquares(vector<string> &grid, int size);

void Challenge21() {
	ifstream input;
	input.open("Input/Challenge21/Input.txt");
	string line;

	//Parse the input to set up the rules that will transform the squares
	map<string, string> rules;
	while (getline(input, line)) {
		vector<string> tokens;
		Tokenize(line, tokens, " =>");
		rules[tokens[0]] = tokens[1];
	}

	string grid = ".#./..#/###";
	int size = 3;

	for (int m = 0; m < 18; m++) {
		//Logging
		cout << "Iteration : "<< m << endl;

		int targetSize = size % 2 == 0 ? size + (size / 2) : size + (size / 3);
		
		//Divide the entire grid into 2x2 or 3x3 squares
		vector<string> squares = DivideSquares(grid, size);
		//Change each of the 2x2 or 3x3 squares into larger squares using the map
		ChangeGrid(squares, rules);
		//Combine the squares back into one singular grid of size targetSize
		grid = CombineSquares(squares, size);

		size = targetSize;
	}

	//Find how many characters are '#'
	int finalCount = 0;
	for (int m = 0; m < grid.length(); m++) {
		if (grid[m] == '#')
			finalCount++;
	}
	cout << finalCount << endl;
	
}

//Separate the grid into 2x2 or 3x3 squares
vector<string> DivideSquares(string s, int size) {
	int squareLength = size % 2 == 0 ? 2 : 3;
	int numSquares = size / squareLength;
	
	vector<string> tokens;
	Tokenize(s, tokens, "/");

	vector<string> squares;
	for (int m = 0; m < size; m += squareLength) {
		for (int n = 0; n < size; n += squareLength) {
			string temp;
			temp.append(tokens[m].substr(n, squareLength));
			temp += "/";
			temp.append(tokens[m+1].substr(n, squareLength));
			if (squareLength == 3) {
				temp += "/";
				temp.append(tokens[m + 2].substr(n, squareLength));
			}
			squares.push_back(temp);
		}
	}
	return squares;
}

//Use the map, and rotate/flip the squares if necessary, to update the grid with ever-growing squares
void ChangeGrid(vector<string> &grid, map<string, string> &rules) {
	for (int m = 0; m < grid.size(); m++) {
		bool found = false;
		for (int flip = 0; flip <= 1; flip++) {
			for (int rot = 0; rot < 4; rot++) {
				if (rules.count(grid[m]) == 1) {
					found = true;
					grid[m] = rules[grid[m]];
					break;
				}
				RotateSquare(grid[m]);
			}
			if (found) 
				break;
			ReverseSquare(grid[m]);
		}
	}
}

//Rotate a square with brute force. 
void RotateSquare(string &s) {
	if (s.size() == 5) {
		char temp = s[0];
		s[0] = s[1];
		s[1] = s[4];
		s[4] = s[3];
		s[3] = temp;
	}
	else {
		char temp = s[0]; 
		s[0] = s[2];
		s[2] = s[10];
		s[10] = s[8];
		s[8] = temp;
		temp = s[1];
		s[1] = s[6];
		s[6] = s[9];
		s[9] = s[4];
		s[4] = temp;
	}
}
//Flip the square with brute force.
void ReverseSquare(string &s) {
	if (s.size() == 5) {
		char temp = s[0];
		s[0] = s[1];
		s[1] = temp;
		temp = s[3];
		s[3] = s[4];
		s[4] = temp;
	}
	else {
		char temp = s[0];
		s[0] = s[2];
		s[2] = temp;
		temp = s[8];
		s[8] = s[10];
		s[10] = temp;
		temp = s[4];
		s[4] = s[6];
		s[6] = temp;
	}
}
//Take all the squares and combine them BACK into one string
string CombineSquares(vector<string> &grid, int size) {
	string result = "";
	int squareLength = size % 2 == 0 ? 2 : 3;
	int numSquares = size / squareLength;

	for (int m = 0; m < numSquares; m++) {
		vector<string> parts(squareLength + 1, "");
		for (int n = m * numSquares; n < (m * numSquares) + numSquares; n++) {
			vector<string> temp;
			Tokenize(grid[n], temp, "/");
			for (int q = 0; q < temp.size(); q++) {
				parts[q].append(temp[q]);
			}
		}
		for (int q = 0; q < parts.size(); q++) {
			result += parts[q] + "/";
		}
	}
	result.pop_back();
	return result;
}