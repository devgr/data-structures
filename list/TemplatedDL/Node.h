/** Node.h
George Darling 9/5/2013

Header file for the Node type. Each node points to a next node and a previous
node, forming a doubly linked list. There is a spot to hold data; this can
either be modified to fit the needs of the program, or point to some other
data containing type.
*/
#pragma once
#include "Data.h"
#include "Data2.h"
using namespace std;

template <typename Tdata>
class Node{
	Tdata * data;
	Node * next; // these are private, Node and List are friends so
	Node * prev; // they can access and change.

	public:
		Node(Tdata*, Node*, Node*); // data, prev, next
		~Node(); // destruct the node

		Tdata * getData();

		template <typename Tdata> friend class TList;
		// craziness!
};

template <typename Tdata>
Node<Tdata>::Node(Tdata* item, Node * before, Node * after){
	next = after;
	prev = before;
	data = item;
}

template <typename Tdata>
Node<Tdata>::~Node(){
	delete data; // simple destruct
	// don't delete next, otherwise the whole list will destruct!
}

template <typename Tdata>
Tdata* Node<Tdata>::getData(){ // proper incapsulation, but really not needed because
						// of friends. could do the same for next and prev
	return data;
}