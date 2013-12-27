/* George Darling
TTFT.h
TwoThreeFourTree class

Last updated 11-30-13

*/
#include "TTFT.h"


TTFT::TTFT()
{
	root = new TTFTNode();
}


TTFT::~TTFT()
{
	// traverse the tree carefully blowing it up. might use the dump function.
}


void TTFT::dump(){
	// Do an inorder traversal of the tree.
	//preorder(root); // for debugging
	inorder(root);
}
void TTFT::preorder(TTFTNode * curr){
	for (int val = 0; val < 3 && curr->values[val] != nullptr; val++)
		cout << curr->values[val];
	cout << endl << "-----" << endl;

	for (int child = 0; child < 4 && curr->children[child] != nullptr; child++){
		cout << "Going to child " << child << endl;
		preorder(curr->children[child]);
	}
	cout << "Going up!\n";
	return;
}
void TTFT::inorder(TTFTNode * curr){ // I think this works!! woo!!
	if (curr->children[0] != nullptr){ // if not at a leaf
		inorder(curr->children[0]); // recurse down left
		for (int child = 1; child < 4 && curr->children[child] != nullptr; child++){ // go through each in node, visit one, recurse one
			cout << curr->values[child - 1]; // actually visit
			inorder(curr->children[child]); // recurse down next
		}
	}
	else{ // is a leaf, just print the values 
		for (int val = 0; val < 3 && curr->values[val] != nullptr; val++)
			cout << curr->values[val];
	}
	return;
}

TTFTNode * TTFT::split(TTFTNode * curr){
	TTFTNode * currbackup = curr;
	// the middle value needs to be promoted up
	// the left and right values make the left and right children of middle
	// if there is no node above, create a new root
	// if no room in the parent, recursively call split upwards. I don't think you actually need to do this..
	// the middle needs to go in the appropriate slot in the parent

	if (curr->parent == nullptr){ // we are the root, actually keep curr as the root, build two nodes below it
			// that's to prevent from needing to delete a node, which would delete an item as well.
		TTFTNode* left = new TTFTNode(curr->values[0],curr->children[0],curr->children[1],curr,nullptr,nullptr); // superconstructor!
		TTFTNode* right = new TTFTNode(curr->values[2], curr->children[2], curr->children[3], curr, left, nullptr);
		left->rightsib = right; // it's like a 2D linked list!
		curr->children[0] = left;
		curr->children[1] = right;
		curr->children[2] = nullptr; curr->children[3] = nullptr;
		curr->values[0] = curr->values[1]; // shift good value into the left slot
		curr->values[1] = nullptr; curr->values[2] = nullptr;
		curr->rightsib = nullptr; curr->leftsib = nullptr;
		return curr;
		// I think that is everything!
	}
	else{
		TTFTNode* left = new TTFTNode(curr->values[0], curr->children[0], curr->children[1], curr->parent, curr->leftsib, curr);
		// need one additional node, the left one will be new, the old one will become right, but return parent
		// several cases for moving middle up
		if (curr->parent->nodesize() == 3){
			if (curr->values[1]->get_name() > curr->parent->values[1]->get_name()){
				curr->parent->values[2] = curr->values[1]; // move middle up to right slot
				curr->parent->children[2] = left; // link stuff in
				curr->parent->children[3] = curr;
			}
			else if (curr->values[1]->get_name() > curr->parent->values[0]->get_name()){
				curr->parent->values[2] = curr->parent->values[1]; // slide one over
				curr->parent->values[1] = curr->values[1]; // move middle up
				curr->parent->children[3] = curr->parent->children[2]; // slide child over
				curr->parent->children[2] = curr;
				curr->parent->children[1] = left;
			}
			else{
				curr->parent->values[2] = curr->parent->values[1]; // slide values
				curr->parent->values[1] = curr->parent->values[0];
				curr->parent->values[0] = curr->values[1];
				curr->parent->children[3] = curr->parent->children[2]; // slide children
				curr->parent->children[2] = curr->parent->children[1];
				curr->parent->children[1] = curr;
				curr->parent->children[0] = left; // yay!
			}
		}
		else if (curr->parent->nodesize() == 2){
			if (curr->values[1]->get_name() > curr->parent->values[0]->get_name()){ // add right
				curr->parent->values[1] = curr->values[1]; // push up
				curr->parent->children[2] = curr;
				curr->parent->children[1] = left;
			}
			else{ // add left
				curr->parent->values[1] = curr->parent->values[0];
				curr->parent->values[0] = curr->values[1];
				curr->parent->children[2] = curr->parent->children[1];
				curr->parent->children[1] = curr;
				curr->parent->children[0] = left;
			}
		}
		else std::cout << "We got problems I think.\n"; 
		curr->values[0] = curr->values[2];
		curr->values[1] = nullptr;
		curr->values[2] = nullptr; // This is very important. I'm not sure if this works in all cases though <<<<
		return curr->parent;
	}
	// ??????
}
// Inserts at a leaf
void TTFT::doinsert(TTFTNode * curr, NamedItem * tempitem){
	if (curr->nodesize() == 0){
		if (curr->values[0] == nullptr) // empty tree
			curr->values[0] = tempitem;
		else if (curr->values[1] == nullptr){ // one value in tree
			if (tempitem->get_name() > curr->values[0]->get_name())
				curr->values[1] = tempitem;
			else{
				curr->values[1] = curr->values[0];
				curr->values[0] = tempitem;
			}
		}
		else if (curr->values[2] == nullptr){
			if (tempitem->get_name() > curr->values[1]->get_name())
				curr->values[2] = tempitem;
			else if (tempitem->get_name() > curr->values[0]->get_name()){
				curr->values[2] = curr->values[1];
				curr->values[1] = tempitem;
			}
			else{
				curr->values[2] = curr->values[1];
				curr->values[1] = curr->values[0];
				curr->values[0] = tempitem;
			}
		}
		else{
			curr = split(curr); // check to see if this works in all conditions....
			if (tempitem->get_name() < curr->values[0]->get_name()){
				TTFTNode * left = curr->children[0];
				if (tempitem->get_name() > left->values[0]->get_name())
					left->values[1] = tempitem;
				else{
					left->values[1] = left->values[0];
					left->values[0] = tempitem;
				}
			}
			else{
				TTFTNode * right = curr->children[0];
				if (tempitem->get_name() > right->values[0]->get_name())
					right->values[1] = tempitem;
				else{
					right->values[1] = right->values[0];
					right->values[0] = tempitem;
				}
			}
		}
	}
}

void TTFT::Add(NamedItem * tempitem){
	bool done = false;
	TTFTNode * curr = root;
	
	while (!done){
		int nsize = curr->nodesize();
		if (nsize == 0){ // that means it is a leaf
			doinsert(curr, tempitem);
			done = true;
		}
		else if (nsize == 4){ // need to split
			curr = split(curr); // after spliting, curr is its previous parent
		}
		else if (nsize == 2){ // go right or left
			if (tempitem->get_name() > curr->values[0]->get_name())
				curr = curr->children[1];
			else
				curr = curr->children[0];
		}
		else if (nsize == 3){ // go right middle or left
			if (tempitem->get_name() > curr->values[1]->get_name())
				curr = curr->children[2];
			else if (tempitem->get_name() > curr->values[0]->get_name())
				curr = curr->children[1];
			else
				curr = curr->children[0];
		}
		else std::cout << "Oh noes!!\n";
	}
}

void TTFT::Remove(string name){
	// This function doesn't really work. I'm just out of time.
	// It might remove items from leaves in certain conditions. See the outline
	// in the commented out code for where its going.

	if (root->values[0] == nullptr){
		std::cout << "Empty tree, nothing to delete\n";
		return;
	}
	TTFTNode * rmnode = rmsearch(name, root);
	NamedItem * successor = nullptr;
	// find the item to delete by finding its node first
	if (rmnode != nullptr){
		// get the actual item out of that node that is the one to be removed
		int val;
		for (val = 0; val < 3 && rmnode->values[val] != nullptr; val++)
			if (rmnode->values[val]->get_name() == name)
				break;
		if (rmnode->values[val] == nullptr) std::cout << "STAAAHP!\n";
		// Start working towards finding rm's inorder successor to swap with it
		// Do a bunch of things along the way.
		// Do these things need to be done the whole way down starting from the root? I think so <<<<<<<<<<
		TTFTNode * curr = root; // start here
		
		/* XXXXXXXXXXXXXXXXXXXXXXX
		TTFTNode * betterrmnode = nullptr;
		bool founditem = false;
		int foundindex = 0;
		// some more stuff

		loop:
		while (curr->nodesize() != 0){ // not a leaf - start going down the tree!
			// if adjacent sibling has more than one key, take from parent, sibling key goes to parent
			// if no adjacent sibling has more than one, steal from parent
			// if parent is the root and has only one key, sib has one key
			// then fuse those into one node (the root) and the tree shrinks
			if (curr->nodesize() == 2){ // single value, need to grab more.
				if (curr->leftsib != nullptr && curr->leftsib->nodesize() > 2){ // steal from left

				}
				else if (curr->rightsib != nullptr && curr->rightsib->nodesize() > 2){ // steal from right.

				}
				else if (curr->parent->nodesize() > 2){ // steal from parent

				}
				else if (curr->parent == root){ // shorten tree
					TTFTNode * templ = root->children[0];
					TTFTNode * tempr = root->children[1];
					root->values[1] = root->values[0];
					root->values[0] = templ->values[0]; // copy values up into the root
					root->values[2] = tempr->values[0];
					root->children[0] = templ->children[0]; // copy children
					root->children[1] = templ->children[1];
					root->children[2] = tempr->children[0];
					root->children[3] = tempr->children[1];
					root->children[0]->parent = root; // set parents
					root->children[1]->parent = root;
					root->children[2]->parent = root;
					root->children[3]->parent = root;
					delete templ; // clean up
					delete tempr;
					curr = root;
					continue;
				}
			}
			// Advance down the tree
			if (!founditem){ // normal search for item, not successor
				// check if item is in this node
				for (int val = 0; val < 3 && curr->values[val] != nullptr; val++){
					if (curr->values[val]->get_name() == name){
						founditem = true;
						foundindex = val;
						betterrmnode = curr;
						if (curr->children[val + 1] != nullptr) // just checking...
							curr = curr->children[val + 1]; // after this go left
						goto loop; // YES, I JUST USED GOTO.
					}
				}
				int v;
				for (v = 0; v < 3 && curr->values[v] != nullptr; v++){
					if (curr->values[v]->get_name() > name){
						if (curr->children[v] != nullptr){
							curr = curr->children[v]; // recurse left
							goto loop;
						}
						else std::cout << "???\n";
					}
				}
				if (curr->values[v]->get_name() < name){ // recurse right
					if (curr->children[v] != nullptr){
						curr = curr->children[v];
						goto loop;
					}
					else std::cout << "???\n";
				}
			}
			else{ // searching for successor
				curr = curr->children[0]; // Oh man. hope this is ok.
			}
		}
		if (betterrmnode == nullptr){
			std::cout << "Guess it wasn't found for deleting\n";
			return;
		}
		//XXXXXXXXXXXXXXXXXXXXXXXX */
		curr = rmnode; // old remove me <<<<<
		if (curr->nodesize() == 0){ // is a leaf!
			// swap with inorder successor
			successor = curr->values[0]; // note that if you are starting from a leaf, this is not actually the successor
			curr->values[0] = rmnode->values[val];
			rmnode->values[val] = successor;
			//curr->values[0] = betterrmnode->values[val];
			//betterrmnode->values[val] = successor;

			if (curr->values[1] == nullptr){ // only one value. stuff gets complicated.

			}
			else{ // Easy! just remember to sort the node after removing.
				delete curr->values[0];
				curr->values[0] = nullptr;
				if (curr->values[2] != nullptr){ // two values left in the node
					if (curr->values[2] < curr->values[1]){
						curr->values[0] = curr->values[2];
						curr->values[2] = nullptr;
					}
					else{
						curr->values[0] = curr->values[1];
						curr->values[1] = curr->values[2];
						curr->values[2] = nullptr;
					}
				}
				else{ // just slide one left
					curr->values[0] = curr->values[1];
					curr->values[1] = nullptr;
				}
			}
		}

	}
	else std::cout << "No node found to delete.\n";
}


// --------------------------------------------------------------------------------------
// Searching tree stuff
NamedItem * TTFT::Find(string name){
	return search(name, root);
}

NamedItem * TTFT::search(string name, TTFTNode * curr){
	// OK. So the logic in this function could be much shorter. I know...
	// look through the node for a match first
	for (int val = 0; val < 3 && curr->values[val] != nullptr; val++){
		if (curr->values[val]->get_name() == name)
			return curr->values[val];
	}
	int v;
	for (v = 0; v < 3 && curr->values[v] != nullptr; v++){
		if (curr->values[v]->get_name() > name){
			if (curr->children[v] != nullptr)
				return search(name, curr->children[v]); // recurse left
			else return nullptr; // no children, not found
		}
	}
	if (curr->values[v]->get_name() < name){ // recurse right
		if (curr->children[v] != nullptr)
			return search(name, curr->children[v]);
		else return nullptr; // not found
	}
	return nullptr; // just in case
}
TTFTNode * TTFT::rmsearch(string name, TTFTNode * curr){
	// This is just the same as the other search, but it returns a node instead of just a value
	for (int val = 0; val < 3 && curr->values[val] != nullptr; val++){
		if (curr->values[val]->get_name() == name)
			return curr;
	}
	int v;
	for (v = 0; v < 3 && curr->values[v] != nullptr; v++){
		if (curr->values[v]->get_name() > name){
			if (curr->children[v] != nullptr)
				return rmsearch(name, curr->children[v]); // recurse left
			else return nullptr; // no children, not found
		}
	}
	if (curr->values[v]->get_name() < name){ // recurse right
		if (curr->children[v] != nullptr)
			return rmsearch(name, curr->children[v]);
		else return nullptr; // not found
	}
	return nullptr; // just in case
}