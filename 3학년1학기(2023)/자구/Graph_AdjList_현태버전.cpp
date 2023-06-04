#include <stdio.h>
#include <stdlib.h>

struct Node;
struct List;
struct VE;


typedef struct Node* AdjListNode; //노드의 포인터에 해당하는 AdjListNode
typedef AdjListNode *Head; // 노드의 포인터AdjListNode의 포인터 typedef struct Node **Head
typedef AdjListNode *Head; // 노드의 포인터AdjListNode의 포인터 typedef struct Node **Head
typedef struct VE* Graph;
//~ AdjListNode는 Node의 더블 포인터 (typedef Node** Head;)

// 노드 선언
struct Node {
   int NodeNum; // 노드 번호
   AdjListNode Next; // 다음을 가르키는 포인터
};

// 하나의 자료형만 가지고 있기에 구현할 필요가 없다.
/*
// 리스트 선언
struct List {
   AdjListNode Head; // 헤드
};
*/

// 그래프 선언
struct VE {
   int V; // vertax의 크기
   // AdjList Adj; // 인접리스트
    Head Adj;
};


AdjListNode NewNode(int NodeNum); // 노드 생성
Graph CreateGraph(int V); // 그래프 생성
void AddEdge(Graph G, int u, int v); // 엣지 추가
void PrintGraph(Graph G); // 그래프 출력

void AddEdge_Undirected(Graph G, int u, int v); // 무방향 그래프 엣지 추가

// 노드 생성
AdjListNode NewNode(int NodeNum) {
    AdjListNode newNode;// 노드 생성
   newNode = (AdjListNode)malloc(sizeof(struct Node)); // 메모리 할당

   newNode->NodeNum = NodeNum; // 노드 번호 설정
   newNode->Next = NULL; // 다음 리스트 일단 비워둠

    return newNode;

}


// 그래프 생성
Graph CreateGraph(int V) {
   Graph G; // 그래프 생성
   G = (Graph)malloc(sizeof(struct VE)); // 메모리 할당
   G->V = V; // vertax 크기 설정

   // 그래프의 인접리스트에 메모리 할당
   G->Adj = (Head)malloc(V * sizeof(struct Node));
   // 인접리스트는 노드의 개수만큼 리스트가 필요하므로 V * 메모리할당

   // vertax 크기만큼 반복
    for (int i = 0; i < V; i++)
      G->Adj[i] = NewNode(i); // i번 노드 생성

    return G;
}


// 엣지 추가
void AddEdge(Graph G, int u, int v) {
    AdjListNode newNode;
   newNode = NewNode(v); // v노드 생성

   // 원래 상태 :u -> x
   newNode->Next = G->Adj[u]->Next; // v의 다음 = u의 다음 (v -> x)
   G->Adj[u]->Next = newNode; // u의 다음 = v (u -> v)
   // 완료 후 : u -> v -> x
}

// 무방향 그래프 엣지 추가
void AddEdge_Undirected(Graph G, int u, int v) {
    AddEdge(G, u, v);
    AddEdge(G, v, u);
}


// 그래프 출력
void PrintGraph(Graph G) {
   int V = G->V; // vertax의 크기

   // 모든 vartax(시작점)에 대해 실행
    for (int i = 0; i < V; i++) {
        AdjListNode Tmp;
      Tmp = G->Adj[i]; // 시작 노드
      // 다음 노드가 있을 때까지
    while (Tmp) {
        printf("%d -> ", Tmp->NodeNum);
         Tmp = Tmp->Next; // 다음 노드로
        }
    printf("\n");
    }
}


int main() {

    Graph G1;
   G1 = CreateGraph(5); // 노드 5개짜리 방향 그래프 생성

   // 그래프 엣지 추가
    AddEdge(G1, 0, 1);
    AddEdge(G1, 0, 2);
    AddEdge(G1, 0, 3); // 0 -> 3 -> 2 -> 1
    AddEdge(G1, 1, 2);
    AddEdge(G1, 1, 4); // 1 -> 4 -> 2
    AddEdge(G1, 2, 4); // 2 -> 4
    AddEdge(G1, 3, 4); // 3 -> 4
    PrintGraph(G1);

    printf("======================================================\n");


    Graph G2;
   G2 = CreateGraph(5); // 노드 5개짜리 무방향 그래프 생성

   // 그래프 엣지 추가
    AddEdge_Undirected(G2, 0, 1);
    AddEdge_Undirected(G2, 0, 2);
    AddEdge_Undirected(G2, 0, 3);
    AddEdge_Undirected(G2, 1, 2); 
    AddEdge_Undirected(G2, 1, 4);
    AddEdge_Undirected(G2, 2, 4); 
    AddEdge_Undirected(G2, 3, 4); 
    PrintGraph(G2);

   // 0 -> 3 -> 2 -> 1
   // 1 -> 4 -> 2 -> 0 
   // 2 -> 4 -> 1 -> 0 
   // 3 -> 4 -> 0 
   // 4 -> 3 -> 2 -> 1

   // 아래와 같이 u,v를 바꿔서 추가해줘도 된다.
   // AddEdge(G,0,1);
   // AddEdge(G,1,0);

    return 0;
}