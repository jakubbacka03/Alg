#include <iostream>
#include <utility>
#include "Graph.h"

int main()
{
    using clock = chrono::high_resolution_clock;
    Graph g;
       
    clock::time_point t1 = clock::now();

    g.loadGraph("graph2.txt");
    g.findLargestComponent();
    g.findEccentricities();
    g.findRadiusAndDiameter();
    
    clock::time_point t2 = clock::now();

    auto timeOfProgram = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();

    cout << "Duration of program: " << timeOfProgram << "ms" << endl;

    return 0;
}
