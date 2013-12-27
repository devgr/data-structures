/** List.h
George Darling 9/5/2013

Header file for the List type. This provides a pointer to the head node of
of a circular doubly linked list consisting of Nodes, and the methods with which to
build the linked list.
*/
#include "Node.h"
#include <iostream>
using namespace std;

class List{
	private:
		Node * head;
	public:
		List();
		~List();

		void printList();
		//void insertNode(int, Data*); // location, data for the node
		void addEnd(Data*); // add at the end of the list with data
		int removeNode(int); // find based on data then remove
		Data * findData(int); // based on the number given to a data in
							// a node, return a pointer to the data object
};