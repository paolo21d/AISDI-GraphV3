#include "Graph.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <fstream>
#include <string>

using namespace std;

/*bool Graph::delFunc(const unsigned &d) {
	return d==removeElement;
}*/

Graph::Graph() {
	vertex = 0;
	edge = 0;
	adjList = nullptr;
}


Graph::~Graph() {
	if (adjList != nullptr)
		delete[] adjList;
}

void Graph::inputGraph() {
	cin >> vertex >> edge;
	adjList = new list<unsigned>[vertex]; //zaalokowanie pami�ci na list� s�siedztwa
	unsigned v1, v2;
	for (unsigned i = 0; i < edge; ++i) { //wczytanie krawedzi do list sasiedztwa
		cin >> v1 >> v2;
		adjList[v1].push_back(v2);
		adjList[v2].push_back(v1);
		edges.push_back(make_pair(v1, v2));
	}

	/*for (unsigned i = 0; i < vertex; ++i) { //posortowanie list s�siedztwa
		sort(adjList[i].begin(), adjList[i].end());
	}*/
}

bool Graph::inputGraphFromFile(string src) {
	fstream file;
	file.open(src, ios::in);
	if (!file.good())
		return false;

	file >> vertex;
	adjList = new list<unsigned>[vertex]; //zaalokowanie pami�ci na list� s�siedztwa
	unsigned v1, v2;
	while (file.good()) {
		file >> v1 >> v2;
		if (file.fail()) break; //sprawdzenie czy to juz byl koniec danych
		++edge;
		adjList[v1].push_back(v2);
		adjList[v2].push_back(v1);
		edges.push_back(make_pair(v1, v2));
	}

	/*for (unsigned i = 0; i < vertex; ++i) { //posortowanie list s�siedztwa
		sort(adjList[i].begin(), adjList[i].end());
	}*/

	file.close();
	return true;
}

void Graph::inputGraphLab(){
	cin >> vertex;
	adjList = new list<unsigned>[vertex]; //zaalokowanie pami�ci na list� s�siedztwa
	unsigned v1, v2;
	unsigned e=0;
	while(!cin.eof()){
		cin >>v1 >> v2;
		adjList[v1].push_back(v2);
		adjList[v2].push_back(v1);
		edges.push_back(make_pair(v1, v2));
		++e;
	}
	edge=e;
}

bool Graph::checkConnectivity() {
	vector<bool>visited;
	unsigned v, u, vc = 0;
	for (int i = 0; i < vertex; ++i) visited.push_back(false);
	stack<unsigned> s;

	if (vertex == 0) return true; //graf pusty traktujemy jako spojny

	s.push(0);
	visited[0] = true;
	while (!s.empty()) {
		v = s.top();
		s.pop();
		++vc;
		for (auto it = adjList[v].begin(); it != adjList[v].end(); ++it) {
			u = *it;
			if (!visited[u]) {
				visited[u] = true;
				s.push(u);
			}
		}
	}

	if (vc == vertex) return true;
	else return false;
}

void Graph::getBridges() {
	unsigned delV1, delV2;
	list<unsigned> delEdges1, delEdges2;
	list<unsigned> *pointerV1, *pointerV2;
	int cn; //ilosc skladowych grafu
	for (int i = 0; i < edge; ++i) {
		delV1 = edges[i].first;
		delV2 = edges[i].second;
		delEdges1 = adjList[delV1];
		delEdges2 = adjList[delV2];

		pointerV1 = &adjList[delV1];
		pointerV2 = &adjList[delV2];
		//usuwam krawedzie od wierzcholka 1
		//removeElement = delV1;
		pointerV1->clear();
		for (auto it = delEdges1.begin(); it != delEdges1.end(); ++it) { //usun kolejne krawedzie dochodzace do wierzcholka 1
			for (auto del = adjList[*it].begin(); del != adjList[*it].end(); ++del) {
				if (*del == delV1) {
					adjList[*it].erase(del);
					break;
				}
			}
			//adjList[*it].remove_if(delFunc);
		}

		//usuwam krawedzie od wierzcholka 2
		pointerV2->clear();
		//removeElement = delV1;
		for (auto it = delEdges2.begin(); it != delEdges2.end(); ++it) { //usun kolejne krawedzie dochodzace do wierzcholka 2
			for (auto del = adjList[*it].begin(); del != adjList[*it].end(); ++del) {
				if (*del == delV2) {
					adjList[*it].erase(del);
					break;
				}
			}
			//adjList[*it].remove_if(delFunc);
		}
		//cout << "######Usuwam krawedz: " << delV1 << " " << delV2 << endl;
		//printGraph();
		//sprawdzenie ilosci skladowych
		cn = getQuantityOfComponents();
		if (cn > 3) cout << "Most rozlegly: " << delV1 << " " << delV2 << endl;

		//ponowne dodanie krawedzi
		adjList[delV1] = delEdges1;
		for (auto it = delEdges1.begin(); it != delEdges1.end(); ++it) {
			if (*it == delV2) continue;
			adjList[*it].push_back(delV1);
		}

		adjList[delV2] = delEdges2;
		for (auto it = delEdges2.begin(); it != delEdges2.end(); ++it) {
			if (*it == delV1) continue;
			adjList[*it].push_back(delV2);
		}
		//cout << "***Oryginalny graf: " << endl;
		//printGraph();
	}
}

int Graph::getQuantityOfComponents() {
	int cn = 0;                    // Zerujemy licznik sp�jnych sk�adowych
	unsigned v, u;
	vector<bool> visited;
	stack<unsigned> S;
	for (unsigned i = 0; i < vertex; ++i) visited.push_back(false); //zerowanie listy odwiedzonych wierzcholkow

	for (unsigned i = 0; i < vertex; ++i)
		if (!visited[i])                // Szukamy nieodwiedzonego jeszcze wierzcho�ka
		{
			cn++;                  // Zwi�kszamy licznik sk�adowych
			S.push(i);             // Na stosie umieszczamy numer bie��cego wierzcho�ka
			visited[i] = true;             // i oznaczamy go jako odwiedzonego i ponumerowanego
			while (!S.empty())      // Przechodzimy graf algorytmem DFS
			{
				v = S.top();         // Pobieramy wierzcho�ek
				S.pop();             // Usuwamy go ze stosu
									 // Przegl�damy s�siad�w wierzcho�ka v
				for (auto it = adjList[v].begin(); it != adjList[v].end(); ++it) {
					u = *it;
					if (!visited[u]) {
						S.push(u);
						visited[u] = true;
					}
				}
			}
		}

	return cn;
}

void Graph::printGraph() {
	cout << "Vertex: " << vertex << "\tEdge: " << edge << endl;
	for (int i = 0; i < vertex; ++i) {
		cout << "V " << i << ":\t";
		//for (int x = 0; x < adjList[i].size(); ++x)
		//	cout << adjList[i][x] << " ";
		for (auto it = adjList[i].begin(); it != adjList[i].end(); ++it)
			cout << *it << " ";
		cout << endl;
	}
}
