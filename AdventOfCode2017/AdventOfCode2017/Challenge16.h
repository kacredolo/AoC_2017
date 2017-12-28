#pragma once
/*
Rank Part 1 : 426
Time Part 1 : 00 : 19 : 45

Rank Part 2 : 462
Time Part 2 : 01 : 03 : 41

Notes : I approached this one completely wrong at first. It was a pretty complicated problem.
The main part that messed with me was the pA/B, as my plan (to do one billion moves) involved just the indices, not the letters themselves


--- Day 16: Permutation Promenade ---
You come upon a very unusual sight; a group of programs here appear to be dancing.

There are sixteen programs in total, named a through p. They start by standing in a line: a stands in position 0, b stands in position 1, and so on until p, which stands in position 15.

The programs' dance consists of a sequence of dance moves:

Spin, written sX, makes X programs move from the end to the front, but maintain their order otherwise. (For example, s3 on abcde produces cdeab).
Exchange, written xA/B, makes the programs at positions A and B swap places.
Partner, written pA/B, makes the programs named A and B swap places.
For example, with only five programs standing in a line (abcde), they could do the following dance:

s1, a spin of size 1: eabcd.
x3/4, swapping the last two programs: eabdc.
pe/b, swapping programs e and b: baedc.
After finishing their dance, the programs end up in order baedc.

You watch the dance for a while and record their dance moves (your puzzle input). In what order are the programs standing after their dance?

Your puzzle answer was fgmobeaijhdpkcln.

--- Part Two ---
Now that you're starting to get a feel for the dance moves, you turn your attention to the dance as a whole.

Keeping the positions they ended up in from their previous dance, the programs perform it again and again: including the first dance, a total of one billion (1000000000) times.

In the example above, their second dance would begin with the order baedc, and use the same dance moves:

s1, a spin of size 1: cbaed.
x3/4, swapping the last two programs: cbade.
pe/b, swapping programs e and b: ceadb.
In what order are the programs standing after their billion dances?

Your puzzle answer was lgmkacfjbopednhi.

Both parts of this puzzle are complete! They provide two gold stars: **
*/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include "CommonFunctions.h"

using namespace std;

void Challenge16() {
	ifstream input;
	input.open("Input/Challenge16/Input.txt");
	string line;

	string result = "abcdefghijklmnop";

	while (getline(input, line)) {
		vector<string> tokens;
		Tokenize(line, tokens, ",");
		map<string, int> myMap;

		//We mess with the tokens vector, so keep track of an original
		vector<string> originalTokens = tokens;

		//Run the "dance" a billion times
		for (unsigned long long x = 0; x < 1000000000; x++) {
			//Log purposes
			cout << x << "\t" << result << endl;

			tokens = originalTokens;
			for (int m = 0; m < tokens.size(); m++) {
				//Parse the tokens to separate the current move from the indices
				char move = tokens[m][0];
				tokens[m].erase(0, 1);

				//s5 moves the last 5 letters to the front. s3 moves the last 3 letters to the front.
				if (move == 's') {
					int x = stoi(tokens[m]);
					string left = result.substr(result.size() - x, x);
					string right = result.substr(0, result.size() - x);
					result = left + right;
				}
				//x1/3 swaps whatever is in indices 1 and 3
				else if (move == 'x') {
					vector<string> swapPrograms;
					Tokenize(tokens[m], swapPrograms, "/");
					char temp = result[stoi(swapPrograms[0])];
					result[stoi(swapPrograms[0])] = result[stoi(swapPrograms[1])];
					result[stoi(swapPrograms[1])] = temp;
				}
				//pa/b swaps the letters a and b
				else if (move == 'p') {
					vector<string> swapPrograms;
					Tokenize(tokens[m], swapPrograms, "/");
					for (int n = 0; n < result.length(); n++) {
						if (result[n] == swapPrograms[0][0])
							result[n] = swapPrograms[1][0];
						else if (result[n] == swapPrograms[1][0])
							result[n] = swapPrograms[0][0];
					}
				}
			}

			//Skip the majority of the work if we have come across a permutation that already exists
			if (myMap.find(result) != myMap.end()) {
				unsigned long long temp = x - myMap[result];
				while (x + temp < 1000000000)
					x += temp;
			}
			myMap[result] = x;
		}

		cout << "Final Permutation : ";
		cout << result << endl;
	}


}