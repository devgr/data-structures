/** List.h
George Darling 9/5/2013

Header file for the List type. This provides a pointer to the head node of
of a circular doubly linked list consisting of Nodes, and the methods with which to
build the linked list.
*/
#pragma once
#include "Node.h"
#ifndef includeiostream
	#define includeiostream
	#include <iostream>
#endif
using namespace std;

template <typename Tdata>
class TList{
	private:
		Node<Tdata> * head; // going step by step, will need to template
			// the list class as well, then do List<Data> in main
	public:
		TList();
		~TList();

		void printList();
		void addEnd(Tdata*); // add at the end of the list with data
		int removeNode(int); // find based on data then remove
		Tdata * findData(int); // based on the number given to a data in
							// a node, return a pointer to the data object

};

template <typename Tdata>
TList<Tdata>::TList(){
	head = new Node<Tdata>(nullptr, nullptr, nullptr); // head has no data and points to no other nodes yet
	head->next = head; // fancy!
	head->prev = head;
}

template <typename Tdata>
void TList<Tdata>::printList(){
	// Get a Node<Data>to work with, skipping the head, then iterate down the list until back at head
	for(Node<Tdata> * traverse = head->next; traverse != head; traverse = traverse->next)
		cout << traverse->data->getNumber() << " "; // now that's a fancy for loop!

	cout << endl;
}

template <typename Tdata>
void TList<Tdata>::addEnd(Tdata* item){
	Node<Tdata>* newNode = new Node<Tdata>(item, head->prev, head); // prev is the old last node, next is first
	head->prev->next = newNode; // link the old end to new
	head->prev = newNode; // foot pointer goes to the new end
}

template <typename Tdata>
int TList<Tdata>::removeNode(int num){ // finds, then removes
	for(Node<Tdata>* traverse = head->next; traverse != head; traverse = traverse->next){
		if(traverse->data->getNumber() == num){
			traverse->prev->next = traverse->next; // re-link the surrounding nodes
			traverse->next->prev = traverse->prev;
			delete traverse;
			return 1; // success, I assume.
		}
	}
	return -1; // error, didn't find item to delete
}

template <typename Tdata>
Tdata * TList<Tdata>::findData(int num){
	// regular traverse, look at each element and compare to num
	for(Node<Tdata>* traverse = head->next; traverse != head; traverse = traverse->next){
		if(traverse->data->getNumber() == num) return traverse->data;
	}
	return new Tdata(-1); // if it doesn't find the data
}

template <typename Tdata>
TList<Tdata>::~TList(){ // carefully blow up the list
	Node<Tdata>* current = head->next;
	Node<Tdata>* nextone;
	while(current != head){
		nextone = current->next;
		delete current;
		current = nextone;
	}
	delete head; // BYE :'(
}
