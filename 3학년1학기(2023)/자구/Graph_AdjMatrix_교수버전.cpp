#include <stdio.h>
#include <stdlib.h>

#define MAX_V 10

struct VE{
	int V;
	bool Adj[MAX_V][MAX_V];
};

typedef struct VE *Graph;

Graph CreateGraph(int V);
void AddEdge(Graph G, int u, int v);
void PrintGraph(Graph G);

Graph CreateGraph(int V){
	Graph G;
	G = (Graph)malloc(sizeof(struct VE));
	
	G->V = V;
	for(int i=0; i<G->V; i++){
		for(int j=0; j<G->V; j++){
			G->Adj[i][j]=false;
		}
	}
	
	return G;
}

void AddEdge(Graph G, int u, int v){
	G->Adj[u][v] = true;
}

void PrintGraph(Graph G){
	int V = G->V;
	for(int i=0; i<V; i++){
		for(int j=0; j<V; j++){
			if(G->Adj[i][j]){
				printf("%d -> %d\n", i, j);
			}
		}
	}
}

int main(){
	Graph G;
	G = CreateGraph(5);
	
	AddEdge(G, 0, 1);
	AddEdge(G, 0, 2);
	AddEdge(G, 0, 3);
	AddEdge(G, 1, 2);
	AddEdge(G, 1, 4);
	AddEdge(G, 2, 4);
	AddEdge(G, 3, 4);
	
	PrintGraph(G);
	
	return 0;
}
