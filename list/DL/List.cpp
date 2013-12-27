/** List.cpp
George Darling 9/5/2013

Implementation of the List type. See List.h for documentation.
*/
#include "List.h"

using namespace std;

List::List(){
	head = new Node(nullptr, nullptr, nullptr); // head has no data and points to no other nodes yet
	head->next = head; // fancy!
	head->prev = head;
}
void List::printList(){
	// Get a node to work with, skipping the head, then iterate down the list until back at head
	for(Node * traverse = head->next; traverse != head; traverse = traverse->next)
		cout << traverse->data->getNumber() << " "; // now that's a fancy for loop!

	cout << endl;
}
// void List::insertNode(int location, Data* item){}

void List::addEnd(Data* item){
	Node * newNode = new Node(item, head->prev, head); // prev is the old last node, next is first
	head->prev->next = newNode; // link the old end to new
	head->prev = newNode; // foot pointer goes to the new end
}
int List::removeNode(int num){ // finds, then removes
	for(Node * traverse = head->next; traverse != head; traverse = traverse->next){
		if(traverse->data->getNumber() == num){
			traverse->prev->next = traverse->next; // re-link the surrounding nodes
			traverse->next->prev = traverse->prev;
			delete traverse;
			return 1; // success, I assume.
		}
	}
	return -1; // error, didn't find item to delete
}

Data* List::findData(int num){
	// regular traverse, look at each element and compare to num
	for(Node * traverse = head->next; traverse != head; traverse = traverse->next){
		if(traverse->data->getNumber() == num) return traverse->data;
	}
	return new Data(-1); // if it doesn't find the data
}


List::~List(){ // carefully blow up the list
	Node * current = head->next;
	Node * nextone;
	while(current != head){
		nextone = current->next;
		delete current;
		current = nextone;
	}
	delete head; // BYE :'(
}