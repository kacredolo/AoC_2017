#pragma once
/*
Rank Part 1 : 780
Time Part 1 : 00:08:45

Rank Part 2 : 775
Time Part 2 : 00:16:35

Notes : Easy one that could be a tutorial for map/set. It's clear that there's a LOT more people this year compared to last. That's pretty cool.

--- Day 4: High-Entropy Passphrases ---

A new system policy has been put in place that requires all accounts to use a passphrase instead of simply a password. A passphrase consists of a series of words (lowercase letters) separated by spaces.

To ensure security, a valid passphrase must contain no duplicate words.

For example:

aa bb cc dd ee is valid.
aa bb cc dd aa is not valid - the word aa appears more than once.
aa bb cc dd aaa is valid - aa and aaa count as different words.
The system's full passphrase list is available as your puzzle input. How many passphrases are valid?

Your puzzle answer was 477.

--- Part Two ---

For added security, yet another system policy has been put in place. Now, a valid passphrase must contain no two words that are anagrams of each other - that is, a passphrase is invalid if any word's letters can be rearranged to form any other word in the passphrase.

For example:

abcde fghij is a valid passphrase.
abcde xyz ecdab is not valid - the letters from the third word can be rearranged to form the first word.
a ab abc abd abf abj is a valid passphrase, because all letters need to be used when forming another word.
iiii oiii ooii oooi oooo is valid.
oiii ioii iioi iiio is not valid - any of these words can be rearranged to form any other word.
Under this new system policy, how many passphrases are valid?

Your puzzle answer was 167.

Both parts of this puzzle are complete! They provide two gold stars: **
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include "CommonFunctions.h"

using namespace std;

void Challenge4() {
	ifstream input;
	input.open("Input/Challenge4/Input.txt");
	string line;

	int totalValidPart1 = 0;
	int totalValidPart2 = 0;

	while (getline(input, line)) {
		set<string> mySet;
		set<string> myAnagramSet;

		vector<string> v;
		Tokenize(line, v, " \t");

		bool isValidPart1 = true;
		bool isValidPart2 = true;

		for (int m = 0; m < v.size(); m++) {
			//Check if the current token is a repeat
			if (mySet.count(v[m]) == 1) {
				isValidPart1 = false;
				isValidPart2 = false;
				break;
			}
			mySet.insert(v[m]);

			//Part 2
			//Sort the token alphabetically to check for anagrams, only for part 2
			std::sort(v[m].begin(), v[m].end());
			if (myAnagramSet.count(v[m]) == 1) {
				isValidPart2 = false;
				break;
			}
			myAnagramSet.insert(v[m]);
		}

		if (isValidPart1)
			totalValidPart1++;

		if (isValidPart2)
			totalValidPart2++;
	}

	cout << totalValidPart1 << endl;
	cout << totalValidPart2 << endl;
}