
/*
Rank Part 1 : 522
Time Part 1 : 01 : 11 : 30

Rank Part 2 : 625
Time Part 2 : 01 : 55 : 00

Notes : This one ended up slightly awkward because the way I did part 1 was completely backwards to the way part 2 needed to be done. I also had included some dynamic programming to make it more efficient, which was then thrown out for part 2.

--- Day 24: Electromagnetic Moat ---
The CPU itself is a large, black building surrounded by a bottomless pit. Enormous metal tubes extend outward from the side of the building at regular intervals and descend down into the void. There's no way to cross, but you need to get inside.

No way, of course, other than building a bridge out of the magnetic components strewn about nearby.

Each component has two ports, one on each end. The ports come in all different types, and only matching types can be connected. You take an inventory of the components by their port types (your puzzle input). Each port is identified by the number of pins it uses; more pins mean a stronger connection for your bridge. A 3/7 component, for example, has a type-3 port on one side, and a type-7 port on the other.

Your side of the pit is metallic; a perfect surface to connect a magnetic, zero-pin port. Because of this, the first port you use must be of type 0. It doesn't matter what type of port you end with; your goal is just to make the bridge as strong as possible.

The strength of a bridge is the sum of the port types in each component. For example, if your bridge is made of components 0/3, 3/7, and 7/4, your bridge has a strength of 0+3 + 3+7 + 7+4 = 24.

For example, suppose you had the following components:

0/2
2/2
2/3
3/4
3/5
0/1
10/1
9/10
With them, you could make the following valid bridges:

0/1
0/1--10/1
0/1--10/1--9/10
0/2
0/2--2/3
0/2--2/3--3/4
0/2--2/3--3/5
0/2--2/2
0/2--2/2--2/3
0/2--2/2--2/3--3/4
0/2--2/2--2/3--3/5
(Note how, as shown by 10/1, order of ports within a component doesn't matter. However, you may only use each port on a component once.)

Of these bridges, the strongest one is 0/1--10/1--9/10; it has a strength of 0+1 + 1+10 + 10+9 = 31.

What is the strength of the strongest bridge you can make with the components you have available?

Your puzzle answer was 2006.

--- Part Two ---
The bridge you've built isn't long enough; you can't jump the rest of the way.

In the example above, there are two longest bridges:

0/2--2/2--2/3--3/4
0/2--2/2--2/3--3/5
Of them, the one which uses the 3/5 component is stronger; its strength is 0+2 + 2+2 + 2+3 + 3+5 = 19.

What is the strength of the longest bridge you can make? If you can make multiple bridges of the longest length, pick the strongest one.

Your puzzle answer was 1994.

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

struct Wire {
	int a, b;
	bool used;
	Wire(string &s, map<int, vector<Wire*>> &m) {
		vector<int> tokens;
		Tokenize(s, tokens, "/");
		a = tokens[0];
		b = tokens[1];
		used = false;
	}
};

void RecSolWire(int currConn, int bridgeLength, int &maxBridgeLength, int sum, map<int, vector<Wire*>> &myMap, int &maxSum );

void Challenge24() {
	ifstream input;
	input.open("Input/Challenge24/Input.txt");
	string line;

	//Fill a map with the wires. map[0] holds all wires with a 0 connection, giving access to other indices of map[]
	map<int, vector<Wire*>> myMap;
	while (getline(input, line)) {
		Wire *temp = new Wire(line, myMap);
		myMap[temp->a].push_back(temp);
		myMap[temp->b].push_back(temp);
	}

	//Part 2 variables
	int largestBridge = 0;
	int maxSum = 0;

	//Recursive Solution
	RecSolWire(0, 0, largestBridge, 0, myMap, maxSum);

	cout << maxSum << endl;
}

void RecSolWire(int currConn, int bridgeLength, int &maxBridgeLength, int sum, map<int, vector<Wire*>> &myMap, int &maxSum) {
	
	vector<Wire*> v = myMap[currConn];

	//Check if we have reached a new max bridge length, for part 2
	if (bridgeLength > maxBridgeLength) {
		maxBridgeLength = bridgeLength;
		maxSum = 0;
	}

	for (int m = 0; m < v.size(); m++) {
		//Only access wires that aren't already being used
		if (v[m]->used == false) {
			//Set this wire to being used before the call, then being free after the call
			v[m]->used = true;
			//Find the connecting index (0:2 and we are on 2, brings us to 0)
			int nextConn = v[m]->a == currConn ? v[m]->b : v[m]->a;
			RecSolWire(nextConn, bridgeLength + 1, maxBridgeLength, sum + v[m]->a + v[m]->b, myMap, maxSum);
			v[m]->used = false;
		}
	}
	
	//Only change the answer if this bridge is as long as the longest
	if (bridgeLength == maxBridgeLength && sum > maxSum) {
		maxSum = sum;
	}
}