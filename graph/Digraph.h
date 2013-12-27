/* Digraph.h
George Darling

Lab 7
12/05/13

Directed Graph class. The graph is stored as an adjacency list, which is implemented
with a std::list of std::lists. Vertices can be added, edges can be created, and a 
topological sort can be done on the graph to show an order of prerequisites.

Some things to add. It would make sense to have either a generic digraph that uses
digraph vertices (rather than just the specific string), or have this class be templated
to support different sorts of values in the vertices.
*/
#pragma once
#include <iostream>
#include <string>
#include <list>
#include <unordered_set> // maybe
using namespace std;

class Digraph
{
private:
	list<list<string>*> * graph; // Adjacency list
	list<string> * sorted; // used in topo sort
	unordered_set<string> * vertices; // Just a set of the vertices so I can easily check if it has been added yet.
	unordered_set<string> * visited; // for use in the topological sort
	unordered_set<string> * tempvisited; // used in 
	int numedges; // keep track of how much things.
	int numvertices;

	void visit(list<string>* ); // part of depth first search
	void printgraph(); // just helpful

public:
	void toposort(); // Does a topological sort. Returns true if a sort is found, false if not.
	void addvertex(string); // extend the big list to have another vertex!
	void addedge(string, string); // add an edge from, to
	Digraph(); // only constructor needed, makes an empty directed graph
	~Digraph(); // deletes each list, then deletes the big list.
};

