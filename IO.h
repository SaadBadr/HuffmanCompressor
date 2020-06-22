#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;


///////////////////////////////////  STRING IO ///////////////////////////////////

void writeStringA (ofstream& out, const string& content) {

	unsigned size = content.size();
	out.write(reinterpret_cast<char*>(&size), sizeof(unsigned));
	out.write(content.c_str(), size * sizeof(unsigned char));

	return;
}

void writeStringB(string filename, const string& content) {

	ofstream out(filename, ios_base::binary);
	unsigned size = content.size();
	out.write(content.c_str(), size * sizeof(unsigned char));
	out.close();
	return;
}



string readString(string filename) {
	ifstream in(filename, ios::binary);
	string text((istreambuf_iterator<char>(in)),
		(istreambuf_iterator<char>()));
	return text;
}

///////////////////////////////////  VECTOR IO ///////////////////////////////////

template <typename T>
void writeVector(ofstream& out, vector<T>& v) {
	unsigned int size = v.size();
	out.write(reinterpret_cast<char*>(&size), sizeof(unsigned));
	out.write(reinterpret_cast<char*>(&v[0]), v.size() * sizeof(T));
}





template <typename T>
void readVector(ifstream& file, vector<T>& v) {
	unsigned vsize;
	file.read(reinterpret_cast<char*>(&vsize), sizeof(unsigned));
	v.resize(vsize);
	file.read(reinterpret_cast<char*>(&v[0]), ((unsigned long) vsize) * sizeof(T));
}