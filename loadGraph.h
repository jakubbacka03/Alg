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
		int FindEccentricities(const vector<vector<int>>& graph, int& radius, int& diameter);		

	public:
		loadGraph(string path);		
};

