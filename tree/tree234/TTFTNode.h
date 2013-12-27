/* George Darling
TTFTNode.h
TwoThreeFourTreeNode class
Last updated 11-30-13
*/
#pragma once
//#include "TTFT.h"
#include "NamedItem.h"
class TTFTNode
{
protected:
	bool visited;
	// all of these do just what you expect.
	NamedItem * values[3];

	TTFTNode * children[4];
	TTFTNode * parent;
	TTFTNode * leftsib;
	TTFTNode * rightsib;

public:
	TTFTNode();
	TTFTNode(NamedItem*, TTFTNode*, TTFTNode*, TTFTNode*, TTFTNode*, TTFTNode*);
	~TTFTNode();

	int nodesize(); // returns how many child pointers are being used

	friend class TTFT; // TTFT will work directly with the values and such
};

