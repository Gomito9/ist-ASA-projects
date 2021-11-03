#include <iostream>
#include <stdio.h>
#include <list>
#include <vector>
#include <stack>

using namespace std;

int V, E;
int maxPath = 0;
int minClicks = 0;

vector<vector<int>> adj;
vector<vector<int>> adjTranspose;

vector<int> nrChildren;
vector<int> maxReach;
vector<bool> visited;

stack<int> dominoStack;

void buildBases();
void playDominos();
void dfsDominos();
void printInfo();


void buildBases() {
	
	if (scanf("%d %d", &V, &E) != 2 || V < 2 || E < 0 ) {
		printf("Erro: conjunto \"V E\" inválido");
		exit(1);
	}
	
	 /*Build Graphs */
	adj = vector<vector<int>>(V, vector<int>(0));
	adjTranspose = vector<vector<int>>(V, vector<int>(0));

	for(int i=0; i<E ;i++){
        int u, v;
        if (scanf("%d %d",&u,&v) != 2) {
					printf("Erro: conjunto \"u v\" inválido");
					exit(1);
				}

				adj[u-1].push_back(v-1);
				adjTranspose[v-1].push_back(u-1);
	}
	
	visited = vector<bool>(V);		/* Build vector of visited vertices */
	maxReach = vector<int>(V);		/* Build vector of max path reachable through each vertex */
	nrChildren = vector<int>(V);	/* Build counting vector of vertices' children */

	for (int i = 0; i < V; i++) {  /* Setup vectors */
		visited[i] = false;
		maxReach[i] = 1;
		nrChildren[i] = (int) adj[i].size();
	}
}



void playDominos() {

	for(int k = 0; k < V; k++) {
		if (adjTranspose[k].size() == 0) {
			minClicks++;
			dominoStack.push(k);	
		}
	}

	dfsDominos();
}



void dfsDominos() {
	int v;
	int sonsVisited;

	while (!dominoStack.empty()) {
		v = dominoStack.top();
		sonsVisited = 0;		

		if (!visited[v])
			visited[v] = true;

		int nrSons = (int) nrChildren[v];
		for (int i=0; i < nrSons; i++) {
			int son = adj[v][i];

			if (!visited[son])
				dominoStack.push(son);
			else
				sonsVisited+=1;
					
			if (maxReach[v] < (maxReach[son] + 1))
				maxReach[v] = maxReach[son] + 1;						
		}
		
		if (sonsVisited == nrSons)
			dominoStack.pop();

	}
}



void printInfo() { 
	for (int i = 0; i < V; i++) {
		if (maxReach[i] > maxPath) 	
			maxPath = maxReach[i];
	}

	printf("%d %d\n", minClicks, maxPath); 
}

int main() {
	buildBases();
	playDominos();
	printInfo();
	return 0;
}

