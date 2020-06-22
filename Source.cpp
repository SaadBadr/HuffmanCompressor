#include <iostream>
#include "Huffman.h"
#include "IO.h"
#define filename "enwik8.t"


void encode() {

	cout << "ENCODING STARTED\n";
	string text = readString(filename);
	map<unsigned char, string> dictionary;
	vector < Node* > heap;
	ofstream out("encoded.bin", ios_base::binary);

	{
		stringFreqCalculator(text, heap);
		int size = heap.size();

		vector <unsigned char> c(size);
		vector <unsigned int> f(size);

		for (int i = 0; i < size; i++)
		{
			c[i] = heap[i]->character;
			f[i] = heap[i]->frequency;
		}

		Node* root = makeHuffmanHeap(heap);
		getHuffmanCodes(root, dictionary);

		deleteHuffmanHeap(root);

		writeVector(out, c);
		writeVector(out, f);
	}

	huffmanEncode(dictionary, text);

	writeStringA(out, text);
	out.close();

}


void readEncodedData(string &text, vector<Node*> &heap) {


	ifstream in("encoded.bin", ios_base::binary);

	vector <unsigned char> c;
	readVector(in, c);

	vector <unsigned int> f;
	readVector(in, f);


	vector<unsigned char> temp;
	readVector(in, temp);
	string t(temp.begin(), temp.end());
	text = t;

	in.close();

	int size = c.size();

	heap.resize(size);

	for (int i = 0; i < size; i++)
	{
		heap[i] = new Node(f[i], c[i]);
	}

}


void decode() {
	cout << "DECODING STARTED\n";
	string text;
	vector <Node*> heap;
	readEncodedData(text, heap);

	Node* root = makeHuffmanHeap(heap);
	
	string BitsString;
	stringToBits(text, BitsString);
	huffmanDecode(root, BitsString, text);
	writeStringB("decoded", text);
}



int main() {
	
	startTime();
	
	encode();
	
	endTime();
	printDuaration("Encoding");
	
	startTime();
	
	decode();
	
	endTime();
	printDuaration("Decoding");
	
	if (IsIdentical(filename, "decoded"))
		cout << "SUCCESS, the two files are identical";
	else
		cout << "FAILURE, the two files are not identical";
	return 0;
}
