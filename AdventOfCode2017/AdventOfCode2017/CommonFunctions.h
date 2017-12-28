#pragma once
#ifndef __COMMONFUNCTIONS__
#define __COMMONFUNCTIONS__

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <map>

using namespace std;

//So we can easily see what direction it's currently moving
enum { south, west, north, east };

template <typename T>
void PrintVector(vector<T> v, bool space = false) {
	cout << "Printing Contents of Vector : " << endl;
	for (int m = 0; m < v.size(); m++) {
		cout << v[m];
		if (space)
			cout << " ";
		else
			cout << endl;
	}
	if(space)
		cout << endl;
	cout << "Done Printing Vector" << endl;
}

template <typename T>
void Print2DVector(vector<vector<T>> v, bool space = true) {
	cout << "Printing Contents of 2D Vector : " << endl;
	for (int m = 0; m < v.size(); m++) {
		for (int n = 0; n < v[m].size(); n++) {
			cout << v[m][n];
			if (space)
				cout << " ";
			else
				cout << endl;
		}
		cout << endl;
	}
	if (space)
		cout << endl;
	cout << "Done Printing Vector" << endl;
}

void Tokenize(const string& str,
	vector<int>& tokens,
	const string& delimiters = " ")
{
	// Skip delimiters at beginning.
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	// Find first "non-delimiter".
	string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos)
	{
		// Found a token, add it to the vector.
		tokens.push_back(stoi(str.substr(lastPos, pos - lastPos)));
		// Skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delimiters, pos);
		// Find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
	}
}

void Tokenize(const string& str,
	vector<string>& tokens,
	const string& delimiters = " ")
{
	// Skip delimiters at beginning.
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	// Find first "non-delimiter".
	string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos)
	{
		// Found a token, add it to the vector.
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		// Skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delimiters, pos);
		// Find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
	}
}

void reverseSelection(vector<int> &v, int length, int l, int r) {
	for (int m = 0; m < length / 2; m++) {
		int temp = v[l];
		v[l] = v[r];
		v[r] = temp;

		l = (l + 1) % v.size();
		if (r == 0)
			r = v.size() - 1;
		else
			r--;
	}
}


//Challenge 10 Originally
string knothash(string s) {
	ifstream input;

	//Lengths indicates the size of the subset that will be reversed
	//Add several specific numbers at the end according to the problem
	vector<int> lengths;
	for (int m = 0; m < s.length(); m++) {
		lengths.push_back((int)s[m]);
	}
	lengths.insert(lengths.end(), { 17, 31, 73, 47, 23 });

	//Start with an array 0-255, this will go through several reversals
	vector<int> v;
	for (int m = 0; m < 256; m++)
		v.push_back(m);

	//Keep track of the current Index and the skip size over the entire operation
	int currIndex = 0;
	int skipSize = 0;
	//Perform the hashing 64 times according to the problem
	for (int x = 0; x < 64; x++) {
		for (int m = 0; m < lengths.size(); m++) {
			reverseSelection(v, lengths[m], currIndex, (currIndex + lengths[m] - 1) % v.size());
			currIndex = (currIndex + lengths[m] + skipSize) % v.size();
			skipSize++;
		}
	}

	string knotHash;
	stringstream ss;
	for (int m = 0; m < 16; m++) {
		int temp = 0;
		int currIndex = m * 16;
		for (int n = 0; n < 16; n++) {
			temp = temp ^ v[currIndex + n];
		}
		//Transform the int to hex, and make sure to keep leading 0's if there are any
		ss << std::hex << setfill('0') << setw(2) << temp;
	}
	ss >> knotHash;
	return knotHash;
}

//Check if an input is a number or a register that contains a number. Return a number either way.
int64_t GetValue(map<string, int64_t> &m, string s) {
	if (s[0] >= 'a' && s[0] <= 'z')
		return m[s];
	return stoi(s);
}

bool isPrime(int num)
{
	if (num <= 1)
		return false;
	else if (num == 2)
		return true;
	else if (num % 2 == 0)
		return false;
	else
	{
		bool prime = true;
		int divisor = 3;
		double num_d = static_cast<double>(num);
		int upperLimit = static_cast<int>(sqrt(num_d) + 1);

		while (divisor <= upperLimit)
		{
			if (num % divisor == 0)
				prime = false;
			divisor += 2;
		}
		return prime;
	}
}


#endif // !__COMMONFUNCTIONS__
