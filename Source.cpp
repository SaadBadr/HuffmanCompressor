#include <iostream>
#include "Huffman.h"
#include "IO.h"

#define original_filename "enwik8"
#define decoded_filename "decoded"
#define encoded_filename "encoded.bin"

void encode()
{

	startTime();

	cout << "ENCODING STARTED\n";
	string text = "";
	readString(original_filename, text);
	unordered_map<unsigned char, string> dictionary;
	vector<Node *> heap;
	ofstream out("encoded.bin", ios_base::binary);

	{
		stringFreqCalculator(text, heap);
		int size = heap.size();

		vector<unsigned char> c(size);
		vector<unsigned int> f(size);

		for (int i = 0; i < size; i++)
		{
			c[i] = heap[i]->character;
			f[i] = heap[i]->frequency;
		}

		Node *root = makeHuffmanHeap(heap);
		getHuffmanCodes(root, dictionary);

		deleteHuffmanHeap(root);

		writeVector(out, c);
		writeVector(out, f);
	}

	huffmanEncode(dictionary, text);

	writeStringA(out, text);
	out.close();

	endTime();
	printDuaration("Encoding");
}

void readEncodedData(string &text, vector<Node *> &heap)
{

	ifstream in(encoded_filename, ios_base::binary);

	vector<unsigned char> c;
	readVector(in, c);

	vector<unsigned int> f;
	readVector(in, f);

	vector<unsigned char> temp;
	readVector(in, temp);
	text.assign(temp.begin(), temp.end());

	in.close();

	int size = c.size();

	heap.resize(size);

	for (int i = 0; i < size; i++)
	{
		heap[i] = new Node(f[i], c[i]);
	}
}

void decode()
{

	startTime();

	cout << "DECODING STARTED\n";
	string text;
	vector<Node *> heap;
	readEncodedData(text, heap);

	Node *root = makeHuffmanHeap(heap);

	string BitsString;
	stringToBits(text, BitsString);
	huffmanDecode(root, BitsString, text);

	deleteHuffmanHeap(root);

	writeStringB(decoded_filename, text);

	endTime();
	printDuaration("Decoding");
}

int main()
{

	cout << "****INSTRUCTIONS:" << endl;
	cout << "-Encoding: please make sure that the file " << original_filename << " is placed in the same directory with the program." << endl;
	cout << "-Decoding: please make sure that the file " << encoded_filename << " is placed in the same directory with the program." << endl;

	cout << endl
		 << endl;

	char y = 'y';
	signed short option;

	while (y == 'y')
	{
		cout << "Please choose required operation:" << endl;
		cout << " 1. Encode " << original_filename << endl;
		cout << " 2. Decode " << encoded_filename << endl;
		cout << " 3. Encode " << original_filename << " then Decode " << encoded_filename << endl;

		cin >> option;

		if (option != 2)
			encode();

		if (option != 1)
			decode();

		if (option != 2)
			cout << "Compression Ratio: " << CompressionRatio(original_filename, encoded_filename) << endl;

		if (option != 1)
		{

			cout << "Do you want to run a test checking that the decoded file and the original file are the same? (y/n)" << endl;

			cin >> y;

			if (y == 'y')

				if (IsIdentical(original_filename, decoded_filename))
					cout << "SUCCESS, the two files are identical." << endl;
				else
					cout << "FAILURE, the two files are not identical." << endl;
		}

		cout << endl
			 << "Do you want to run the program again? (y/n)" << endl;
		cin >> y;
	}

	return 0;
}
