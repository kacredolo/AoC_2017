
/*
Rank Part 1 : 1187
Time Part 1 : 02 : 59 : 39

Rank Part 2 : 1316
Time Part 2 : 04 : 17 : 23

Notes : I was late by 2-3 hours on this one. It was a hard one either way!
Part 1 wasn't too bad. But Part 2 needed it ran 1000x longer than part 1 which made my solution MUCH too slow.
There was probably a way to find out if the virus repeats, but I was engrossed in my solution and in the end I changed from map to unordered_map and had to include a Boost Hash function for pair<int, int>

--- Day 22: Sporifica Virus ---
Diagnostics indicate that the local grid computing cluster has been contaminated with the Sporifica Virus. The grid computing cluster is a seemingly-infinite two-dimensional grid of compute nodes. Each node is either clean or infected by the virus.

To prevent overloading the nodes (which would render them useless to the virus) or detection by system administrators, exactly one virus carrier moves through the network, infecting or cleaning nodes as it moves. The virus carrier is always located on a single node in the network (the current node) and keeps track of the direction it is facing.

To avoid detection, the virus carrier works in bursts; in each burst, it wakes up, does some work, and goes back to sleep. The following steps are all executed in order one time each burst:

If the current node is infected, it turns to its right. Otherwise, it turns to its left. (Turning is done in-place; the current node does not change.)
If the current node is clean, it becomes infected. Otherwise, it becomes cleaned. (This is done after the node is considered for the purposes of changing direction.)
The virus carrier moves forward one node in the direction it is facing.
Diagnostics have also provided a map of the node infection status (your puzzle input). Clean nodes are shown as .; infected nodes are shown as #. This map only shows the center of the grid; there are many more nodes beyond those shown, but none of them are currently infected.

The virus carrier begins in the middle of the map facing up.

For example, suppose you are given a map like this:

..#
#..
...
Then, the middle of the infinite grid looks like this, with the virus carrier's position marked with [ ]:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . # . . .
. . . #[.]. . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
The virus carrier is on a clean node, so it turns left, infects the node, and moves left:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . # . . .
. . .[#]# . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
The virus carrier is on an infected node, so it turns right, cleans the node, and moves up:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . .[.]. # . . .
. . . . # . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
Four times in a row, the virus carrier finds a clean, infects it, turns left, and moves forward, ending in the same place and still facing up:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . #[#]. # . . .
. . # # # . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
Now on the same node as before, it sees an infection, which causes it to turn right, clean the node, and move forward:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . # .[.]# . . .
. . # # # . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
After the above actions, a total of 7 bursts of activity had taken place. Of them, 5 bursts of activity caused an infection.

After a total of 70, the grid looks like this, with the virus carrier facing up:

. . . . . # # . .
. . . . # . . # .
. . . # . . . . #
. . # . #[.]. . #
. . # . # . . # .
. . . . . # # . .
. . . . . . . . .
. . . . . . . . .
By this time, 41 bursts of activity caused an infection (though most of those nodes have since been cleaned).

After a total of 10000 bursts of activity, 5587 bursts will have caused an infection.

Given your actual map, after 10000 bursts of activity, how many bursts cause a node to become infected? (Do not count nodes that begin infected.)

Your puzzle answer was 5433.

--- Part Two ---
As you go to remove the virus from the infected nodes, it evolves to resist your attempt.

Now, before it infects a clean node, it will weaken it to disable your defenses. If it encounters an infected node, it will instead flag the node to be cleaned in the future. So:

Clean nodes become weakened.
Weakened nodes become infected.
Infected nodes become flagged.
Flagged nodes become clean.
Every node is always in exactly one of the above states.

The virus carrier still functions in a similar way, but now uses the following logic during its bursts of action:

Decide which way to turn based on the current node:
If it is clean, it turns left.
If it is weakened, it does not turn, and will continue moving in the same direction.
If it is infected, it turns right.
If it is flagged, it reverses direction, and will go back the way it came.
Modify the state of the current node, as described above.
The virus carrier moves forward one node in the direction it is facing.
Start with the same map (still using . for clean and # for infected) and still with the virus carrier starting in the middle and facing up.

Using the same initial state as the previous example, and drawing weakened as W and flagged as F, the middle of the infinite grid looks like this, with the virus carrier's position again marked with [ ]:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . # . . .
. . . #[.]. . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
This is the same as before, since no initial nodes are weakened or flagged. The virus carrier is on a clean node, so it still turns left, instead weakens the node, and moves left:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . # . . .
. . .[#]W . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
The virus carrier is on an infected node, so it still turns right, instead flags the node, and moves up:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . .[.]. # . . .
. . . F W . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
This process repeats three more times, ending on the previously-flagged node and facing right:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . W W . # . . .
. . W[F]W . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
Finding a flagged node, it reverses direction and cleans the node:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . W W . # . . .
. .[W]. W . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
The weakened node becomes infected, and it continues in the same direction:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . W W . # . . .
.[.]# . W . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
Of the first 100 bursts, 26 will result in infection. Unfortunately, another feature of this evolved virus is speed; of the first 10000000 bursts, 2511944 will result in infection.

Given your actual map, after 10000000 bursts of activity, how many bursts cause a node to become infected? (Do not count nodes that begin infected.)

Your puzzle answer was 2512599.

Both parts of this puzzle are complete! They provide two gold stars: **
*/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <time.h>
#include <boost/functional/hash.hpp>
#include "CommonFunctions.h"

using namespace std;

enum { Clean, Weakened, Infected, Flagged };
struct Virus {
	pair<int, int> position;
	int direction;
	int64_t timesInfected;

	Virus(int x, int y) {
		position.first = y;
		position.second = x;

		direction = north;
		timesInfected = 0;
	}

	int64_t GetResult() {
		return timesInfected;
	}

	void Burst(unordered_map<pair<int, int>, int, boost::hash<std::pair<int, int>>> &m) {
		ChangeDirection(m);
		SwapInfectionStatus(m);
		MoveForward(m);
	}

	//Turn left if infected
	//Turn right if clean
	//Reverse direction if flagged
	void ChangeDirection(unordered_map<pair<int, int>, int, boost::hash<std::pair<int, int>>> &m) {
		if (m[position] == Infected) {
			switch (direction) {
			case north:
				direction = east;
				break;
			case west:
				direction = north;
				break;
			case south:
				direction = west;
				break;
			case east:
				direction = south;
				break;
			}
		}
		else if (m[position] == Clean) {
			switch (direction) {
			case north:
				direction = west;
				break;
			case west:
				direction = south;
				break;
			case south:
				direction = east;
				break;
			case east:
				direction = north;
				break;
			}
		}
		else if (m[position] == Flagged) {
			switch (direction) {
			case north:
				direction = south;
				break;
			case west:
				direction = east;
				break;
			case south:
				direction = north;
				break;
			case east:
				direction = west;
				break;
			}
		}
	}

	//Part 2 added Weakened and Flagged states. 
	//Clean -> Weakened -> Infected -> Flagged -> Clean
	void SwapInfectionStatus(unordered_map<pair<int, int>, int, boost::hash<std::pair<int, int>>> &m) {
		switch (m[position]) {
		case Clean:
			m[position] = Weakened;
			break;
		case Weakened:
			m[position] = Infected;
			timesInfected++;
			break;
		case Infected:
			m[position] = Flagged;
			break;
		case Flagged:
			m[position] = Clean;
			break;
		}
	}

	//Move in the direction the virus is facing
	void MoveForward(unordered_map<pair<int, int>, int, boost::hash<std::pair<int, int>>> &m) {
		switch (direction) {
		case north:
			position.first--;
			break;
		case west:
			position.second--;
			break;
		case south:
			position.first++;
			break;
		case east:
			position.second++;
			break;
		}
		m.emplace(position, Clean);
	}
};

void Challenge22() {
	ifstream input;
	input.open("Input/Challenge22/Input.txt");
	string line;

	//Unordered_map is much faster when we aren't going to iterate
	//Use a custom hash function for pair<int, int> for it to work
	unordered_map<pair<int, int>, int, boost::hash<std::pair<int, int>>> grid;

	//Parse the input
	vector<string> inputGrid;
	while (getline(input, line)) {
		inputGrid.push_back(line);
		for (int m = 0; m < line.length(); m++) {
			pair<int, int> temp = { (int)inputGrid.size() - 1, m };
			grid[temp] = inputGrid[(int)inputGrid.size() - 1][m] == '#' ? Infected : Clean;
		}
	}

	Virus v((int)inputGrid[0].size() / 2, (int)inputGrid.size() / 2);

	time_t t = time(NULL);
	for (int64_t m = 0; m < 10000000; m++) {
		//Logging
		if (m % 100000 == 0) {
			cout << "Progress : " << m << " / 10000000" << endl;
			cout << "Seconds Since Last 100k : " << difftime(time(NULL), t) << endl << endl;
			t = time(NULL);
		}
		v.Burst(grid);
	}

	//Output how many times was a node infected
	cout << v.GetResult() << endl;
}