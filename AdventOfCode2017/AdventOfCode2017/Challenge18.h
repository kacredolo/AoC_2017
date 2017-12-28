#pragma once
#pragma once
/*
Rank Part 1 : 656
Time Part 1 : 00 : 42 : 14

Rank Part 2 : 832
Time Part 2 : 03 : 23 : 22

Notes : This one was NOT easy. Seems straight forward enough, but whether my code was bugged or that we needed 64 bit variables or that it just took forever to run. It got hard.

--- Day 18: Duet ---
You discover a tablet containing some strange assembly code labeled simply "Duet". Rather than bother the sound card with it, you decide to run the code yourself. Unfortunately, you don't see any documentation, so you're left to figure out what the instructions mean on your own.

It seems like the assembly is meant to operate on a set of registers that are each named with a single letter and that can each hold a single integer. You suppose each register should start with a value of 0.

There aren't that many instructions, so it shouldn't be hard to figure out what they do. Here's what you determine:

snd X plays a sound with a frequency equal to the value of X.
set X Y sets register X to the value of Y.
add X Y increases register X by the value of Y.
mul X Y sets register X to the result of multiplying the value contained in register X by the value of Y.
mod X Y sets register X to the remainder of dividing the value contained in register X by the value of Y (that is, it sets X to the result of X modulo Y).
rcv X recovers the frequency of the last sound played, but only when the value of X is not zero. (If it is zero, the command does nothing.)
jgz X Y jumps with an offset of the value of Y, but only if the value of X is greater than zero. (An offset of 2 skips the next instruction, an offset of -1 jumps to the previous instruction, and so on.)
Many of the instructions can take either a register (a single letter) or a number. The value of a register is the integer it contains; the value of a number is that number.

After each jump instruction, the program continues with the instruction to which the jump jumped. After any other instruction, the program continues with the next instruction. Continuing (or jumping) off either end of the program terminates it.

For example:

set a 1
add a 2
mul a a
mod a 5
snd a
set a 0
rcv a
jgz a -1
set a 1
jgz a -2
The first four instructions set a to 1, add 2 to it, square it, and then set it to itself modulo 5, resulting in a value of 4.
Then, a sound with frequency 4 (the value of a) is played.
After that, a is set to 0, causing the subsequent rcv and jgz instructions to both be skipped (rcv because a is 0, and jgz because a is not greater than 0).
Finally, a is set to 1, causing the next jgz instruction to activate, jumping back two instructions to another jump, which jumps again to the rcv, which ultimately triggers the recover operation.
At the time the recover operation is executed, the frequency of the last sound played is 4.

What is the value of the recovered frequency (the value of the most recently played sound) the first time a rcv instruction is executed with a non-zero value?

Your puzzle answer was 2951.

--- Part Two ---
As you congratulate yourself for a job well done, you notice that the documentation has been on the back of the tablet this entire time. While you actually got most of the instructions correct, there are a few key differences. This assembly code isn't about sound at all - it's meant to be run twice at the same time.

Each running copy of the program has its own set of registers and follows the code independently - in fact, the programs don't even necessarily run at the same speed. To coordinate, they use the send (snd) and receive (rcv) instructions:

snd X sends the value of X to the other program. These values wait in a queue until that program is ready to receive them. Each program has its own message queue, so a program can never receive a message it sent.
rcv X receives the next value and stores it in register X. If no values are in the queue, the program waits for a value to be sent to it. Programs do not continue to the next instruction until they have received a value. Values are received in the order they are sent.
Each program also has its own program ID (one 0 and the other 1); the register p should begin with this value.

For example:

snd 1
snd 2
snd p
rcv a
rcv b
rcv c
rcv d
Both programs begin by sending three values to the other. Program 0 sends 1, 2, 0; program 1 sends 1, 2, 1. Then, each program receives a value (both 1) and stores it in a, receives another value (both 2) and stores it in b, and then each receives the program ID of the other program (program 0 receives 1; program 1 receives 0) and stores it in c. Each program now sees a different value in its own copy of register c.

Finally, both programs try to rcv a fourth time, but no data is waiting for either of them, and they reach a deadlock. When this happens, both programs terminate.

It should be noted that it would be equally valid for the programs to run at different speeds; for example, program 0 might have sent all three values and then stopped at the first rcv before program 1 executed even its first instruction.

Once both of your programs have terminated (regardless of what caused them to do so), how many times did program 1 send a value?

Your puzzle answer was 7366.

Both parts of this puzzle are complete! They provide two gold stars: **



*/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <queue>
#include "CommonFunctions.h"

using namespace std;

//Avoid string compares
enum class Instruction {snd, set, add, mul, mod, rcv, jgz};

//Parse the input and section the important data
struct Job {
	Instruction i;
	string origin;
	string second;

	Job(string &line)
	{
		stringstream ss(line);
		string inst;
		ss >> inst >> origin >> second;
		if (inst == "snd")
			i = Instruction::snd;
		else if (inst == "set")
			i = Instruction::set;
		else if (inst == "add")
			i = Instruction::add;
		else if (inst == "mul")
			i = Instruction::mul;
		else if (inst == "mod")
			i = Instruction::mod;
		else if (inst == "rcv")
			i = Instruction::rcv;
		else if (inst == "jgz")
			i = Instruction::jgz;
	}
};
//int64_t GetValue(map<string, int64_t> &m, string s);
int RunJob(map<string, int64_t> &m, Job &j, queue<int64_t> &q1, queue<int64_t> &q2, int &count);

void Challenge18() {
	ifstream input;
	input.open("Input/Challenge18/Input.txt");
	string line;
	
	vector<Job> commands;
	while (getline(input, line)) {		
		commands.push_back(line);
	}

	int index1 = 0;
	int index2 = 0;
	queue<int64_t> q1, q2;
	int timesSent1 = 0;
	int timesSent2 = 0;
	map<string, int64_t> myMap1;
	map<string, int64_t> myMap2;
	myMap1["p"] = 0;
	myMap2["p"] = 1;

	//Continue until a deadlock occurs, where both programs are waiting for data from each other 
	while (commands[index1].i != Instruction::rcv || q1.empty() == false 
		|| commands[index2].i != Instruction::rcv || q2.empty() == false) {
		//Run program one until it is waiting for data from program two
		while (commands[index1].i != Instruction::rcv || q1.empty() == false) {
			index1 += RunJob(myMap1, commands[index1], q1, q2, timesSent1);
		}
		//Run program two until it is waiting for data from program one
		while (commands[index2].i != Instruction::rcv || q2.empty() == false) {
			index2 += RunJob(myMap2, commands[index2], q2, q1, timesSent2);
		}
	}

	cout << "Part 2 Answer, Program 1 Sends : " << timesSent2 << endl;

}

//Handles all the specific instructions. Add, Mod, Jump, Send, etc.
int RunJob(map<string, int64_t> &m, Job &j, queue<int64_t> &q1, queue<int64_t> &q2, int &count) {
	//We return index delta, which will ultimately move the index further into the commands
	int indexDelta = 1;
	switch (j.i) {
	case Instruction::add:
		m[j.origin] += GetValue(m, j.second);
		break;
	case Instruction::set:
		m[j.origin] = GetValue(m, j.second);
		break;
	case Instruction::mod:
		m[j.origin] %= GetValue(m, j.second);
		break;
	case Instruction::mul:
		m[j.origin] *= GetValue(m, j.second);
		break;
	case Instruction::jgz:
		if (GetValue(m, j.origin) > 0)
			indexDelta = GetValue(m, j.second);
		break;
	case Instruction::snd:
		//q2 is always the opposite queue in this function
		q2.push(GetValue(m, j.origin));
		//This is where we are getting our answer
		count++;
		break;
	case Instruction::rcv:
		m[j.origin] = q1.front();
		q1.pop();
		break;
	}
	return indexDelta;
}

/*
Moved to CommonFunctions
//Check if an input is a number or a register that contains a number. Return a number either way.
int64_t GetValue(map<string, int64_t> &m, string s) {
	if (s[0] >= 'a' && s[0] <= 'z')
		return m[s];
	return stoi(s);
}
*/