#ifndef KEYED_ITEM_H
#define KEYED_ITEM_H

#include <string>

using namespace std;

/*
 * Use either
 * 1) a "typedef" for "KeyType" or
 * 2) make "KeyType" a template parameter
 */

class KeyedItem{
public:
   KeyedItem() {}
   KeyedItem(const KeyType& keyValue)
      : searchKey(keyValue) {}
   
   KeyType getKey() const{  return searchKey; }
   void setKey(const KeyType key) {  searchKey = key; }
   
   friend ostream& operator<< (ostream& out, KeyedItem* keyItem){
       out << "KeyedItem: " << keyItem->getKey() << endl;
       return out;
   }
       
protected:
   KeyType searchKey;
}; // end KeyedItem

#endif /* KEYED_ITEM_H */
