#include "loadGraph.h"
#include "loadGraph.h"
#include <stack>
#include <list>

void loadGraph::AddEdge(int from, int to, vector<list<int>>& adjacencyList)
{
    if (from == to)
        return;
    adjacencyList[from].push_back(to);
    adjacencyList[to].push_back(from);
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
    vector<list<int>> adjacencyList(max_vertex + 1);
    inputfile.open(path);

    while (inputfile >> from >> to)
    {
        AddEdge(from, to, adjacencyList);
    }
    inputfile.close();

    //largest component
    int largestComponentSize = findLargestComponent(adjacencyList);
    cout << "Largest component: " << largestComponentSize << endl;

    //eccentricities
    FindEccentricities(adjacencyList);
}

int loadGraph::DFS(int startVertex, vector<bool>& visited, vector<list<int>>& adjacencyList)
{
    int verticesInComponent = 0;
    stack<int> st;

    st.push(startVertex);
    visited[startVertex] = true;

    while (!st.empty())
    {
        int v = st.top();
        st.pop();

        ++verticesInComponent;

        for (int i : adjacencyList[v])
        {
            if (!visited[i])
            {
                visited[i] = true;
                st.push(i);
            }
        }
    }
    return verticesInComponent;
}

int loadGraph::BFS(int startVertex, vector<bool>& visited, vector<list<int>>& adjacencyList)
{
    queue<int> q;
    visited[startVertex] = true;
    q.push(startVertex);
    int eccentricity = 0;

    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++)
        {
            int vertex = q.front();
            q.pop();


            for (int j : adjacencyList[vertex])
            {
                if (!visited[j])
                {
                    visited[j] = true;
                    q.push(j);
                }
            }
        }
        eccentricity++;
    }
    return eccentricity;
}

int loadGraph::findLargestComponent(vector<list<int>>& adjacencyList)
{
    int maxVertex = adjacencyList.size() - 1;
    vector<bool> visited(maxVertex + 1, false);
    int largestComponentSize = 0;

    for (int i = 1; i <= maxVertex; ++i)
    {
        if (!visited[i])
        {
            int componentSize = DFS(i, visited, adjacencyList);
            largestComponentSize = max(largestComponentSize, componentSize);
        }
    }
    return largestComponentSize;
}


void loadGraph::FindEccentricities(vector<list<int>>& adjacencyList)
{
    int maxVertex = adjacencyList.size() - 1;
    vector<bool> visited(maxVertex + 1, false);
    int largestComponentSize = 0;
    int radius = INT_MAX;
    int diameter = 0;

    for (int i = 1; i <= maxVertex; ++i)
    {
        if (!visited[i]) {
            int componentSize = DFS(i, visited, adjacencyList);
            largestComponentSize = max(largestComponentSize, componentSize);
            int eccentricity = 0;

            for (int j = 1; j <= maxVertex; ++j)
            {
                if (visited[j])
                {
                    vector<bool> tempVisited(maxVertex + 1, false);
                    eccentricity = max(eccentricity, BFS(j, tempVisited, adjacencyList));
                }
            }
            radius = min(radius, eccentricity);
            diameter = max(diameter, eccentricity);
        }
    }
    cout << "Radius of largest component: " << radius << endl;
    cout << "Diameter of largest component: " << diameter << endl;
}
