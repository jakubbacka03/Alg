#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <numeric>

using namespace std;

class loadGraph
{
private:
	void AddEdge(int from, int to, vector<vector<int>>& adjacencyMatrix);
	int DFS(int startVertex, vector<bool>& visited, vector<vector<int>>& adjacencyMatrix);
	int BFS(int startVertex, vector<bool>& visited, vector<vector<int>>& adjacencyMatrix);
	int findLargestComponent(vector<vector<int>>& adjacencyMatrix);
	void FindEccentricities(vector<vector<int>>& adjacencyMatrix);

public:
	loadGraph(string path);
};

