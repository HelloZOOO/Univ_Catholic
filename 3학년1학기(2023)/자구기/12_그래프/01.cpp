//배열로 인접리스트 구현

#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX 30

//!그래프를 인접 행렬로 표현하기위한 구조처 정의
typedef struct graphType{
    int n;
    int adjMatrix[MAX_VERTEX][MAX_VERTEX]; // 30 x 30 2차원 배열 그래프
}grantptType;

//!공백 그래프를 생성하는 연산
void createGraph(grantptType *g){
    int i, j;
    g->n = 0; //그래프 정점(노드) 개수를 0으로 초기화

    //* 그래프 내부 모든 배열을 0으로 초기화
    for(i = 0; i < MAX_VERTEX; i++){
        for(j = 0; j < MAX_VERTEX; j++){
            g->adjMatrix[i][j] = 0;
        }
    }
}

//! 그래프 g에 정점 v를 삽입하는 연산
void insertVertex(grantptType *g, int v){
    //*노드가 이미 최대개수야?
    if((g->n)>MAX_VERTEX){
        printf("\n 그래프 정점개수가 초과되었습니다.\n");
        return;
    }
    g->n++; //*노드 추가 가능하면 노드 개수를 나타내는 n 증가시켜~
}

//! 그래프 g에 간선(u,v)를 추가하는 연산 (엣지 추가)
void insertEdge(grantptType *g, int u, int v){
    //*n은 1씩 증가하기 때문에 
    //*u나 v가 노드 개수 보다 큰 값이 들어오면 그것은 없는 값임
    if(u >= g->n || v >= g->n){
        printf("\n 그래프에 없는 정점입니다");
        return;
    }
    //* 1값은 곧 연결 되어있다는 뜻.
    // (예를 들어 간선 [5][6]=1 이라는것은 5와 6이 붙어있다는 뜻)
    g->adjMatrix[u][v] = 1;
}

void print_adjMatrix(grantptType *g){
    int i, j;
    for(i = 0; i < g->n; i++){
        printf("\n\t\t");
        for(j = 0; j < g->n; j++){
            printf("%d ", g->adjMatrix[i][j]);
        }
    }
}

int main(){
    int i;
    grantptType *G1,*G2,*G3,*G4;
    G1 = (grantptType *)malloc(sizeof(grantptType));
    G2 = (grantptType *)malloc(sizeof(grantptType));
    G3 = (grantptType *)malloc(sizeof(grantptType));
    G4 = (grantptType *)malloc(sizeof(grantptType));
    createGraph(G1); createGraph(G2); createGraph(G3); createGraph(G4);

    //~ 그래프 G1
    for (i = 0; i < 4; i++)
        insertVertex(G1, i);  // G1의 정점 0~3 삽입 
    insertEdge(G1, 0, 1);
    insertEdge(G1, 0, 3);
    insertEdge(G1, 1, 0);
    insertEdge(G1, 1, 2);
    insertEdge(G1, 1, 3);
    insertEdge(G1, 2, 1);
    insertEdge(G1, 2, 3);
    insertEdge(G1, 3, 0);
    insertEdge(G1, 3, 1);
    insertEdge(G1, 3, 2);
    printf("\n G1의 인접 행렬");
    print_adjMatrix(G1);

    //~ 그래프 G2
    //* 완전 연결 리스트라 엣지의 개수는 n(n-1)/2 개
    for (i = 0; i < 3; i++)
        insertVertex(G2, i);  // G2의 정점 0~2 삽입 
    insertEdge(G2, 0, 1);
    insertEdge(G2, 0, 2);
    insertEdge(G2, 1, 0);
    insertEdge(G2, 1, 2);
    insertEdge(G2, 2, 0);
    insertEdge(G2, 2, 1);
    printf("\n\n G2의 인접 행렬");
    print_adjMatrix(G2);

    //~ 그래프 G3
    for (i = 0; i < 4; i++)
        insertVertex(G3, i); // G3의 정점 0~3 삽입
    insertEdge(G3, 0, 1);
    insertEdge(G3, 0, 3);
    insertEdge(G3, 1, 2);
    insertEdge(G3, 1, 3);
    insertEdge(G3, 2, 3);
    printf("\n\n G3의 인접 행렬");
    print_adjMatrix(G3);

    //~ 그래프 G4
    for (i = 0; i < 3; i++)
        insertVertex(G4, i);    // G4의 정점 0~2 삽입 
    insertEdge(G4, 0, 1);
    insertEdge(G4, 0, 2);
    insertEdge(G4, 1, 0);
    insertEdge(G4, 1, 2);
    printf("\n\n G4의 인접 행렬");
    print_adjMatrix(G4);

}