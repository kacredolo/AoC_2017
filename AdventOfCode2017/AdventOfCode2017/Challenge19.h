#pragma once
/*
Rank Part 1 : 319
Time Part 1 : 00 : 27 : 31

Rank Part 2 : 275
Time Part 2 : 00 : 28 : 50

Notes : A nice change from yesterday, things went right this time. This type of problem is interesting because it throws a lot at you, but you don't need more than 25% of what it's throwing.

--- Day 19: A Series of Tubes ---
Somehow, a network packet got lost and ended up here. It's trying to follow a routing diagram (your puzzle input), but it's confused about where to go.

Its starting point is just off the top of the diagram. Lines (drawn with |, -, and +) show the path it needs to take, starting by going down onto the only line connected to the top of the diagram. It needs to follow this path until it reaches the end (located somewhere within the diagram) and stop there.

Sometimes, the lines cross over each other; in these cases, it needs to continue going the same direction, and only turn left or right when there's no other option. In addition, someone has left letters on the line; these also don't change its direction, but it can use them to keep track of where it's been. For example:

|
|  +--+
A  |  C
F---|----E|--+
|  |  |  D
+B-+  +--+

Given this diagram, the packet needs to take the following path:

Starting at the only line touching the top of the diagram, it must go down, pass through A, and continue onward to the first +.
Travel right, up, and right, passing through B in the process.
Continue down (collecting C), right, and up (collecting D).
Finally, go all the way left through E and stopping at F.
Following the path to the end, the letters it sees on its path are ABCDEF.

The little packet looks up at you, hoping you can help it find the way. What letters will it see (in the order it would see them) if it follows the path? (The routing diagram is very wide; make sure you view it without line wrapping.)

Your puzzle answer was DTOUFARJQ.

--- Part Two ---
The packet is curious how many steps it needs to go.

For example, using the same routing diagram from the example above...

|
|  +--+
A  |  C
F---|--|-E---+
|  |  |  D
+B-+  +--+

...the packet would go:

6 steps down (including the first line at the top of the diagram).
3 steps right.
4 steps up.
3 steps right.
4 steps down.
3 steps right.
2 steps up.
13 steps left (including the F it stops on).
This would result in a total of 38 steps.

How many steps does the packet need to go?

Your puzzle answer was 16642.

Both parts of this puzzle are complete! They provide two gold stars: **
*/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "CommonFunctions.h"

using namespace std;

int ChangeDirection(vector<vector<char>> &v, pair<int, int> i, int d);
void Move(pair<int, int> &i, int &d);
void Challenge19() {
	ifstream input;
	input.open("Input/Challenge19/Input.txt");
	string line;

	vector<vector<char>> grid;
	pair<int, int> currIndex;
	bool firstLine = true;
	while (getline(input, line)) {
		vector<char> newLine;
		for (int m = 0; m < line.length(); m++) {
			newLine.push_back(line[m]);
			if (line[m] == '|' && firstLine) {
				currIndex = { 0, m };
			}
		}
		grid.push_back(newLine);
		firstLine = false;
	}

	int dir = south;
	//Part 2 variable
	int stepCounter = 0;

	cout << "Part 1 : ";
	while (currIndex.first >= 0 && currIndex.first < grid.size()
		&& currIndex.second >= 0 && currIndex.second < grid[0].size()) {
		stepCounter++;
		switch (grid[currIndex.first][currIndex.second]) {
			//Just continue forward until we hit a letter or a '+'
		case '|':
		case '-':
		case ' ':
			break;
		case '+':
			dir = ChangeDirection(grid, currIndex, dir);
			break;
		default:
			cout << grid[currIndex.first][currIndex.second];
		}
		Move(currIndex, dir);

	}
	cout << endl;
	//Part 2 result
	cout << "Part 2 : " << stepCounter - 1 << endl;
}

//Finds a neighbor that isn't empty and isn't from the direction we came from
int ChangeDirection(vector<vector<char>> &v, pair<int, int> i, int d) {
	if (i.first > 0 && v[i.first - 1][i.second] != ' ' && d != south)
		return north;
	if (i.first < v.size()-1 && v[i.first + 1][i.second] != ' ' && d != north)
		return south;
	if (i.second > 0 && v[i.first][i.second - 1] != ' ' && d != east)
		return west;
	if (i.second < v[0].size()-1 && v[i.first][i.second + 1] != ' ' && d != west)
		return east;

	return d;
}

//Move the current index depending on the current direction
void Move(pair<int, int> &i, int &d) {
	if (d == south)
		i.first++;
	if (d == north)
		i.first--;
	if (d == east)
		i.second++;
	if (d == west)
		i.second--;
}

