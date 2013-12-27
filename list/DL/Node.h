/** Node.h
George Darling 9/5/2013

Header file for the Node type. Each node points to a next node and a previous
node, forming a doubly linked list. There is a spot to hold data; this can
either be modified to fit the needs of the program, or point to some other
data containing type.
*/
#include "Data.h"
using namespace std;

class Node{
	Data * data;
	Node * next; // these are private, Node and List are friends so
	Node * prev; // they can access and change.

	public:
		Node(Data*, Node*, Node*); // data, prev, next
		~Node(); // destruct the node

		Data * getData();

		friend class List;
};