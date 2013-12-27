#include "HashTable.h"


// constructor. sets default value and gets a vector of the right length
HashTable::HashTable(int size)
{
	tablesize = size;
	numofitems = 0;
	numlistsused = 0;
	loadfactor = 0.0;
	//table = new list<T>[size];
	table = new vector<list<HashItem *>>(tablesize); // could just use resize
}
HashTable::~HashTable()
{
	// also go through whole table deleting and clearing.
	dump(true); // magically use my dump function to delete everything
	table->clear();
	delete table;
}

void HashTable::dump(bool destroy = false){
	int index = 0; // I used iterators to go through the vector instead, but this would have been easier.
	for (vector < list < HashItem* >> ::iterator entries = (*table).begin(); entries != (*table).end(); entries++){
		if (!(*entries).empty()){
			if(!destroy) cout << "Bucket index " << index << ":\n";
			for (list<HashItem*>::iterator items = (*entries).begin(); items != (*entries).end(); items++){
				// print out each item.
				if (!destroy)
					cout << (*items);
				else{
					delete (*items);
					(*entries).erase(items);
				}
			}
		}
		index++;
	}
	cout << endl;

}
// very simply get the hash index then push it on the front of the list
void HashTable::Add(HashItem * item){
	int index = hashfunction(item->get_name());
	if ((*table)[index].empty()) numlistsused++;
	(*table)[index].push_front(item);
	numofitems++;
	calcloadfactor();
}
void HashTable::Remove(string key){
	int index = -1;
	bool found = false;
	int counter = 0;
	list<HashItem*>::iterator tempit = Find(key, index, found, counter);
	if (found){ // if item was found
		delete (*tempit); // free the memory in case
		(*table)[index].erase(tempit);
		if ((*table)[index].empty()) numlistsused--;
		numofitems--;
	}
	else cout << "ALERT: \"" << key << "\" not found!\n";
	if (counter == 1) cout << counter << " item visited for remove()\n"; // this is silly
	else cout << counter << " items visited for remove()\n";
	calcloadfactor();
}

// this is fun function! it returns a list iterator and has lots of useful parameters.
list<HashItem*>::iterator HashTable::Find(string key, int& index, bool& found, int& counter){
	counter = 0; // count how many items you traverse
	found = false;
	index = hashfunction(key);
	if ((*table)[index].empty()){ // case where there is nothing in the list at that index in the table
		return (*table)[index].begin();
	}
	//list<HashItem*>::iterator tempit = find((*table)[index].begin(), (*table)[index].end(), new HashItem(key));
	// That was a really cool line, but just made more problems.
	list<HashItem*>::iterator tempit;
	for (tempit = (*table)[index].begin(); tempit != (*table)[index].end(); tempit++){
		counter++;
		if ((*tempit)->get_name() == key){
			found = true; // otherwise it must be found, return an iterator to its location
			return tempit;
		}
	}
	// not found
	return tempit;
}

// This hash function anecdotally produces very good results
int HashTable::hashfunction(string key){
	unsigned int hashindex = 1880497;
	int index = 0;
	for (char character = key[index]; character != '\0'; character = key[++index])
		hashindex = hashindex * 197 + character;
	return hashindex % tablesize;
}
void HashTable::calcloadfactor(){
	if (numlistsused != 0) // watch for devide by 0
		loadfactor = (double)numofitems / (double)numlistsused;
	else loadfactor = 0.0;
	cout << "Alpha: " << loadfactor << endl << endl;
}
