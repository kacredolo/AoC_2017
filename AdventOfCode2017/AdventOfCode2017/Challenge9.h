#pragma once
/*

Rank Part 1 : 256
Time Part 1 : 00 : 14 : 10

Rank Part 2 : 232
Time Part 2 : 00 : 16 : 27

Notes : I did good with this one! I initially did it with stacks. Probably because of the typical open-closed bracket approach to check for nested brackets.

--- Day 9: Stream Processing ---

A large stream blocks your path. According to the locals, it's not safe to cross the stream at the moment because it's full of garbage. You look down at the stream; rather than water, you discover that it's a stream of characters.

You sit for a while and record part of the stream (your puzzle input). The characters represent groups - sequences that begin with { and end with }. Within a group, there are zero or more other things, separated by commas: either another group or garbage. Since groups can contain other groups, a } only closes the most-recently-opened unclosed group - that is, they are nestable. Your puzzle input represents a single, large group which itself contains many smaller ones.

Sometimes, instead of a group, you will find garbage. Garbage begins with < and ends with >. Between those angle brackets, almost any character can appear, including { and }. Within garbage, < has no special meaning.

In a futile attempt to clean up the garbage, some program has canceled some of the characters within it using !: inside garbage, any character that comes after ! should be ignored, including <, >, and even another !.

You don't see any characters that deviate from these rules. Outside garbage, you only find well-formed groups, and garbage always terminates according to the rules above.

Here are some self-contained pieces of garbage:

<>, empty garbage.
<random characters>, garbage containing random characters.
<<<<>, because the extra < are ignored.
<{!>}>, because the first > is canceled.
<!!>, because the second ! is canceled, allowing the > to terminate the garbage.
<!!!>>, because the second ! and the first > are canceled.
<{o"i!a,<{i<a>, which ends at the first >.
Here are some examples of whole streams and the number of groups they contain:

{}, 1 group.
{{{}}}, 3 groups.
{{},{}}, also 3 groups.
{{{},{},{{}}}}, 6 groups.
{<{},{},{{}}>}, 1 group (which itself contains garbage).
{<a>,<a>,<a>,<a>}, 1 group.
{{<a>},{<a>},{<a>},{<a>}}, 5 groups.
{{<!>},{<!>},{<!>},{<a>}}, 2 groups (since all but the last > are canceled).
Your goal is to find the total score for all groups in your input. Each group is assigned a score which is one more than the score of the group that immediately contains it. (The outermost group gets a score of 1.)

{}, score of 1.
{{{}}}, score of 1 + 2 + 3 = 6.
{{},{}}, score of 1 + 2 + 2 = 5.
{{{},{},{{}}}}, score of 1 + 2 + 3 + 3 + 3 + 4 = 16.
{<a>,<a>,<a>,<a>}, score of 1.
{{<ab>},{<ab>},{<ab>},{<ab>}}, score of 1 + 2 + 2 + 2 + 2 = 9.
{{<!!>},{<!!>},{<!!>},{<!!>}}, score of 1 + 2 + 2 + 2 + 2 = 9.
{{<a!>},{<a!>},{<a!>},{<ab>}}, score of 1 + 2 = 3.
What is the total score for all groups in your input?

Your puzzle answer was 21037.

--- Part Two ---

Now, you're ready to remove the garbage.

To prove you've removed it, you need to count all of the characters within the garbage. The leading and trailing < and > don't count, nor do any canceled characters or the ! doing the canceling.

<>, 0 characters.
<random characters>, 17 characters.
<<<<>, 3 characters.
<{!>}>, 2 characters.
<!!>, 0 characters.
<!!!>>, 0 characters.
<{o"i!a,<{i<a>, 10 characters.
How many non-canceled characters are within the garbage in your puzzle input?

Your puzzle answer was 9495.

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

void Challenge9() {
	ifstream input;
	input.open("Input/Challenge9/Input.txt");
	string line;

	int groupCounter = 0;
	bool isGarbage = false;

	while (getline(input, line)) {

		int totalPart1 = 0;
		int totalPart2 = 0;

		for (string::iterator it = line.begin(); it != line.end(); it++) {
			//Skip the character after an '!'
			if (*it == '!')
				it++;
			//Check if we are entering garbage (but count '<' as garbage if we are already in garbage)
			else if (*it == '<' && isGarbage == false)
				isGarbage = true;
			//Exiting garbage
			else if (*it == '>' && isGarbage)
				isGarbage = false;
			//A new nested group
			else if (*it == '{' && isGarbage == false)
				groupCounter++;
			//Closing a group, add the counter to the sum and decrement the counter
			else if (*it == '}' && isGarbage == false) {
				totalPart1 += groupCounter;
				groupCounter--;
			}
			//Part 2, count all characters (aside from above if-statements) in garbage
			else if (isGarbage) {
				totalPart2++;
			}
		}
		cout << totalPart1 << endl;
		cout << totalPart2 << endl;
	}
}