#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include "IO.h"

using namespace std;

class Node
{
public:
	unsigned int frequency;
	unsigned char character;
	Node* right;
	Node* left;

	Node(unsigned int f, unsigned char c = '\0', Node* r = NULL, Node* l = NULL) {
		frequency = f;
		character = c;
		right = r;
		left = l;
	}
};


struct greaters {
	bool operator()(const Node* l, const Node* r) const {
		if (l->frequency == r->frequency)
			return l->character > r->character;
		else
			return l->frequency > r->frequency;
	}
};

void stringFreqCalculator(string& text, vector < Node* >& v) {
	
	unordered_map <unsigned char, unsigned int> frequency;

	for (char c : text)
		frequency[c]++;

	v.resize(frequency.size());

	unordered_map <unsigned char, unsigned int>::iterator itr = frequency.begin();
	
	unsigned int i = 0;

	while (itr != frequency.end()) {
		v[i++] = new Node(itr->second, itr->first);
		itr++;
	}
		
}

/// Bits Manipulation Functions

void bitsToString(string& bits, string& str) {

	string::iterator itr = bits.begin();
	str = "";

	while (itr < bits.end() - 1) {
		unsigned char tmp = ((unsigned char) * (itr) == '1')
			+ ((unsigned char) * (itr + 1) == '1') * 2
			+ ((unsigned char) * (itr + 2) == '1') * 4
			+ ((unsigned char) * (itr + 3) == '1') * 8
			+ ((unsigned char) * (itr + 4) == '1') * 16
			+ ((unsigned char) * (itr + 5) == '1') * 32
			+ ((unsigned char) * (itr + 6) == '1') * 64
			+ ((unsigned char) * (itr + 7) == '1') * 128;
		str += tmp;
		itr += 8;
	}
}


void stringToBits(string & str, string & bits) {

	string::iterator itr = str.begin();
	bits = "";

	string tmp;

	while (itr != str.end()) {
		int j = 0;
		tmp = "00000000";
		for (int i = 1; i < 256; i *= 2)
		{
			if (*itr & i)
				tmp[j] = '1';
			j++;
		}
		bits += tmp;
		itr++;
	}

}

/// Time Functions

chrono::steady_clock::time_point timeBegin;
chrono::steady_clock::time_point timeEnd;


void startTime() {
	timeBegin = chrono::steady_clock::now();
}

void endTime() {
	timeEnd = chrono::steady_clock::now();
}

void printDuaration(string operation) {
	cout << operation + " DONE in: " << chrono::duration_cast<chrono::seconds>(timeEnd - timeBegin).count() << "[s]\n";
}



/// Testing Functions

bool IsIdentical(string firstFileName, string secondFileName) {
	return readString(firstFileName).compare(readString(secondFileName)) == 0;
}

int getFileSize(string f) {
	ifstream file(f, ios::binary | ios::ate);
	int in = file.tellg();
	file.close();
	return in;
}

float CompressionRatio(string input, string output) {

	return getFileSize(input) / (float) getFileSize (output);
}
