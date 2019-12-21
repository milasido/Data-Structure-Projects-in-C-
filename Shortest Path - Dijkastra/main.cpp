#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cfloat>
#include <iomanip>
#include"ArgumentManager.h"
using namespace std;

//read source---------------------------------------
int readSource(ifstream &ifs, string path)
{
	int source = 0, dest = 0;
	ifs.open(path);
	while (!ifs.eof())
	{
		ifs >> source; ifs >> dest;
	}
	ifs.close();
	return source;
}
//read destination-------------------------------------
int readDest(ifstream &ifs, string path)
{
	int source = 0, dest = 0;
	ifs.open(path);
	while (!ifs.eof())
	{
		ifs >> source; ifs >> dest;
	}
	ifs.close();
	return dest;
}
//read size matrix----------------------------------------
int matrixsize(ifstream &ifs, string input)
{
	int s, d; double w; 
	string line; 
	vector<int> a; 
	ifs.open(input);
	while (!ifs.eof())
	{
		ifs >> s; ifs >> d; ifs >> w;
			a.push_back(s);
			a.push_back(d);
	}
	int count = *max_element(a.begin(), a.end());

	ifs.close();
	return count+1;
}
//create graph------------------------------------------------
double **createGraph(ifstream &ifs, string input, int V)
{
	ifs.open(input);
	double **graph = new double*[V];
	for (int i = 0; i < V; ++i)
		graph[i] = new double[V];

	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
			graph[i][j] = DBL_MAX;
	int s, d; double w;
	while (!ifs.eof())
	{
		ifs >> s; ifs >> d; ifs >> w;
		graph[s][d] = w;
		//graph[d][s] = w;
	}
	ifs.close();
	return graph;
}
//return min distance of vertex-------------------------------
int minDistance(double *dist, bool sptSet[], int V)
{
	// Initialize min value 
	double min = DBL_MAX;
	int min_index;

	for (int v = 0; v < V; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

// Function that implements Dijkstra's single source shortest path algorithm 
// for a graph represented using adjacency matrix representation 
double dijkstra(double **graph, int src, int dest, int V)
{
	double *dist = new double[V];     // The output array.  dist[i] will hold the shortest 
					 // distance from src to i 

	bool *sptSet = new bool[V]; // sptSet[i] will be true if vertex i is included in shortest 
					// path tree or shortest distance from src to i is finalized 

	// Initialize all distances as INFINITE and stpSet[] as false 
	for (int i = 0; i < V; i++)
		dist[i] = DBL_MAX, sptSet[i] = false;

	// Distance of source vertex from itself is always 0 
	dist[src] = 0;

	// Find shortest path for all vertices 
	for (int count = 0; count < V - 1; count++)
	{
		// Pick the minimum distance vertex from the set of vertices not 
		// yet processed. u is always equal to src in the first iteration. 
		int u = minDistance(dist, sptSet, V);

		// Mark the picked vertex as processed 
		sptSet[u] = true;

		// Update dist value of the adjacent vertices of the picked vertex. 
		for (int v = 0; v < V; v++)

			// Update dist[v] only if is not in sptSet, there is an edge from  
			// u to v, and total weight of path from src to  v through u is  
			// smaller than current value of dist[v] 
			if (sptSet[v] == false && graph[u][v] && dist[u] != DBL_MAX 
				&& dist[u] + graph[u][v] < dist[v])

				dist[v] = dist[u] + graph[u][v];
	}
	if (dest > V - 1)
		return DBL_MAX;
	else
		return dist[dest];
}

int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");
	string path = am.get("path");
//int main()
//{	
//	string input = "input90.txt";
//	string path = "path90.txt";
//	string output = "aaa.txt";

	ifstream ifs; ofstream ofs;
	int source = readSource(ifs, path);
	int dest = readDest(ifs, path);
	int size = matrixsize(ifs, input);
	
	double **graph = createGraph(ifs, input, size);	
	double shortest = dijkstra(graph, source, dest, size);
	
	ofs.open(output);
	if (shortest == DBL_MAX)
		ofs << "Infinite";
	else ofs << fixed << setprecision(1) << shortest;

	ofs.close();
	//system("pause");
	return 0;
}