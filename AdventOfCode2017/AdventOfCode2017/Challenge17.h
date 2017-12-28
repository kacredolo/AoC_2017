#pragma once
/*
Rank Part 1 : 640
Time Part 1 : 00 : 20 : 36

Rank Part 2 : 390
Time Part 2 : 00 : 30 : 43

Notes : People seem to be getting faster instead of slower. One thing I've noticed with these competitions is
that the difficulty of a problem is tied exponentially to the quickness of peoples solutions. Easy problems make quick solutions, hard problems take longer
Whereas I am more consistent regardless of the difficulty. I take 10 minutes on the easy problems, but also 10 minutes on the harder problems.
I liked todays problem.

--- Day 17: Spinlock ---
Suddenly, whirling in the distance, you notice what looks like a massive, pixelated hurricane: a deadly spinlock. This spinlock isn't just consuming computing power, but memory, too; vast, digital mountains are being ripped from the ground and consumed by the vortex.

If you don't move quickly, fixing that printer will be the least of your problems.

This spinlock's algorithm is simple but efficient, quickly consuming everything in its path. It starts with a circular buffer containing only the value 0, which it marks as the current position. It then steps forward through the circular buffer some number of steps (your puzzle input) before inserting the first new value, 1, after the value it stopped on. The inserted value becomes the current position. Then, it steps forward from there the same number of steps, and wherever it stops, inserts after it the second new value, 2, and uses that as the new current position again.

It repeats this process of stepping forward, inserting a new value, and using the location of the inserted value as the new current position a total of 2017 times, inserting 2017 as its final operation, and ending with a total of 2018 values (including 0) in the circular buffer.

For example, if the spinlock were to step 3 times per insert, the circular buffer would begin to evolve like this (using parentheses to mark the current position after each iteration of the algorithm):

(0), the initial state before any insertions.
0 (1): the spinlock steps forward three times (0, 0, 0), and then inserts the first value, 1, after it. 1 becomes the current position.
0 (2) 1: the spinlock steps forward three times (0, 1, 0), and then inserts the second value, 2, after it. 2 becomes the current position.
0  2 (3) 1: the spinlock steps forward three times (1, 0, 2), and then inserts the third value, 3, after it. 3 becomes the current position.
And so on:

0  2 (4) 3  1
0 (5) 2  4  3  1
0  5  2  4  3 (6) 1
0  5 (7) 2  4  3  6  1
0  5  7  2  4  3 (8) 6  1
0 (9) 5  7  2  4  3  8  6  1
Eventually, after 2017 insertions, the section of the circular buffer near the last insertion looks like this:

1512  1134  151 (2017) 638  1513  851
Perhaps, if you can identify the value that will ultimately be after the last value written (2017), you can short-circuit the spinlock. In this example, that would be 638.

What is the value after 2017 in your completed circular buffer?

Your puzzle answer was 1561.

--- Part Two ---
The spinlock does not short-circuit. Instead, it gets more angry. At least, you assume that's what happened; it's spinning significantly faster than it was a moment ago.

You have good news and bad news.

The good news is that you have improved calculations for how to stop the spinlock. They indicate that you actually need to identify the value after 0 in the current state of the circular buffer.

The bad news is that while you were determining this, the spinlock has just finished inserting its fifty millionth value (50000000).

What is the value after 0 the moment 50000000 is inserted?

Your puzzle answer was 33454823.

Both parts of this puzzle are complete! They provide two gold stars: **

At this point, you should return to your advent calendar and try another puzzle.

Your puzzle input was 382.
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

void Challenge17() {
	ifstream input;
	input.open("Input/Challenge17/Input.txt");
	string line;

	while (getline(input, line)) {
		vector<string> tokens;
		Tokenize(line, tokens, ",");

		int i = stoi(tokens[0]);

		vector<int> v(1, 0);
		vector<int>::iterator it = v.begin();
		for (int m = 1; m <= 2017; m++) {
			for (int n = 0; n < i; n++) {
				it++;
				if (it == v.end())
					it = v.begin();
			}
			it++;
			it = v.insert(it, m);
		}

		//Part 1 Output : The number that resides right after the last inserted step
		cout << "Part 1 : " << *(it + 1) << endl;
		
		//Part 2, circumvent the process and avoid vectors. 
		//All we need to know is if a new number would be inserted right after 0
		long long zeroIndex = 0;
		long long currIndex = 0;
		long long numberAfter0 = 0;
		for (long long m = 1; m < 50000000; m++) {
			currIndex = ((currIndex + i) % m) + 1;
			if (currIndex == zeroIndex)
				zeroIndex++;
			else if (currIndex == zeroIndex + 1) {
				numberAfter0 = m;
			}
		}
		cout << numberAfter0 << endl;
	}
}