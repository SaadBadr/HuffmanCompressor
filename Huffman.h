
/*

******Instructions:

in both, encoding and decoding you should call makeHuffmanHeap which takes as parameters:

1- heap : vector < Node* > | its a vector of Nodes, as each node contains a character, frequency, left and right children pointers
	(check in Utility.h, class: Node and function: stringFreqCalculator)

this function will return the root of the huffman heap as Node, so you can traverse it either for encoding and decoding.

***Encoding:

A- To get huffman codes call getHuffmanCodes which takes:

	1- root : Node* | the root of the huffman's heap.
	2- dictionary : unordered_map <unsigned char, string> | empty map to save the codes in it.
	'there is a third parameter but DON'T USE IT AS IT USED IN RECURSION PROCESS ONLY'

B- Now you have the codes you can delete huffman heap to avoid memory leak, simply call deleteHuffmanHeap and pass the root for it.

C- Call huffmanEncode and pass those parameters:
	1-dictionary: unordered_map <unsigned char, string> | the dictionary we got from getHuffmanCodes
	2-encoded: string | this is the orignal text you want to encode, and it will contain the encoded data

	after the function excutes, 'encoded' string now will contatin the encoded data.


***Decoding

A- Call huffmanDecode and pass those parameters:
	1- root: Node* | the root of the huffman heap
	2- BitsString: string | this is a string of 1's and 0's (ex: "10010111") which results from encoding process. 
		(check Utility.h to convert string of bits "1001011110010111" to string of chars "ab" and vice versa)
	3- decoded: string | empty string which will contain the decoded data

B- After decoding, remember to call deleteHuffmanHeap and pass for it the root as a parameter, to delete huffman heap and avoid memory leak.

*/

#pragma once
#include <unordered_map>
#include "Utility.h"
#include <algorithm>

void getHuffmanCodes(Node *root, unordered_map<unsigned char, string> &dictionary, string code = "")
{

	if (root->character != '\0')
		dictionary[root->character] = code;

	if (root->left)
		getHuffmanCodes(root->left, dictionary, code + '0');

	if (root->right)
		getHuffmanCodes(root->right, dictionary, code + '1');

	return;
}

Node *makeHuffmanHeap(vector<Node *> &heap)
{

	make_heap(heap.begin(), heap.end(), greaters());

	while (heap.size() > 1)
	{

		Node *l = heap.front();
		pop_heap(heap.begin(), heap.end(), greaters());
		heap.pop_back();

		Node *r = heap.front();
		pop_heap(heap.begin(), heap.end(), greaters());
		heap.pop_back();

		heap.push_back(new Node(l->frequency + r->frequency, '\0', l, r));
		push_heap(heap.begin(), heap.end(), greaters());
	}

	return heap.front();
}

void huffmanEncode(unordered_map<unsigned char, string> &dictionary, string &encoded)
{

	string::iterator itr = encoded.begin();
	string tmp = "";

	while (itr != encoded.end())
	{
		tmp += dictionary[*itr];
		itr++;
	}

	int addedBits = tmp.size() % 8;

	if (addedBits != 0)
	{
		addedBits = 8 - addedBits;

		for (int i = 0; i < addedBits; i++)
		{
			tmp += '0';
		}
	}

	string added = "00000000";

	int j = 0;
	for (int i = 1; i < 256; i *= 2)
	{
		if (addedBits & i)
			added[j] = '1';
		j++;
	}

	tmp += added;
	bitsToString(tmp, encoded);
}

void huffmanDecode(Node *root, string &encoded, string &decoded)
{
	Node *tmp = root;
	string::iterator itr = encoded.begin();
	decoded = "";
	unsigned long addedBits = encoded.size() - 8;
	unsigned char x = ((unsigned char)*(itr + addedBits) == '1') + (((unsigned char)*(itr + addedBits + 1) == '1') << 1) + (((unsigned char)*(itr + addedBits + 2) == '1') << 2) + (((unsigned char)*(itr + addedBits + 3) == '1') << 3) + (((unsigned char)*(itr + addedBits + 4) == '1') << 4) + (((unsigned char)*(itr + addedBits + 5) == '1') << 5) + (((unsigned char)*(itr + addedBits + 6) == '1') << 6) + (((unsigned char)*(itr + addedBits + 7) == '1') << 7);

	addedBits = x + 8;

	while (itr != encoded.end() - addedBits)
	{
		tmp = root;
		while (tmp->character == '\0')
		{
			if (*itr == '0')
				tmp = tmp->left;
			else
				tmp = tmp->right;
			itr++;
		}
		decoded += tmp->character;
	}
}

void deleteHuffmanHeap(Node *root)
{

	if (root->left)
		deleteHuffmanHeap(root->left);

	if (root->right)
		deleteHuffmanHeap(root->right);

	if (root)
		delete root;
}
