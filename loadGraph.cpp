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

    // largest component
    int largestComponentSize = findLargestComponent(adjacencyList);
    cout << "Largest component: " << largestComponentSize << endl;

    // eccentricities
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
    vector<int> distance(adjacencyList.size(), 0);

    q.push(startVertex);
    visited[startVertex] = true;

    int eccentricity = 0;

    visited = vector<bool>(adjacencyList.size(), false);

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        for (int neighbor : adjacencyList[current])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                distance[neighbor] = distance[current] + 1;

                eccentricity = max(eccentricity, distance[neighbor]);

                q.push(neighbor);
            }
        }
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

    int radius = INT_MAX;
    int diameter = 0;

    for (int i = 1; i <= maxVertex; ++i)
    {
        
        int eccentricity = BFS(i, visited, adjacencyList);

        // update radius and diameter
        radius = min(radius, eccentricity);
        diameter = max(diameter, eccentricity);
        
    }

    cout << "Radius: " << radius << endl;
    cout << "Diameter: " << diameter << endl;
}
