#include <iostream>
#include "Graph.h"

using namespace std;
int main() {
	Graph g;
	g.inputGraphFromFile("graf1.txt");
	g.printGraph();
	//cout << "Spojnosc: " << g.checkConnectivity();
	//cout << "Ilosc skladowych: " << g.getQuantityOfComponents() << endl;
	g.getBridges();
	system("pause");
}