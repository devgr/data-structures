/** HashTable.h
George Darling 11/01/2013

 HashTable class, works with HashItems. This is not templated because it
 uses hashitem types instead of some unknown type. The reason for this is
 if it were templated, you could send it a Car type. How do you hash a car?
 Who knows? But if the car is derived from hashitem, it now has a key that
 can be hashed.

 Hash table provides an all in one hashing system, using strings for keys.
 The table is implemented with a std::vector with std:lists as chains for
 storing HashItems.
*/

#pragma once
#include "HashItem.h"
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

using namespace std; // everything I'm doing uses std namespace, so that is helpful.

class HashTable
{
private:
	int tablesize;
	int numofitems;
	int numlistsused;
	double loadfactor;
	vector<list<HashItem *>> * table;
	//list<T> * table;
	// A hash table implemented with a vector with lists for chains. Using vector
	// rather than array so that the table can more easily be resized.

	int hashfunction(string);
	void calcloadfactor();
public:
	HashTable(int); // size of table
	~HashTable();

	void dump(bool);
	void Add(HashItem *);
	void Remove(string);
	list<HashItem*>::iterator Find(string, int&, bool&, int&);
};

