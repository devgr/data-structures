/**
George Darling 9/5/2013

A main function demonstrating the use of a simple linked list in C++
*/
//#include <iostream>
#include "TList.h"

using namespace std;

int main(){
	TList<Data> * exampleList = new TList<Data>();

	cout << "Adding 9 nodes\n";
	for(int i = 1; i < 10; i++){
		exampleList->addEnd(new Data(i));
	}
	exampleList->printList();

	cout << "Searching for the number 5\n";
	cout << exampleList->findData(5)->getNumber() << endl;
	cout << "Searching for the number 13\n";
	cout << exampleList->findData(13)->getNumber() << endl;
	

	TList<Data2> * exampleList2 = new TList<Data2>();
	cout << "Data2\n";
	cout << "Adding 9 nodes\n";
	for(int j = 1; j < 10; j++){
		exampleList2->addEnd(new Data2(j));
	}
	exampleList2->printList();

	cout << "Searching for the number 5\n";
	cout << exampleList2->findData(5)->getNumber() << endl;
	cout << "Searching for the number 13\n";
	cout << exampleList2->findData(13)->getNumber() << endl;

	cout << "Deleting node for 4\n";
	exampleList2->removeNode(4);
	exampleList2->printList();
	cout << "Deleting node for 1\n";
	exampleList2->removeNode(1);
	exampleList2->printList();

	delete exampleList2;


	cout << "Deleting node for 4\n";
	exampleList->removeNode(4);
	exampleList->printList();
	cout << "Deleting node for 1\n";
	exampleList->removeNode(1);
	exampleList->printList();

	delete exampleList;
	return 0;
}