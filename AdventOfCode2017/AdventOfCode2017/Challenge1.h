#pragma once
/*

Rank Part 1 : 18086
Time Part 1 : 22:01:20

Rank Part 2 : 15055
Time Part 2 : 22:13:44

Notes: It started early! I thought it was starting on the first, but I didn't realize it was at MIDNIGHT of Nov. 30

--- Day 1: Inverse Captcha ---

The night before Christmas, one of Santa's Elves calls you in a panic. "The printer's broken! We can't print the Naughty or Nice List!" By the time you make it to sub-basement 17, there are only a few minutes until midnight. "We have a big problem," she says; "there must be almost fifty bugs in this system, but nothing else can print The List. Stand in this square, quick! There's no time to explain; if you can convince them to pay you in stars, you'll be able to--" She pulls a lever and the world goes blurry.

When your eyes can focus again, everything seems a lot more pixelated than before. She must have sent you inside the computer! You check the system clock: 25 milliseconds until midnight. With that much time, you should be able to collect all fifty stars by December 25th.

Collect stars by solving puzzles. Two puzzles will be made available on each day millisecond in the advent calendar; the second puzzle is unlocked when you complete the first. Each puzzle grants one star. Good luck!

You're standing in a room with "digitization quarantine" written in LEDs along one wall. The only door is locked, but it includes a small interface. "Restricted Area - Strictly No Digitized Users Allowed."

It goes on to explain that you may only leave by solving a captcha to prove you're not a human. Apparently, you only get one millisecond to solve the captcha: too fast for a normal human, but it feels like hours to you.

The captcha requires you to review a sequence of digits (your puzzle input) and find the sum of all digits that match the next digit in the list. The list is circular, so the digit after the last digit is the first digit in the list.

For example:

1122 produces a sum of 3 (1 + 2) because the first digit (1) matches the second digit and the third digit (2) matches the fourth digit.
1111 produces 4 because each digit (all 1) matches the next.
1234 produces 0 because no digit matches the next.
91212129 produces 9 because the only digit that matches the next one is the last digit, 9.
What is the solution to your captcha?

Your puzzle answer was 995.

--- Part Two ---

You notice a progress bar that jumps to 50% completion. Apparently, the door isn't yet satisfied, but it did emit a star as encouragement. The instructions change:

Now, instead of considering the next digit, it wants you to consider the digit halfway around the circular list. That is, if your list contains 10 items, only include a digit in your sum if the digit 10/2 = 5 steps forward matches it. Fortunately, your list has an even number of elements.

For example:

1212 produces 6: the list contains 4 items, and all four digits match the digit 2 items ahead.
1221 produces 0, because every comparison is between a 1 and a 2.
123425 produces 4, because both 2s match each other, but no other digit has a match.
123123 produces 12.
12131415 produces 4.
What is the solution to your new captcha?

Your puzzle answer was 1130.

Both parts of this puzzle are complete! They provide two gold stars: **
*/

#include <iostream>
#include <string>
#include <fstream>
#include "CommonFunctions.h"

using namespace std;

void Challenge1() {
	ifstream input;
	input.open("Input/Challenge1/Input.txt");
	string line;

	getline(input, line);

	//PART 1
	//Corner case of the cyclical array, check if first and last digits are the same
	long result1 = line[0] == line[line.length() - 1] ? line[0] - '0' : 0;

	for (string::iterator it = line.begin(); it != line.end() - 1; it++) {
		if (*it == *(it + 1))
			result1 += *it - '0';
	}

	cout << "Part 1 : "<< result1 << endl;

	//PART 2
	int stepSize = line.length() / 2;

	long result2 = 0;

	int first, last;
	for (first = 0, last = stepSize; first < line.length(); first++) {
		if (line[first] == line[last])
			result2 += line[first] - '0';

		// Since the variable "last" is ahead of the "first" variable, make sure to loop it to the start
		last++;
		if (last == line.length())
			last = 0;
	}

	cout << "Part 2 : "<< result2 << endl;
}
