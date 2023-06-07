#include <stdio.h>
#include <stdlib.h>

// !연결리스트로 구현

struct Node;
struct List;
struct VE;

typedef struct Node* AdjListNode; //노드의 포인터에 해당하는 AdjListNode
typedef AdjListNode *Head; // 노드의 포인터AdjListNode의 포인터 typedef struct Node **Head
//~ AdjListNode는 Node의 더블 포인터 (typedef Node** Head;)
typedef struct VE* Graph; // VE를 가르키는 구조체는 Graph다

// !노드 선언
struct Node {
   int NodeNum; // 노드 번호
   AdjListNode Next; // 다음을 가르키는 포인터
};

/*
// 리스트 선언 이었던 것 //
// 하나의 자료형만 가지고 있기에 구현할 필요가 없다.
struct List {
   AdjListNode Head; // 헤드
};
*/

// !그래프 선언
struct VE {
    int V; // vertax의 크기
    Head Adj;
    //노드의 이중포인터인 Head Adj는 곧 노드의 이중포인터
    //*위에서 Head를 Node를 가르키는 포인터인 AdjListNode를 가르키는 노드이니 Adj = **Node 와 같다
};

// !함수 선언부
AdjListNode NewNode(int NodeNum); // 1.노드 생성
Graph CreateGraph(int V); // 2.그래프 생성
void AddEdge(Graph G, int u, int v); // 3.엣지 추가
void PrintGraph(Graph G); // 4.그래프 출력
void AddEdge_Undirected(Graph G, int u, int v); // 5.무방향 그래프 엣지 추가

// ! 1.노드 생성
//노드의 포인트에 해당하는 newNode
//newNode에 메모리를 할당하는데 하나의 구조체 노드만큼의 메모리를 할당하고
//이 노드의 노드 넘버는 int로 받은 nodeNum으로 대체해주고
//다음을 가르키는 노드는 NULL로 설정
//그리고 newNode를 반환하면 Head에 Node가 추가되겠지?
AdjListNode NewNode(int NodeNum) {
    AdjListNode newNode; //* Node를 가르키는 newNode 노드 생성
    newNode = (AdjListNode)malloc(sizeof(struct Node)); // 메모리 할당
    //~newNode는 Node만큼의 크기의 메모리를 할당한다.
    //~malloc 함수 앞에 AdjListNode를 적는 것은 malloc 함수에 할당할 메모리의 타입을 지정하는 것입니다.

    newNode->NodeNum = NodeNum; //~ Node 구조체 내부에 노드번호는 입력받은 인수 NodeNum입니다.
    newNode->Next = NULL; // Node의 다음 노드는 NULL로 해둠

    return newNode; //반환 자료형은 struct 입니다.
}


// ! 2.그래프 생성
//메모리를 할당하고 그래프 생성
Graph CreateGraph(int V) {
    Graph G; // 그래프 생성
    G = (Graph)malloc(sizeof(struct VE)); // 메모리 할당 //~결국 G가 노드의개수
    //~G에 구조체VE의 메모리 크기를 할당합니다.
    //~이떄 Graph는 G에게 할당할 메모리 타입을 지정하는 것.
    G->V = V; // vertax 크기 설정
    //*메모리 할당이 완료된 그래프 G에 벡터V를 입력인수 V로 초기화한다

    // 그래프의 인접리스트에 메모리 할당
    G->Adj = (Head)malloc(V * sizeof(struct Node));
    //? 인접리스트는 노드의 개수만큼 리스트가 필요하므로 V * 메모리할당
    //~ 그래프 G의 (Head Adj)의 메모리 크기는 버텍스의 수 * 노드의 개수만큼 할당됩니다.
    //? Malloc은 void*를 반환하기에 Node**인 Head로 오버라이딩하여 G에 대입합니다.

    // vertax 크기만큼 반복
    for (int i = 0; i < V; i++)
        G->Adj[i] = NewNode(i); // i번 노드 생성
        //Adj는 총 V개만큼 메모리가 할당되어있다

    return G; //그래프 G를 꼭 리턴
}


// ! 3.엣지 추가
//어떤 그래프를 고를거냐? 출발지에 해당하는 인덱스 u와 목적지에 해당하는 인덱스 v 
void AddEdge(Graph G, int u, int v) {
    AdjListNode newNode; //새로운 노드 선언
    newNode = NewNode(v); // 목적지인 v노드는 새로운 노드다.

    // 원래 상태 :u -> x
    newNode->Next = G->Adj[u]->Next; // v노드의 다음 = u노드의 다음 (v -> x) //!Adj의 인덱스가 결국 헤더를 가르킨다
    G->Adj[u]->Next = newNode; // u의 다음 = v (u -> v)
    // 완료 후 : u -> v -> x
    //헤드는 뉴노드가 된다
}

// ! 4.그래프 출력
void PrintGraph(Graph G) {
   int V = G->V; // 버텍스는 입력된 그래프 G의 vertax 크기

   // 모든 vartax(시작점)에 대해 실행
    for (int i = 0; i < V; i++) {
        AdjListNode Tmp; //Tmp = *Node
        Tmp = G->Adj[i]; // 시작 노드
        // 다음 노드가 있을 때까지
    while (Tmp) {
        printf("%d -> ", Tmp->NodeNum);
         Tmp = Tmp->Next; // 다음 노드로
        }
    printf("\n");
    }
}

// ! 5.무방향(Undirected) 그래프 엣지 추가
void AddEdge_Undirected(Graph G, int u, int v) {
    AddEdge(G, u, v);
    AddEdge(G, v, u);
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