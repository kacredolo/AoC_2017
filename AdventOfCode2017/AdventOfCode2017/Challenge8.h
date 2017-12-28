#pragma once
/*

Rank Part 1 : 526
Time Part 1 : 00 : 16 : 29

Rank Part 2 : 505
Time Part 2 : 00 : 18 : 05

Notes : Part 2 of today was only a minor change to part 1. Caught me off guard how small of a task it asked.


--- Day 8: I Heard You Like Registers ---

You receive a signal directly from the CPU. Because of your recent assistance with jump instructions, it would like you to compute the result of a series of unusual register instructions.

Each instruction consists of several parts: the register to modify, whether to increase or decrease that register's value, the amount by which to increase or decrease it, and a condition. If the condition fails, skip the instruction without modifying the register. The registers all start at 0. The instructions look like this:

b inc 5 if a > 1
a inc 1 if b < 5
c dec -10 if a >= 1
c inc -20 if c == 10
These instructions would be processed as follows:

Because a starts at 0, it is not greater than 1, and so b is not modified.
a is increased by 1 (to 1) because b is less than 5 (it is 0).
c is decreased by -10 (to 10) because a is now greater than or equal to 1 (it is 1).
c is increased by -20 (to -10) because c is equal to 10.
After this process, the largest value in any register is 1.

You might also encounter <= (less than or equal to) or != (not equal to). However, the CPU doesn't have the bandwidth to tell you what all the registers are named, and leaves that to you to determine.

What is the largest value in any register after completing the instructions in your puzzle input?

Your puzzle answer was 4647.

--- Part Two ---

To be safe, the CPU also needs to know the highest value held in any register during this process so that it can decide how much memory to allocate to these operations. For example, in the above instructions, the highest value ever held was 10 (in register c after the third instruction was evaluated).

Your puzzle answer was 5590.

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

void Challenge8() {
	ifstream input;
	input.open("Input/Challenge8/Input.txt");
	string line;

	int part2Answer = 0;
	map<string, int> myMap;
	while (getline(input, line)) {

		vector<string> v;
		Tokenize(line, v, " ");

		//Make sure the relevant indicies are instantiated
		myMap.emplace(std::pair<string, int>(v[0], 0));
		myMap.emplace(std::pair<string, int>(v[4], 0));

		//Whether it asks to "inc" or "dec" the index
		int multiplier = v[1] == "inc" ? 1 : -1;

		//Parse the equation to see if we need to change the index
		if (v[5] == "<" && myMap[v[4]] < stoi(v[6]))
			myMap[v[0]] += multiplier * stoi(v[2]);
		else if (v[5] == ">" && myMap[v[4]] > stoi(v[6]))
			myMap[v[0]] += multiplier * stoi(v[2]);
		else if (v[5] == "<=" && myMap[v[4]] <= stoi(v[6]))
			myMap[v[0]] += multiplier * stoi(v[2]);
		else if (v[5] == ">=" && myMap[v[4]] >= stoi(v[6]))
			myMap[v[0]] += multiplier * stoi(v[2]);
		else if (v[5] == "==" && myMap[v[4]] == stoi(v[6]))
			myMap[v[0]] += multiplier * stoi(v[2]);
		else if (v[5] == "!=" && myMap[v[4]] != stoi(v[6]))
			myMap[v[0]] += multiplier * stoi(v[2]);

		//Part 2, keep track of the largest number encountered through the process
		if (myMap[v[0]] > part2Answer)
			part2Answer = myMap[v[0]];
	}

	//Part 1, find the largest number contained in the map
	int greatestNum = myMap.begin()->second;
	for (map<string, int>::iterator it = myMap.begin(); it != myMap.end(); it++) {
		if (it->second > greatestNum)
			greatestNum = it->second;
	}

	//Part 1 Answer
	cout << greatestNum << endl;

	//Part 2 Answer
	cout << part2Answer << endl;
}