#include "Graph.h"

void Graph::loadGraph(string path)
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
        unsigned int compare = max(from, to) + 1;

        if (this->adjList.size() < compare)
        {
            this->adjList.resize(compare);
        }

        this->adjList[from].push_back(to);
        this->adjList[to].push_back(from);
    }
    inputfile.close();

    this->listOfVertices.resize(this->adjList.size());
    this->largestComponent.resize(this->adjList.size());

    for (int i = 0;i < this->adjList.size(); i++)
    {
        if (!this->adjList[i].empty())
        {
            this->listOfVertices.push_back(i);
        }
    }
}

vector<int> Graph::DFS(int startVertex, vector<bool>& visited)
{   
    vector<int> verticesInComponent;
    stack<int> st;

    st.push(startVertex);
    verticesInComponent.push_back(startVertex);
    visited[startVertex] = true;

    while (!st.empty())
    {
        int v = st.top();
        st.pop();

        for (int i : this->adjList[v])
        {
            if (!visited[i])
            {
                verticesInComponent.push_back(i);
                visited[i] = true;
                st.push(i);
            }
        }
    }
    return verticesInComponent;
}

void Graph::findLargestComponent()
{
    vector<bool> visited(this->adjList.size(), false);
    size_t largestComponentSize = 0;
    vector<int> component;

    for (int i : this->listOfVertices)
    {
        if (!visited[i])
        {
            component = DFS(i, visited);
        }
        if (largestComponentSize < component.size())
        {
            largestComponentSize = component.size();
            this->largestComponent = component;
        }
    }
    cout << "Largest component size: " << largestComponentSize << endl;
}

void Graph::findEccentricities()
{
    int a = 0;
    queue<int> q;
    for (int i : this->largestComponent)
    {
        vector<bool> visited(this->adjList.size(), 0);
        int dis = 0;
        q.push(i);
        visited[i] = true;
        a++;
        vector<int> distance(this->adjList.size());
        distance[i] = 0;
        while (!q.empty())
        {
            int current = q.front();
            q.pop();

            for (int neighbor : this->adjList[current])
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    
                    q.push(neighbor);
                    distance[neighbor] = distance[current] + 1;
                    dis = max(dis, distance[neighbor]);
                }
            }
        }
        this->eccentricity.push_back(dis);
        cout << a << endl;
    }
}

void Graph::findRadiusAndDiameter()
{
    int radius = INT_MAX;
    int diameter = 0;

    for (int i : this->eccentricity)
    {
        radius = min(radius, i);
        diameter = max(diameter, i);
    }
    
    cout << "Diameter: " << diameter << endl;
    cout << "Radius: " << radius << endl;

}
