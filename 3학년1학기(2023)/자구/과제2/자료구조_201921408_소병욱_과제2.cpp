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
void AddEdge_Undirected(Graph G, int u, int v); // 4.무방향 그래프 엣지 추가
void PrintGraph(Graph G); // 5.그래프 출력
void DFSUtil(Graph G, int startNode, int visited[]); // 6.그래프 DFS 핵심기능 구현
void DFS(Graph G, int startNode); // 7.그래프 DFS 간소화된 인터페이스 제공


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

// ! 4.무방향(Undirected) 그래프 엣지 추가
// ~ 사실 방향 엣지를 양 방향에 만들어주는 함수
void AddEdge_Undirected(Graph G, int u, int v) {
    AddEdge(G, u, v);
    AddEdge(G, v, u);
}

// ! 5.그래프 출력
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
    printf("NULL\n");
    }
}

// ! 6.그래프 DFS 기능 출력
// ~ 깊이 우선 검색(DFS) 알고리즘의 핵심 구현입니다. 주어진 노드에서 시작하여 DFS 순회를 수행합니다. 
void DFSUtil(Graph G, int startNode, int visited[]) {
    visited[startNode] = 1; // 현재 노드를 방문한 것으로 표시
    printf("%d -> ", startNode);

    AdjListNode currentNode = G->Adj[startNode]->Next; // 현재 노드의 첫 번째 인접 노드를 가져옴

    // 특정한 순서로 인접한 노드를 저장하기 위한 배열 생성
    AdjListNode* adjacentNodes = (AdjListNode*)malloc(G->V * sizeof(AdjListNode));
    int numAdjacentNodes = 0;

    while (currentNode) {
        if (visited[currentNode->NodeNum] == 0) { // 인접한 노드가 방문되지 않은 경우
            adjacentNodes[numAdjacentNodes++] = G->Adj[currentNode->NodeNum]; // 인접한 노드를 배열에 저장
            visited[currentNode->NodeNum] = 1; // 인접한 노드를 방문한 것으로 표시
        }
        currentNode = currentNode->Next; // 다음 인접한 노드로 이동
    }

    // 노드 번호를 기준으로 오름차순으로 인접한 노드 정렬
    for (int i = 0; i < numAdjacentNodes - 1; i++) {
        for (int j = i + 1; j < numAdjacentNodes; j++) {
            if (adjacentNodes[i]->NodeNum > adjacentNodes[j]->NodeNum) {
                AdjListNode temp = adjacentNodes[i];
                adjacentNodes[i] = adjacentNodes[j];
                adjacentNodes[j] = temp;
            }
        }
    }

    // 정렬된 순서로 인접한 노드를 재귀적으로 방문
    for (int i = 0; i < numAdjacentNodes; i++) {
        DFSUtil(G, adjacentNodes[i]->NodeNum, visited);
    }

    free(adjacentNodes); // 배열에 할당된 메모리 해제
}

// ! 7.그래프 DFS
// ~ 그래프에서 DFS 순회를 수행하기 위한 간소화된 인터페이스를 제공
void DFS(Graph G, int startNode) {
    printf("\nDFS result: ");
    int V = G->V; // 그래프의 전체 노드 수
    int *visited = (int *)malloc(V * sizeof(int)); // 방문한 노드를 추적하기 위한 배열 생성

    for (int i = 0; i < V; i++) {
        visited[i] = 0; // 모든 노드를 방문하지 않은 것으로 초기화
    }

    DFSUtil(G, startNode, visited); // DFSUtil 함수를 호출하여 DFS 탐색 실행

    free(visited); // 방문 배열에 할당된 메모리 해제
    printf("NULL\n");
}

// ! 8.그래프 BFS 기능 출력
void BFS(Graph G, int startNode) {
    int V = G->V;
    int* visited = (int*)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) {
        visited[i] = 0;
    }
    
    // Create a queue for BFS
    int* queue = (int*)malloc(V * sizeof(int));
    int front = 0, rear = 0;
    
    // Enqueue the start node and mark it as visited
    queue[rear++] = startNode;
    visited[startNode] = 1;
    
    printf("BFS result: ");
    
    while (front != rear) {
        // Dequeue a node from the queue
        int currentNode = queue[front++];
        printf("%d -> ", currentNode);
        
        AdjListNode adjacentNode = G->Adj[currentNode]->Next;
        while (adjacentNode) {
            if (visited[adjacentNode->NodeNum] == 0) {
                // Enqueue the adjacent node and mark it as visited
                queue[rear++] = adjacentNode->NodeNum;
                visited[adjacentNode->NodeNum] = 1;
            }
            adjacentNode = adjacentNode->Next;
        }
    }
    
    printf("NULL\n");
    
    free(visited);
    free(queue);
}




// ! 메인함수
int main() {

    //! 그래프 생성
    Graph G;
    G = CreateGraph(10); // 노드 9개짜리 무방향 그래프 생성

    //! 엣지 생성
    // 방향 엣지로 하나하나 추가
    AddEdge(G, 1, 2);
    AddEdge(G, 1, 4);
    AddEdge(G, 1, 6);
    AddEdge(G, 2, 1);
    AddEdge(G, 2, 5);
    AddEdge(G, 2, 8);
    AddEdge(G, 3, 4);
    AddEdge(G, 4, 1);
    AddEdge(G, 4, 3);
    AddEdge(G, 5, 2);
    AddEdge(G, 5, 7);
    AddEdge(G, 6, 1);
    AddEdge(G, 6, 8);
    AddEdge(G, 7, 5);
    AddEdge(G, 7, 9);
    AddEdge(G, 8, 2);
    AddEdge(G, 8, 6);
    AddEdge(G, 8, 9);
    AddEdge(G, 9, 7);
    AddEdge(G, 9, 8);

    PrintGraph(G);

    // 1 -> 2 -> 4 -> 6 -> NULL
    // 2 -> 1 -> 5 -> 8 -> NULL
    // 3 -> 4 -> NULL
    // 4 -> 1 -> 3 -> NULL
    // 5 -> 2 -> 7 -> NULL
    // 6 -> 1 -> 8 -> NULL
    // 7 -> 5 -> 9 -> NULL
    // 8 -> 2 -> 6 -> 9 -> NULL
    // 9 -> 7 -> 8 -> NULL

    //! DFS
    DFS(G, 5);
    //5 -> 2 -> 1 -> 4 -> 3 -> 6 -> 8 -> 9 -> 7 -> NULL
    //5 2 1 4 3 6 8 9 7
    BFS(G, 5);
    //5 -> 2 -> 7 -> 1 -> 8 -> 9 -> 4 -> 6 -> 3 -> NULL
    //5 2 7 1 8 9 4 6 3


    return 0;
}