#include <stdio.h>
#include <stdlib.h>

struct Node;
struct List;
struct VE;

typedef struct Node *AdjListNode;
typedef AdjListNode *Head; // typedef struct Node **Head
typedef struct VE *Graph;

struct Node{
	int NodeNum;
	AdjListNode Next;
};


struct VE{
	int V;
	Head Adj; //AdjList Adj;
};

AdjListNode NewNode(int NodeNum);
Graph CreateGraph(int V);
void AddEdge(Graph G, int u, int v);
void PrintGraph(Graph G);

AdjListNode NewNode(int NodeNum){
	AdjListNode newNode;
	newNode = (AdjListNode)malloc(sizeof(struct Node));
	newNode->NodeNum = NodeNum;
	newNode->Next = NULL;
	return newNode;
}

Graph CreateGraph(int V){
	Graph G;
	G = (Graph)malloc(sizeof(struct VE));
	
	G->V = V;
	G->Adj = (Head)malloc(V*sizeof(struct Node));
	for(int i=0; i<V; i++){
		G->Adj[i] = NewNode(i);
	}
	
	return G;
}

void AddEdge(Graph G, int u, int v){
	AdjListNode newNode;
	newNode = NewNode(v);
	
	newNode->Next = G->Adj[u]->Next;
	G->Adj[u]->Next = newNode;
}

void AddEdge_Und(Graph G, int u, int v){
	AddEdge(G, u, v);
	AddEdge(G, v, u);
}

void PrintGraph(Graph G){
	int V = G->V;
	for(int i=0; i<V; i++){
		AdjListNode Tmp;
		Tmp = G->Adj[i];
		
		while(Tmp){
			printf(" %d -> ", Tmp->NodeNum);
			Tmp = Tmp->Next;
		}
		printf("\n");
	}
}

int main(){
	int V;
	V = 5;
	
	Graph G;
	G = CreateGraph(V);
		
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
