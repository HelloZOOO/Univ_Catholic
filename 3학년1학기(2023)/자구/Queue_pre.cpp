//원형리스트(큐) 구현

#include <stdio.h>
#include <stdlib.h>

struct CircularQueue; //구조체 형태로 선언

typedef int ElementType; //큐는 정수 엘리먼트를 갖게된다
typedef struct CircularQueue* Queue; //서큘러 큐 포인터를 갖는 Queue를 선언해준다

//구조체 선언
struct CircularQueue
{
    ElementType* Array;
    //엘리먼트(정수) 어레이를 갖는다 하지만 맥시멈 크기를 따로 안정하고 
    //생성할때 맥시멈 사이즈를 정해주기위해 포인터 어레이로 이름을 붙여줌
    int Front;
    int Rear;
    int Size; //리스트 최대사이즈
    int Capacity; //용량을 확인하기위해 Capacity추가
};

//코드 상단 함수 선언
int isEmpty(Queue Q); //리스트로 선언되기때문에 리스트가 비어있는지 확인
int isFull(Queue Q); //리스트가 꽉차있는지 확인
Queue CreateQueue(int MaxSize); //큐 생성
void MakeEmpty(Queue Q); //큐 비우기
int CheckIdx(int Index, Queue Q); //최대 인덱스에 도달했는지 확인
void Enqueue(ElementType X, Queue Q); //큐 추가
ElementType Dequeue(Queue Q); //큐 삭제
ElementType GetFront(Queue Q); //큐의 맨앞을 받아오는 함수
ElementType GetRear(Queue Q); //큐의 맨 뒤 받아오는 함수
void PrintQueue(Queue Q); // 큐 값을 출력합니다 비어있는 리스트는 출력 X
void PrintArray(Queue Q); //비어있는 리스트 포함 큐 값을 출력


//함수 구현
Queue CreateQueue(int MaxSize)
{
    Queue Q; //큐를 생성
    Q = (Queue)malloc(sizeof(struct CircularQueue)); //스트럭트 크기만큼 메모리 할당
    Q->Capacity = MaxSize; // Capacity가 곧 인수 MaxSizze
    Q->Array = (ElementType*)malloc(Q->Capacity * sizeof(ElementType)); //int * 임 (띄어쓰기 있어도 상관 X)
    //구조체 CircularQueue의 배열을 동적으로 할당

    //모든 엘리먼트의 요소를 NULL로 초기화
    for (int i = 0; i < Q->Capacity; i++) {
        Q->Array[i] = NULL;
    }
    Q->Size = 0; //엘리먼트가 없기때문 //방금 추가해서 크기는 0
    Q->Front = 1; //인큐를 하면 리어에 인덱스가 1씩 증가하게되는데 프론트가 리어보다 인덱스가 하나 많은 상태여야한다
    Q->Rear = 0;

    return Q;

}

int isEmpty(Queue Q)
{
    return(Q->Size == 0);
}

int isFull(Queue Q)
{
    return(Q->Size == Q->Capacity);//최대크기 인덱스와 같다면 꽉 찬 상태이니
}

void MakeEmpty(Queue Q)
{
    Q->Size = 0;
    Q->Front = 1;
    Q->Rear = 0;
}

//서큘러 어레이 특성상 가장 마지막 인덱스보다 커지면 0으로 초기화되어야하는데, 다음과같이 인덱스와 Capacity를 비교를 하는데
//인덱스에 1을 더한 상태에서qlry
//만약 인덱스 크기가 5라면 0~4 일탠데, 캐파시티가 5 인덱스가 4면 인덱스에 1을 더해서
//한마디로 인덱스가 최대크기와 동일할때 리턴한다
int CheckIdx(int Index, Queue Q)
{
    //1추가된 인덱스
    if (++Index == Q->Capacity) {
        Index = 0;
    }
    return Index;
}

//큐 추가 함수
void Enqueue(ElementType X, Queue Q)
{
    //꽉차있으면 그냥 프린트하고 끝
    if (isFull(Q))
    {
        printf("Queue is full\n");
        return;
    }
    //안꽉차있으면
    Q->Size = Q->Size + 1; // 혹은 Q->Size++ 로 표현가능 // 사이즈를 1 증가시키고 
    Q->Rear = CheckIdx(Q->Rear, Q); // Rear -> CheckIdx를 통해 0으로 초기화하거나 1을 증가시킨다
    Q->Array[Q->Rear] = X; // 큐의 Array에 변경된 Rear에 X를 추가
}

ElementType Dequeue(Queue Q)
{
    ElementType Y = -9999; //더미값
    if (isEmpty(Q))
    {
        printf("Queue is empty\n");
        return Y;
    }
    Q->Size = Q->Size - 1; //Q->Size-- 로 표현가능 
    Y = GetFront(Q);
    Q->Front = CheckIdx(Q->Front, Q);
    return Y;
}

ElementType GetFront(Queue Q)
{
    return (Q->Array[Q->Front]);
}

ElementType GetRear(Queue Q)
{
    return (Q->Array[Q->Rear]);
}

void PrintQueue(Queue Q)
{
    int i = 0;
    int idx = Q->Front;

    while (i < Q->Size)
    {
        printf(" %d ", Q->Array[idx]);
        idx = CheckIdx(idx, Q);
        i++;
    }
    printf("\n");
}

void PrintArray(Queue Q)
{
    for (int i = 0; i < Q->Capacity; i++) {
        printf(" %d ", Q->Array[i]);
    }
}


//////////////////

int main()
{
    Queue Q;

    Q = CreateQueue(10);

    Enqueue(1, Q);
    Enqueue(3, Q);
    Enqueue(4, Q);
    PrintQueue(Q); //큐출력
    PrintArray(Q); //리스트 출력

    printf("\n****************************************************************\n");
    //크기가 초과되도록 큐 추가
    Enqueue(5, Q);
    Enqueue(8, Q);
    Enqueue(10, Q);
    Enqueue(11, Q);
    Enqueue(12, Q);
    Enqueue(14, Q);
    Enqueue(16, Q);
    PrintQueue(Q); //큐출력
    PrintArray(Q); //리스트 출력

    printf("\n****************************************************************\n");
    //큐 삭제
    Dequeue(Q);
    Dequeue(Q);
    PrintQueue(Q); //큐출력
    PrintArray(Q); //리스트 출력

    return 0;
}