#pragma once
/*

Rank Part 1 : 1389
Time Part 1 : 01 : 43 : 35

Rank Part 2 : 953
Time Part 2 : 02 : 04 : 01

Notes : I was an hour and 17 minutes starting this one.
The first part wasn't clear how we were supposed to incorporate challenge 10 knot-hashes. The second part was a typical island problem


--- Day 14: Disk Defragmentation ---

Suddenly, a scheduled job activates the system's disk defragmenter. Were the situation different, you might sit and watch it for a while, but today, you just don't have that kind of time. It's soaking up valuable system resources that are needed elsewhere, and so the only option is to help it finish its task as soon as possible.

The disk in question consists of a 128x128 grid; each square of the grid is either free or used. On this disk, the state of the grid is tracked by the bits in a sequence of knot hashes.

A total of 128 knot hashes are calculated, each corresponding to a single row in the grid; each hash contains 128 bits which correspond to individual grid squares. Each bit of a hash indicates whether that square is free (0) or used (1).

The hash inputs are a key string (your puzzle input), a dash, and a number from 0 to 127 corresponding to the row. For example, if your key string were flqrgnkx, then the first row would be given by the bits of the knot hash of flqrgnkx-0, the second row from the bits of the knot hash of flqrgnkx-1, and so on until the last row, flqrgnkx-127.

The output of a knot hash is traditionally represented by 32 hexadecimal digits; each of these digits correspond to 4 bits, for a total of 4 * 32 = 128 bits. To convert to bits, turn each hexadecimal digit to its equivalent binary value, high-bit first: 0 becomes 0000, 1 becomes 0001, e becomes 1110, f becomes 1111, and so on; a hash that begins with a0c2017... in hexadecimal would begin with 10100000110000100000000101110000... in binary.

Continuing this process, the first 8 rows and columns for key flqrgnkx appear as follows, using # to denote used squares, and . to denote free ones:

##.#.#..-->
.#.#.#.#
....#.#.
#.#.##.#
.##.#...
##..#..#
.#...#..
##.#.##.-->
|      |
V      V
In this example, 8108 squares are used across the entire 128x128 grid.

Given your actual key string, how many squares are used?

Your puzzle answer was 8292.

--- Part Two ---

Now, all the defragmenter needs to know is the number of regions. A region is a group of used squares that are all adjacent, not including diagonals. Every used square is in exactly one region: lone used squares form their own isolated regions, while several adjacent squares all count as a single region.

In the example above, the following nine regions are visible, each marked with a distinct digit:

11.2.3..-->
.1.2.3.4
....5.6.
7.8.55.9
.88.5...
88..5..8
.8...8..
88.8.88.-->
|      |
V      V
Of particular interest is the region marked 8; while it does not appear contiguous in this small view, all of the squares marked 8 are connected when considering the whole 128x128 grid. In total, in this example, 1242 regions are present.

How many regions are present given your key string?

Your puzzle answer was 1069.

Both parts of this puzzle are complete! They provide two gold stars: **
*/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <queue>
#include "CommonFunctions.h"

using namespace std;

//New functions
string convertHashToBinary(string s);
int countIslands(vector<vector<int>> grid);

void Challenge14() {
	string input = "ugkiagan";

	int occupiedSquares = 0;
	vector<vector<int>> grid;
	for (int m = 0; m < 128; m++) {

		//Add -0 through -127 to the input to get different hashes for each line
		stringstream ss;
		ss << input << "-" << m;
		string temp;
		ss >> temp;

		//Challenge 10 hashing
		temp = knothash(temp);

		//0 = 0000, 1 = 0001, e = 1110, etc
		temp = convertHashToBinary(temp);

		//Create a grid
		vector<int> newLine;
		for (int n = 0; n < temp.length(); n++) {
			newLine.push_back(temp[n] - '0');

			//Part 1, count the number of occupied (1) squares
			if (temp[n] == '1')
				occupiedSquares++;
		}
		grid.push_back(newLine);
	}

	//Part 1 result
	cout << "Number of occupied squares : " << occupiedSquares << endl;


	cout << "Number of islands : " << countIslands(grid) << endl;



}

//Bruteforce all the cases 0-f
string convertHashToBinary(string s) {
	string result;
	stringstream ss;
	for (int m = 0; m < s.length(); m++) {
		switch (s[m]) {
		case '0':
			ss << "0000";
			break;
		case '1':
			ss << "0001";
			break;
		case '2':
			ss << "0010";
			break;
		case '3':
			ss << "0011";
			break;
		case '4':
			ss << "0100";
			break;
		case '5':
			ss << "0101";
			break;
		case '6':
			ss << "0110";
			break;
		case '7':
			ss << "0111";
			break;
		case '8':
			ss << "1000";
			break;
		case '9':
			ss << "1001";
			break;
		case 'a':
			ss << "1010";
			break;
		case 'b':
			ss << "1011";
			break;
		case 'c':
			ss << "1100";
			break;
		case 'd':
			ss << "1101";
			break;
		case 'e':
			ss << "1110";
			break;
		case 'f':
			ss << "1111";
			break;
		}
	}
	ss >> result;
	return result;
}

//Uses queue and breadth-first search to count the islands (adjoined not diagonal)
int countIslands(vector<vector<int>> grid) {
	vector<vector<int>> islands(grid.size(), vector<int>(grid[0].size(), 0));
	int numIslands = 0;
	for (int m = 0; m < grid.size(); m++) {
		for (int n = 0; n < grid[m].size(); n++) {
			if (grid[m][n] == 1 && islands[m][n] == 0) {
				numIslands++;
				queue<pair<int, int>> q;
				q.push(make_pair(m, n));
				while (!q.empty()) {
					pair<int, int> p = q.front();
					if (p.first + 1 < grid.size() && grid[p.first + 1][p.second] == 1 && islands[p.first + 1][p.second] == 0) {
						islands[p.first + 1][p.second] = 1;
						q.push(make_pair(p.first + 1, p.second));
					}
					if (p.first - 1 >= 0 && grid[p.first - 1][p.second] == 1 && islands[p.first - 1][p.second] == 0) {
						islands[p.first - 1][p.second] = 1;
						q.push(make_pair(p.first - 1, p.second));
					}
					if (p.second + 1 < grid[0].size() && grid[p.first][p.second + 1] == 1 && islands[p.first][p.second + 1] == 0) {
						islands[p.first][p.second + 1] = 1;
						q.push(make_pair(p.first, p.second + 1));
					}
					if (p.second - 1 >= 0 && grid[p.first][p.second - 1] == 1 && islands[p.first][p.second - 1] == 0) {
						islands[p.first][p.second - 1] = 1;
						q.push(make_pair(p.first, p.second - 1));
					}
					q.pop();
				}
			}
		}
	}
	return numIslands;
}