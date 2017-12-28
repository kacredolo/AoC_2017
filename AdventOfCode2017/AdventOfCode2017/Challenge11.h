#pragma once
/*

Rank Part 1 : 355
Time Part 1 : 00 : 17 : 53

Rank Part 2 : 338
Time Part 2 : 00 : 22 : 50

Notes : Interesting problem working with hex grid. I'm sure there's a million better ways to do it, but this worked out pretty well.

--- Day 11: Hex Ed ---

Crossing the bridge, you've barely reached the other side of the stream when a program comes up to you, clearly in distress. "It's my child process," she says, "he's gotten lost in an infinite grid!"

Fortunately for her, you have plenty of experience with infinite grids.

Unfortunately for you, it's a hex grid.

The hexagons ("hexes") in this grid are aligned such that adjacent hexes can be found to the north, northeast, southeast, south, southwest, and northwest:

\ n  /
nw +--+ ne
/    \
-+      +-
\    /
sw +--+ se
/ s  \
You have the path the child process took. Starting where he started, you need to determine the fewest number of steps required to reach him. (A "step" means to move from the hex you are in to any adjacent hex.)

For example:

ne,ne,ne is 3 steps away.
ne,ne,sw,sw is 0 steps away (back where you started).
ne,ne,s,s is 2 steps away (se,se).
se,sw,se,sw,sw is 3 steps away (s,s,sw).
Your puzzle answer was 810.

--- Part Two ---

How many steps away is the furthest he ever got from his starting position?

Your puzzle answer was 1567.

Both parts of this puzzle are complete! They provide two gold stars: **
*/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include "CommonFunctions.h"

using namespace std;

void Challenge11() {
	ifstream input;
	input.open("Input/Challenge11/Input.txt");
	string line;

	while (getline(input, line)) {

		vector<string> v;
		Tokenize(line, v, " ,");

		int x = 0;
		int y = 0;

		//Part 2 variables
		int furthestX = 0;
		int furthestY = 0;

		for (int m = 0; m < v.size(); m++) {
			//Each direction needs to be handled specifically
			if (v[m] == "n") {
				x -= 2;
			}
			else if (v[m] == "ne") {
				x--;
				y++;
			}
			else if (v[m] == "e") {
				y += 2;
			}
			else if (v[m] == "se") {
				x++;
				y++;
			}
			else if (v[m] == "s") {
				x += 2;
			}
			else if (v[m] == "sw") {
				x++;
				y--;
			}
			else if (v[m] == "w") {
				y -= 2;
			}
			else if (v[m] == "nw") {
				x--;
				y--;
			}

			//Check if we are further away than we have ever been from the starting node
			if (abs(x) + abs(y) > abs(furthestX) + abs(furthestY)) {
				cout << x << "\t" << y << endl;
				furthestX = x;
				furthestY = y;
			}

		}

		//Diagonally head towards the destination first, then go vertical/horizontal to finish
		x = abs(x);
		y = abs(y);
		int diagonalSteps = min(x, y);
		int directSteps = (max(x, y) - diagonalSteps) / 2;
		int totalSteps = diagonalSteps + directSteps;
		cout << totalSteps << endl;

		//Do the same thing, but for part 2 use the furthest away node instead of the node we landed on
		furthestX = abs(furthestX);
		furthestY = abs(furthestY);
		int diagonalSteps2 = min(furthestX, furthestY);
		int directSteps2 = (max(furthestX, furthestY) - diagonalSteps2) / 2;
		int totalSteps2 = diagonalSteps2 + directSteps2;
		cout << totalSteps2 << endl;
	}
}