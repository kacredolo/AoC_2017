
/*
Rank Part 1 : 379
Time Part 1 : 00 : 23 : 45

Rank Part 2 : 622
Time Part 2 : 01 : 14 : 08

Notes : I was late by 10 or so minutes on this one, but I did pretty well on Part 1 anyways. And then I ROYALLY SCREWED myself on part 2 because I didn't read what the question wanted as an answer. I kept giving Part1's answer but with collisions involved.
I'm using OO techniques more often now.

--- Day 20: Particle Swarm ---
Suddenly, the GPU contacts you, asking for help. Someone has asked it to simulate too many particles, and it won't be able to finish them all in time to render the next frame at this rate.

It transmits to you a buffer (your puzzle input) listing each particle in order (starting with particle 0, then particle 1, particle 2, and so on). For each particle, it provides the X, Y, and Z coordinates for the particle's position (p), velocity (v), and acceleration (a), each in the format <X,Y,Z>.

Each tick, all particles are updated simultaneously. A particle's properties are updated in the following order:

Increase the X velocity by the X acceleration.
Increase the Y velocity by the Y acceleration.
Increase the Z velocity by the Z acceleration.
Increase the X position by the X velocity.
Increase the Y position by the Y velocity.
Increase the Z position by the Z velocity.
Because of seemingly tenuous rationale involving z-buffering, the GPU would like to know which particle will stay closest to position <0,0,0> in the long term. Measure this using the Manhattan distance, which in this situation is simply the sum of the absolute values of a particle's X, Y, and Z position.

For example, suppose you are only given two particles, both of which stay entirely on the X-axis (for simplicity). Drawing the current states of particles 0 and 1 (in that order) with an adjacent a number line and diagram of current X positions (marked in parenthesis), the following would take place:

p=< 3,0,0>, v=< 2,0,0>, a=<-1,0,0>    -4 -3 -2 -1  0  1  2  3  4
p=< 4,0,0>, v=< 0,0,0>, a=<-2,0,0>                         (0)(1)

p=< 4,0,0>, v=< 1,0,0>, a=<-1,0,0>    -4 -3 -2 -1  0  1  2  3  4
p=< 2,0,0>, v=<-2,0,0>, a=<-2,0,0>                      (1)   (0)

p=< 4,0,0>, v=< 0,0,0>, a=<-1,0,0>    -4 -3 -2 -1  0  1  2  3  4
p=<-2,0,0>, v=<-4,0,0>, a=<-2,0,0>          (1)               (0)

p=< 3,0,0>, v=<-1,0,0>, a=<-1,0,0>    -4 -3 -2 -1  0  1  2  3  4
p=<-8,0,0>, v=<-6,0,0>, a=<-2,0,0>                         (0)
At this point, particle 1 will never be closer to <0,0,0> than particle 0, and so, in the long run, particle 0 will stay closest.

Which particle will stay closest to position <0,0,0> in the long term?

Your puzzle answer was 243.

--- Part Two ---
To simplify the problem further, the GPU would like to remove any particles that collide. Particles collide if their positions ever exactly match. Because particles are updated simultaneously, more than two particles can collide at the same time and place. Once particles collide, they are removed and cannot collide with anything else after that tick.

For example:

p=<-6,0,0>, v=< 3,0,0>, a=< 0,0,0>
p=<-4,0,0>, v=< 2,0,0>, a=< 0,0,0>    -6 -5 -4 -3 -2 -1  0  1  2  3
p=<-2,0,0>, v=< 1,0,0>, a=< 0,0,0>    (0)   (1)   (2)            (3)
p=< 3,0,0>, v=<-1,0,0>, a=< 0,0,0>

p=<-3,0,0>, v=< 3,0,0>, a=< 0,0,0>
p=<-2,0,0>, v=< 2,0,0>, a=< 0,0,0>    -6 -5 -4 -3 -2 -1  0  1  2  3
p=<-1,0,0>, v=< 1,0,0>, a=< 0,0,0>             (0)(1)(2)      (3)
p=< 2,0,0>, v=<-1,0,0>, a=< 0,0,0>

p=< 0,0,0>, v=< 3,0,0>, a=< 0,0,0>
p=< 0,0,0>, v=< 2,0,0>, a=< 0,0,0>    -6 -5 -4 -3 -2 -1  0  1  2  3
p=< 0,0,0>, v=< 1,0,0>, a=< 0,0,0>                       X (3)
p=< 1,0,0>, v=<-1,0,0>, a=< 0,0,0>

------destroyed by collision------
------destroyed by collision------    -6 -5 -4 -3 -2 -1  0  1  2  3
------destroyed by collision------                      (3)
p=< 0,0,0>, v=<-1,0,0>, a=< 0,0,0>
In this example, particles 0, 1, and 2 are simultaneously destroyed at the time and place marked X. On the next tick, particle 3 passes through unharmed.

How many particles are left after all collisions are resolved?

Your puzzle answer was 648.

Both parts of this puzzle are complete! They provide two gold stars: **
*/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "CommonFunctions.h"

using namespace std;


struct Particle {
	vector<int64_t> p, v, a;

	Particle(string &line) {
		vector<int> tokens;
		Tokenize(line, tokens, "pva =<,>");
		p = { tokens[0], tokens[1], tokens[2] };
		v = { tokens[3], tokens[4], tokens[5] };
		a = { tokens[6], tokens[7], tokens[8] };
	}

	void Move(map<vector<int64_t>, vector<int64_t>> &c, int &index, bool &foundCollision) {
		//See if this particle is getting closer to the center or not
		int64_t tempDistance = GetDistance();
		
		p[0] += v[0];
		p[1] += v[1];
		p[2] += v[2];

		//Put this location into the map, and the particle into the collision vector
		if (c.find(p) != c.end()) {
			c[p].push_back(index);
			foundCollision = true;
		}
		else {
			vector<int64_t> temp(1, index);
			c[p] = temp;
		}
	}
	
	void Accel() {
		v[0] += a[0];
		v[1] += a[1];
		v[2] += a[2];
	}

	int64_t GetDistance() {
		return abs(p[0]) + abs(p[1]) + abs(p[2]);
	}
};
void Challenge20() {
	ifstream input;
	input.open("Input/Challenge20/Input.txt");
	string line;

	vector<Particle> v;
	while (getline(input, line)) {
		v.push_back(line);
	}

	//Only go through the valid indexes, ignoring ones that have collided
	vector<int> ind;
	for (int m = 0; m < v.size(); m++) {
		ind.push_back(m);
	}

	bool changing = true;
	int count = 0;
	for (int m = 0; m < 400; m++) {
		//Logging
		if (count % 10 == 0)
			cout << count << endl;
		count++;

		//Move each particle and populate the collision map
		map<vector<int64_t>, vector<int64_t>> collisions;
		bool foundCollision = false;
		for (int n = 0; n < ind.size(); n++) {
			v[ind[n]].Accel();
			v[ind[n]].Move(collisions, ind[n], foundCollision);
		}

		if (foundCollision) {
			//Populate the vector 'removing' with any map[index] that has more than 1 particle
			vector<int> removing;
			for (map<vector<int64_t>, vector<int64_t>>::iterator it = collisions.begin(); it != collisions.end(); it++) {
				vector<int64_t> temp = it->second;
				if (temp.size() > 1) {
					for (int i = 0; i < temp.size(); i++)
						removing.push_back(temp[i]);
				}
			}
			//Sort it first so we can start at the back and avoid awkward vector resizing issues
			sort(removing.begin(), removing.end());
			for (int i = removing.size() - 1; i >= 0; i--) {
				for (int q = 0; q < ind.size(); q++) {
					if (ind[q] == removing[i]) {
						ind.erase(ind.begin() + q);
					}
				}
			}
			cout << "Collision! Removing " << removing.size() << " Particles... " << ind.size() << " left." << endl;

		}
	}

	//Find the particle that will be closest to (0, 0, 0) in the longer term
	int64_t lowestDistance = INT64_MAX;
	int64_t lowestParticle = 0;
	for (int m = 0; m < ind.size(); m++) {
		if (v[ind[m]].GetDistance() < lowestDistance) {
			lowestDistance = v[ind[m]].GetDistance();
			lowestParticle = ind[m];
		}
	}
	cout << "Part 1 : " << lowestParticle << endl;
}
