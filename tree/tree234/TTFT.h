/* George Darling
TTFT.h
TwoThreeFourTree class

Last updated 11-30-13

*/
#pragma once
#include <iostream>

#include "TTFTNode.h"
#include "NamedItem.h"
class TTFT{
private:
	TTFTNode * root;

	// A whole bunch of helper functions
	TTFTNode * split(TTFTNode *);
	void doinsert(TTFTNode *, NamedItem *);
	NamedItem * TTFT::search(string, TTFTNode *);
	void inorder(TTFTNode *);
	void preorder(TTFTNode *);
	TTFTNode * rmsearch(string, TTFTNode *);

public:
	TTFT();
	~TTFT();
	void dump();
	void Add(NamedItem *);
	void Remove(string);
	NamedItem * Find(string);

};

