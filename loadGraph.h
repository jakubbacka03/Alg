#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <numeric>
#include <list>

using namespace std;

class loadGraph
{
private:
	void AddEdge(int from, int to, vector<list<int>>& adjacencyList);
	int DFS(int startVertex, vector<bool>& visited, vector<list<int>>& adjacencyList);
	int BFS(int startVertex, vector<bool>& visited, vector<list<int>>& adjacencyList);
	int findLargestComponent(vector<list<int>>& adjacencyList);
	void FindEccentricities(vector<list<int>>& adjacencyList);

public:
	loadGraph(string path);
};
