#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <utility>
class Graph
{
	unsigned vertex; //ilosc wierzcholkow
	unsigned edge; //ilosc krawedzi
	//std::vector<unsigned> *adjList; //lista s¹siedztwa
	std::list<unsigned> *adjList;
	std::vector<std::pair<unsigned, unsigned>> edges;
public:
	Graph();
	~Graph();

	void inputGraph(); //wczytanie grafu z konsoli
	bool inputGraphFromFile(std::string src); //wczytanie grafu z pliku (plik nie moze byc zakonczony enterem)
	bool checkConnectivity();
	void getBridges(); //wypisanie mostow rozleglych grafu
	int getQuantityOfComponents();
	void printGraph();
};

#endif // !GRAPH_H