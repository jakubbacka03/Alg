#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <fstream>
#include <numeric>
#include <iostream>
#include <chrono>

using namespace std;

class Graph
{
	public:	
		vector<vector<int>> adjList; ///< Vektor vektorov (tj. dvojrozmerné pole), kde každý vektor reprezentuje zoznam susedov pre jednotlivé vrcholy grafu
		vector<int>listOfVertices; ///< Počet vrchoov
		vector<int> largestComponent; ///< Najväčšia komponenta
		vector<int> eccentricity; ///< Excentricita vrcholu grafu

		/**
		* Načitava graf z textového súboru, pre každú hranu uloží zdrojový a cieľový vrchol
		* Funkcia vytvára aj zoznam vrcholov grafu a inicializuje zoznam pre najväčšiu komponentu grafu
		* 
		* @param path je vstupny string pre txt súbor
		* 
		* @return void
		*/
		void loadGraph(string path);

		/**
		* Funkcia DFS vykoná prehľadávanie do hĺbky grafu začínajúc v určenom vrchole. Vráti zoznam všetkých vrcholov,
		* ktoré patria do tej istej komponenty ako počiatočný vrchol
		* 
		* @param startVertex Počiatočný vrchol, v ktorom začne prehľadávanie
		* @param visited Pole boolean hodnôt označujúce, ktoré vrcholy už boli navštívené
		* 
		* @return Zoznam vrcholov, ktoré patria do rovnakej komponenty ako počiatočný vrchol
		*/
		vector<int> DFS(int startVertex, vector<bool>& visited);

		/**
		* Najde najväčšiu komponentu v neorientovanom grafe a uloží ju do premennej largestComponent
		* Použije prehľadávanie do hĺbky (DFS) na prehľadanie jednotlivých komponent
		* 
		* @return void
		*/
		void findLargestComponent();

		/**
		* Funkcia vypočíta excentricity všetkých uzlov najväčšej komponenty grafu
		* Funkcia najprv inicializuje počiatočné hodnoty pre výpočet a následne iteruje cez každý uzol v najväčšej komponente
		* Pre každý uzol sa následne vypočíta excentricita pomocou BFS (breadth-first search) algoritmu
		* Pre každý navštívený uzol sa zaznamená jeho vzdialenosť od počiatočného uzla a tá sa porovná s maximálnou vzdialenosťou
		* Nakoniec sa vypočítaná excentricita pridá do vektoru excentricít a vypíše sa aktuálny počet spracovaných uzlov
		* 
		* @return void
		*/
		void findEccentricities();

		/**
		* Funkcia vracia hodnoty radius a diameter
		* 
		* @return void
		*/
		void findRadiusAndDiameter();
};
