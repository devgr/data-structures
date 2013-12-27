/** HashItem.h
George Darling 10/19/2013

HashItem is a base class that is meant to be derived. It provides a name
field for any type derived from it, to be used in a function.
This class is NOT abstract. That sort of makes sense - you could want
to just hash a key, and be able to find out if the key is in the set,
without wanting a value associated with the key.

HashItem > Person > Student, Faculty, Administrator
*/
#pragma once
#include <string>
using namespace std;
// Going to be hashing a string. Could change stuff here if you wanted to hash something else.
typedef string Type;

class HashItem{
protected:
	Type name;
public:
	virtual string print(){ // this gets overriden
		return "";
	}
	HashItem(Type n) // because not abstract
		: name(n){}
	HashItem(){}
	Type get_name(){ // Other things inherit their name from hashitem
		return name;
	}
	void set_name(Type n){
		name = n;
	}

	// Overloading the << operator.
	// usage: cout << yourhashitempointer;
	// simply calls the print function that returns a string.
	friend ostream& operator<<(ostream& printer, HashItem* item){
		printer << item->print();
		return printer;
	}
};