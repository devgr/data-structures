/* George Darling
TwoThreeFourTreeNode class

*/
#include "TTFTNode.h"


TTFTNode::TTFTNode()
{
	visited = false;
	for (int i = 0; i < 4; i++)
		children[i] = nullptr;
	for (int i = 0; i < 3; i++)
		values[i] = nullptr;
	parent = nullptr;
	leftsib = nullptr;
	rightsib = nullptr;
}
TTFTNode::TTFTNode(NamedItem*item, TTFTNode*childL, TTFTNode*childR, TTFTNode*par, TTFTNode*sibL, TTFTNode*sibR){
	values[0] = item;
	values[1] = nullptr; values[2] = nullptr;
	children[0] = childL; children[1] = childR;
	children[2] = nullptr; children[3] = nullptr;
	parent = par;
	leftsib = sibL;
	rightsib = sibR;
	visited = false;
}

TTFTNode::~TTFTNode()
{
	for (int i = 0; i < 4; i++)
		delete children[i];
}

int TTFTNode::nodesize(){
	for (int i = 0; i < 4; i++){
		if (children[i] == nullptr)
			return i;
	}
	return 4;
}
