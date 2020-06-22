#pragma once
#include <algorithm>
#include <map>
#include "Utility.h"
#include <queue>

void getHuffmanCodes(Node* root, map <unsigned char, string> &dictionary, string code="") {
	

	if (root->character != '\0')
		dictionary[root->character] = code;

	if (root->left)
		getHuffmanCodes(root->left, dictionary, code + '0');

	if (root->right)
		getHuffmanCodes(root->right, dictionary, code + '1');

	return;
}





Node* makeHuffmanHeap(vector < Node* > &v) {

	priority_queue <Node*, vector<Node*>, greaters> heap;

	for (size_t i = 0; i < v.size(); i++)
	{
		heap.push(v[i]);
	}

	while (heap.size() > 1) {

		Node* l = heap.top();
		heap.pop();

		Node* r = heap.top();
		heap.pop();

		heap.push(new Node(l->frequency + r->frequency, '\0', l, r));	
	}

	return heap.top();
}


void huffmanEncode(map <unsigned char, string>& dictionary, string& encoded) {
	
	string::iterator itr = encoded.begin();
	string tmp = "";
	
	while (itr != encoded.end()) {
		tmp += dictionary[*itr];
		itr++;
	}

	int addedBits = tmp.size() % 8;

	if (addedBits != 0) {
		addedBits = 8 - addedBits;

		for (int i = 0; i < addedBits; i++)
		{
			tmp += '0';
		}
	}

	string added = "00000000";

	int j = 0;
	for (int i = 1; i < 256; i*=2)
	{
		if(addedBits & i)
			added[j] = '1';
		j++;
	}

	tmp += added;
	bitsToString(tmp, encoded);
}

void deleteHuffmanHeap(Node* root) {

	if (root->left)
		deleteHuffmanHeap(root->left);

	if (root->right)
		deleteHuffmanHeap(root->right);

	delete root;
}

void huffmanDecode(Node* root, string& encoded, string& decoded) {
	Node* tmp = root;
	string::iterator itr = encoded.begin();
	decoded = "";
	unsigned long addedBits = encoded.size() - 8;
	unsigned char x = ((unsigned char) * (itr + addedBits) == '1')
		+ ((unsigned char) * (itr + addedBits +1) == '1') * 2
		+ ((unsigned char) * (itr + addedBits +2) == '1') * 4
		+ ((unsigned char) * (itr + addedBits +3) == '1') * 8
		+ ((unsigned char) * (itr + addedBits +4) == '1') * 16
		+ ((unsigned char) * (itr + addedBits +5) == '1') * 32
		+ ((unsigned char) * (itr + addedBits +6) == '1') * 64
		+ ((unsigned char) * (itr + addedBits +7) == '1') * 128;

	addedBits = x + 8;

	while (itr != encoded.end() - addedBits)
	{
		tmp = root;
		while (tmp->character == '\0') {
			if (*itr == '0')
				tmp = tmp->left;
			else
				tmp = tmp->right;
			itr++;
		}
		decoded += tmp->character;
	}

}

