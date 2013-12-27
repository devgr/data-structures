/* Digraph.cpp
George Darling

Lab 7
12/05/13

Implementation of the Directed Graph class. see Digraph.h for details.
*/
#include "Digraph.h"
using namespace std;

Digraph::Digraph()
{
	// Initialize everything
	graph = new list<list<string>*>();
	sorted = new list<string>();
	vertices = new unordered_set<string>();
	visited = new unordered_set<string>();
	tempvisited = new unordered_set<string>();
	numedges = 0;
	numvertices = 0;
}

Digraph::~Digraph()
{
	// clean up sets
	delete visited;
	delete vertices;
	// go through graph clear each list, then clearing big list
	for (list<list<string>*>::iterator it = graph->begin(); it != graph->end(); it++)
		(**it).clear(); // check out that double dereference!
	graph->clear();
	delete graph;
	delete sorted;
	// bye!
}

void Digraph::visit(list<string> * chain){
	if (tempvisited->count(chain->front())) // if this vertex has been tempvisited, return
		return;
	if (!visited->count(chain->front())){ // if not visited
		tempvisited->insert(chain->front()); // mark temporarily
		// Go down the list starting at the second one and visit those
		for (list<string>::iterator jt = (chain->begin())++; jt != chain->end(); jt++){
			// find the corresponding list in the big list for that vertex and recurse
			for (list<list<string>*>::iterator it = graph->begin(); it != graph->end(); it++){
				if ((*it)->front() == (*jt)) // first in it's list == the one adjacent to the first in chain
					visit((*it));
			}
		}
		visited->insert(chain->front()); // Add to visited
		tempvisited->erase(chain->front()); // remove from tempvisited
		vertices->erase(chain->front()); // remove from vertices?
		sorted->push_front(chain->front()); // push front on sorted
	}
}
void Digraph::toposort(){
	// A depthfirst search style topological sort	
	list<list<string>*>::iterator it = graph->begin();
	while (!vertices->empty()){
		visit((*it)); // pass visit that vertex's adjacency list
		it++; // will this get us through all of the vertices?
	}
	// print out sorted
	cout << "Prerequisites Graph: ";
	list<string>::iterator namesp = sorted->begin();
	cout << (*namesp);
	namesp++;
	while (namesp != sorted->end()){
		cout << ", ";
		cout << (*namesp);
		namesp++;
	}
	cout << endl;

	// reload vertices
	for (list<list<string>*>::iterator vertp = graph->begin(); vertp != graph->end(); vertp++)
		vertices->insert((*vertp)->front());

	visited->clear(); // clear stuff for next run
	vertices->clear();
	tempvisited->clear();
	sorted->clear();
}
void Digraph::printgraph(){
	for (list<list<string>*>::iterator it = graph->begin(); it != graph->end(); it++){
		for (list<string>::iterator jt = (*it)->begin(); jt != (*it)->end(); jt++){
			cout << (*jt) << endl;
		}
		cout << endl;
	}
}

void Digraph::addvertex(string name){
	if (vertices->count(name)) return; // don't bother
	else{
		vertices->insert(name); // Ok, adding a new vertex now
		graph->push_back(new list<string>); // I'm adding a new list of strings to the big list
		graph->back()->push_back(name); // the name of the vertex is the first item in the list.
		numvertices++;
	}
}
void Digraph::addedge(string a, string b){ // edge from a to b 
	// look for correct list
	for (list<list<string>*>::iterator it = graph->begin(); it != graph->end(); it++){
		if ((*it)->front() == a){ // found it
			// add to the list
			numedges++;
			(*it)->push_back(b);
			break;
		}
	}
}


