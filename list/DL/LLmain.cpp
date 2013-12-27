/**
George Darling 9/5/2013

A main function demonstrating the use of a simple linked list in C++
*/
//#include <iostream>
#include "List.h"

using namespace std;

int main(){
	List * exampleList = new List();

	cout << "Adding 9 nodes\n";
	for(int i = 1; i < 10; i++){
		exampleList->addEnd(new Data(i));
	}
	exampleList->printList();

	cout << "Searching for the number 5\n";
	cout << exampleList->findData(5)->getNumber() << endl;
	cout << "Searching for the number 13\n";
	cout << exampleList->findData(13)->getNumber() << endl;

	cout << "Deleting node for 4\n";
	exampleList->removeNode(4);
	exampleList->printList();
	cout << "Deleting node for 1\n";
	exampleList->removeNode(1);
	exampleList->printList();

	delete exampleList;
	return 0;
}