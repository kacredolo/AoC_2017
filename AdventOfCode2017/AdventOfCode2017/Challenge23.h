
/*
Rank Part 1 : 560
Time Part 1 : 00 : 19 : 39

Rank Part 2 : 274
Time Part 2 : 01 : 16 : 19

Notes : Part 1 was quick because most of the code was from Challenge 18. Makes sense that others were faster in just using/copying/whatever previous code quicker than me.
Part 2 was different because the question wasn't how to code it, but to understand WHAT the jobs were doing.
Took a while, but I figured out that it was finding NON-primes between two high numbers, skipping 17 each iteration.

--- Day 23: Coprocessor Conflagration ---
You decide to head directly to the CPU and fix the printer from there. As you get close, you find an experimental coprocessor doing so much work that the local programs are afraid it will halt and catch fire. This would cause serious issues for the rest of the computer, so you head in and see what you can do.

The code it's running seems to be a variant of the kind you saw recently on that tablet. The general functionality seems very similar, but some of the instructions are different:

set X Y sets register X to the value of Y.
sub X Y decreases register X by the value of Y.
mul X Y sets register X to the result of multiplying the value contained in register X by the value of Y.
jnz X Y jumps with an offset of the value of Y, but only if the value of X is not zero. (An offset of 2 skips the next instruction, an offset of -1 jumps to the previous instruction, and so on.)
Only the instructions listed above are used. The eight registers here, named a through h, all start at 0.

The coprocessor is currently set to some kind of debug mode, which allows for testing, but prevents it from doing any meaningful work.

If you run the program (your puzzle input), how many times is the mul instruction invoked?

Your puzzle answer was 3969.

--- Part Two ---
Now, it's time to fix the problem.

The debug mode switch is wired directly to register a. You flip the switch, which makes register a now start at 1 when the program is executed.

Immediately, the coprocessor begins to overheat. Whoever wrote this program obviously didn't choose a very efficient implementation. You'll need to optimize the program if it has any hope of completing before Santa needs that printer working.

The coprocessor's ultimate goal is to determine the final value left in register h once the program completes. Technically, if it had that... it wouldn't even need to run the program.

After setting register a to 1, if the program were to run to completion, what value would be left in register h?

Your puzzle answer was 917.

Both parts of this puzzle are complete! They provide two gold stars: **
*/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>
#include <sstream>
#include "CommonFunctions.h"

using namespace std;

enum class Instruction23 { set, sub, mul, jnz };

//Parse the input and section the important data
struct Job23 {
	Instruction23 i;
	string origin;
	string second;

	Job23(string &line)
	{
		stringstream ss(line);
		string inst;
		ss >> inst >> origin >> second;
		if (inst == "set")
			i = Instruction23::set;
		else if (inst == "sub")
			i = Instruction23::sub;
		else if (inst == "mul")
			i = Instruction23::mul;
		else if (inst == "jnz")
			i = Instruction23::jnz;
	}
};

int RunJob(map<string, int64_t> &m, Job23 &j, int &count);

void Challenge23() {
	ifstream input;
	input.open("Input/Challenge23/Input.txt");
	string line;

	vector<Job23> v;
	map<string, int64_t> m;
	m["a"] = 1;
	m["b"] = 0;
	m["c"] = 0;
	m["d"] = 0;
	m["e"] = 0;
	m["f"] = 0;
	m["g"] = 0;
	m["h"] = 0;

	while (getline(input, line)) {
		Job23 temp(line);
		v.push_back(temp);
	}

	//Part 1
	/*
	int mulCount = 0;
	int index = 0;
	while (index >= 0 && index < v.size()) {
		index += RunJob(m, v[index], mulCount);
	}
	cout<<mulCount<<endl;
	*/

	//Part 2 is too slow using the normal method. 
	//Parsing through it, I understood that it was discovering how many numbers between
	//106500 and 123500 (every 17th number) is NOT a prime.
	int nonPrimeCounter = 0;
	for (int n = 106500; n <= 123500; n += 17)
		nonPrimeCounter += isPrime(n) ? 0 : 1;
	cout << nonPrimeCounter << endl;
}

//Handles all the specific instructions. Add, Mod, Jump, Send, etc.
int RunJob(map<string, int64_t> &m, Job23 &j, int &count) {
	//We return index delta, which will ultimately move the index further into the commands
	int indexDelta = 1;
	switch (j.i) {
	case Instruction23::set:
		m[j.origin] = GetValue(m, j.second);
		break;
	case Instruction23::sub:
		m[j.origin] -= GetValue(m, j.second);
		break;
	case Instruction23::mul:
		m[j.origin] *= GetValue(m, j.second);
		count++;
		break;
	case Instruction23::jnz:
		if (GetValue(m, j.origin) != 0)
			indexDelta = GetValue(m, j.second);
		break;
	}
	return indexDelta;
}