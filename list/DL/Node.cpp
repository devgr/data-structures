/** Node.cpp
George Darling 9/5/2013

Implementation of the Node type. See Node.h for documentation.
*/
#include "Node.h"
using namespace std;

Node::Node(Data* item, Node * before, Node * after){
	next = after;
	prev = before;
	data = item;
}
Node::~Node(){
	delete data; // simple destruct
	// don't delete next, otherwise the whole list will destruct!
}

Data* Node::getData(){ // proper incapsulation, but really not needed because
						// of friends. could do the same for next and prev
	return data;
}