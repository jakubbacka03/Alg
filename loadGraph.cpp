#include "loadGraph.h"
#include "loadGraph.h"
#include <stack>

void loadGraph::AddEdge(int from, int to, vector<vector<int>>& adjacencyMatrix)
{
    if (from == to)
        return;
    adjacencyMatrix[from][to] = 1;
    adjacencyMatrix[to][from] = 1;
}

loadGraph::loadGraph(string path)
{
    ifstream inputfile(path);
    if (!inputfile.is_open())
    {
        cerr << "neda sa otvorit" << endl;
        exit(1);
    }

    int max_vertex = 0;
    int from, to;

    while (inputfile >> from >> to)
    {
        max_vertex = max(max_vertex, max(from, to));
    }
    inputfile.close();
    vector<vector<int>> adjacencyMatrix(max_vertex + 1, vector<int>(max_vertex + 1, 0));
    inputfile.open(path);

    while (inputfile >> from >> to)
    {
        AddEdge(from, to, adjacencyMatrix);
    }
    inputfile.close();

    //largest component
    int largestComponentSize = findLargestComponent(adjacencyMatrix);
    cout << "Largest component: " << largestComponentSize << endl;

    //eccentricities
    FindEccentricities(adjacencyMatrix);


}

int loadGraph::DFS(int startVertex, vector<bool>& visited, vector<vector<int>>& adjacencyMatrix) {
    int verticesInComponent = 0;
    stack<int> st;

    st.push(startVertex);
    visited[startVertex] = true;

    while (!st.empty()) {
        int v = st.top();
        st.pop();

        ++verticesInComponent;

        for (int i = 1; i < adjacencyMatrix[v].size(); ++i) {
            if (adjacencyMatrix[v][i] && !visited[i]) {
                visited[i] = true;
                st.push(i);
            }
        }
    }
    return verticesInComponent;
}


int loadGraph::BFS(int startVertex, vector<bool>& visited, vector<vector<int>>& adjacencyMatrix) {
    queue<int> q;
    visited[startVertex] = true;
    q.push(startVertex);
    int eccentricity = 0;

    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            int vertex = q.front();
            q.pop();

            for (int j = 1; j < adjacencyMatrix[vertex].size(); j++) {
                if (adjacencyMatrix[vertex][j] && !visited[j]) {
                    visited[j] = true;
                    q.push(j);
                }
            }
        }
        eccentricity++;
    }
    return eccentricity;
}

int loadGraph::findLargestComponent(vector<vector<int>>& adjacencyMatrix) {
    int maxVertex = adjacencyMatrix.size() - 1;
    vector<bool> visited(maxVertex + 1, false);
    int largestComponentSize = 0;

    for (int i = 1; i <= maxVertex; ++i) {
        if (!visited[i]) {
            int componentSize = DFS(i, visited, adjacencyMatrix);
            largestComponentSize = max(largestComponentSize, componentSize);
        }
    }
    return largestComponentSize;
}

void loadGraph::FindEccentricities(vector<vector<int>>& adjacencyMatrix) {
    int maxVertex = adjacencyMatrix.size() - 1;
    vector<bool> visited(maxVertex + 1, false);
    int largestComponentSize = 0;
    int radius = INT_MAX;
    int diameter = 0;

    for (int i = 1; i <= maxVertex; ++i) {
        if (!visited[i]) {
            int componentSize = DFS(i, visited, adjacencyMatrix);
            largestComponentSize = max(largestComponentSize, componentSize);
            int eccentricity = 0;

            for (int j = 1; j <= maxVertex; ++j) {
                if (visited[j]) {
                    vector<bool> tempVisited(maxVertex + 1, false);
                    eccentricity = max(eccentricity, BFS(j, tempVisited, adjacencyMatrix));
                }
            }
            radius = min(radius, eccentricity);
            diameter = max(diameter, eccentricity);
        }
    }
    cout << "Radius of largest component: " << radius << endl;
    cout << "Diameter of largest component: " << diameter << endl;
}
