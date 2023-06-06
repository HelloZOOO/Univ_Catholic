#include <stdio.h>
#include <stdlib.h>

struct CircularQueue; //구조체 형태로 원형 큐 선언

typedef int ElementType; //ElementType은 정수형이다
typedef struct CircularQueue* Queue; //Queue는 구조체 원형 큐를 가르킨다

//! ... 구조체 원형 큐 선언
struct CircularQueue {
    ElementType* Array; //원형 큐의 요소는 정수값을 가진다
    //따로 맥시멈 사이즈가 없어 생성할때 맥시멈 사이즈를 정해주기 위해 포인터로 선언
    int Front; //맨앞
    int Rear; //맨뒤
    int Size; //리스트 사이즈
    int Capacity; //리스트 최대 용량을 확인하기 위함
};

//! ... 함수 프로토타입
/*
컴파일러가 함수의 전체 정의를 보기 전에 호출이 올바른지 확인할 수 있습니다
(즉, 올바른 수와 유형의 인수를 가지는지)
*/
int isEmpty(Queue Q); //큐는 리스트로 선언되었기에 리스트가 비어있는지 확인
int isFull(Queue Q); //리스트가 꽉 차 있는지 확인
Queue CreateQueue(int MaxSize); //큐 생성(리스트 최대 크기)
void MakeEmpty(Queue Q); //큐 비우기
int CheckIdx(int Index, Queue Q); // rear이 최대 인덱스에 도달했는지 확인
void Enqueue(ElementType X, Queue Q); //X값을 가진 큐 추가
ElementType Dequeue(Queue Q); //큐 삭제
ElementType GetFront(Queue Q); //맨 앞 큐를 받아옴
ElementType GetRear(Queue Q); //맨 뒤 큐를 받아옴
void PrintQueue(Queue Q); // 큐 값을 출력합니다 비어있는 리스트는 출력 X
void PrintArray(Queue Q); //비어있는 리스트 포함 큐 값을 출력

//! ... 함수 구현 ... //\
================================================================

//! ... 큐 생성
Queue CreateQueue(int MaxSize) {
    Queue Q; //큐 생성
    Q = (Queue)malloc(sizeof(struct CircularQueue)); //구조체 CircularQueue만큼 메모리를 Q에 할당
    Q->Capacity = MaxSize; // Capacity는 인수 MaxSize
    Q->Array = (ElementType*)malloc(Q->Capacity * sizeof(ElementType));
    /*
    구조체 CircularQueue의 배열을 동적으로 할당하고,
    할당된 메모리의 시작 주소를 가리키는 포인터를 Q->Array에 저장하는 것입니다.

    Q의 최대크기 * int의 바이트 크기
    (최대크기가 5고 int형이면 총 크기는 40이 할당된다)
    */

    //모든 엘리먼트의 요소를 NULL로 초기화
    for (int i = 0; i < Q->Capacity; i++) {
        Q->Array[i] = NULL;
    }
    Q->Size = 0; //방금 추가해서 요소가 업식 때문에 크기는 0
    Q->Front = 1;
    Q->Rear = 0;
    /*
    큐를추가하면 하면 Rear에 인덱스가 1씩 증가하게되는데
    Front가 Rear보다 인덱스가 하나 더 많은 상태여야한다

    큐가 비어있는 경우 Front와 Rear가 같은 위치를 가리키게 됩니다.
    이때 큐에 요소를 추가하면
    Rear가 증가하게 되고, Front와 Rear가 같은 위치를 가리키게 됩니다
    */

    return Q;
}

//! ... 큐가 비어있습니까?
//큐가 비어있으면(Size == 0이라면) 1(참)을 반환하고, 아니면 0(거짓)을 반환
int isEmpty(Queue Q) {
    return(Q->Size == 0);
}

//! ... 큐가 꽉 찼습니까?
//큐가 꽉차면(Size == Capacity(MaxSize)) 1(참)을 반환하고, 아니면 0(거짓)을 반환
int isFull(Queue Q) {
    return(Q->Size == Q->Capacity);
}

//! ... 큐 전체 비우기
void MakeEmpty(Queue Q) {
    Q->Size = 0; //큐의 리스트 사이즈는 0입니다
    Q->Front = 1;
    Q->Rear = 0;
    //Front와 Rear의 위치를 초기값으로 되돌립니다
}

//! ... 큐의 Rear이 최대 인덱스에 도달했는지 확인
/*
서큘러 어레이 특성상 가장 Rear가 마지막 인덱스보다 커지면 0으로 초기화되어야하는데,
다음과같이 인덱스와 Capacity(MaxSize)를 비교한다
인덱스에 1을 더한 상태에서비교 (배열은 0부터 시작하기에)
만약 인덱스 크기가 5라면 0~4 일탠데, Capacity가 5에 인덱스가 4면 인덱스에 1을 더해서
한마디로 인덱스가 최대크기와 동일할때 리턴한다

원형 큐에서 Rear는 배열의 마지막 요소에 도달하면 다시 배열의 첫 번째 요소로 돌아가야 합니다.
따라서 ++Index가 Q->Capacity와 같아지면 Index를 0으로 초기화해야 합니다.
*/
int CheckIdx(int Index, Queue Q) {
    //++Indxex가 곧 Rear이다
    if (++Index == Q->Capacity) { //?if문 안에서도 일단 인덱스가 증가하는건가?
        Index = 0; //인덱스는 배열의 첫번째로 돌아갑니다
    //todo if문 내용이 거짓이더라도 ++Index는 작동하여
    //todo Index Input값이 3이고 Capacity가 10이라면 리턴값은 4입니다.        
    }
    return Index; //첫번째 배열을 반환합니다
}

//! ... 큐추가
void Enqueue(ElementType X, Queue Q) {

    //만약 큐가 꽉 차 있다면?
    if (isFull(Q)) {
        printf("Queue is full\n");
        return; //그냥 코드 종료
    }

    //큐 추가가 가능하다면
    Q->Size = Q->Size + 1; //배열의 인덱스를 증가시킵니다 (혹은 Q->Size++ 로 표현가능)
    Q->Rear = CheckIdx(Q->Rear, Q); // Rear을 0으로 초기화하거나 1을 증가시킨다
    Q->Array[Q->Rear] = X; // 큐의 Array에 변경된 Rear에 X를 추가

    /*
    위 코드에서 Q->Size = Q->Size + 1;는 배열의 인덱스를 증가시키는 코드입니다.
    큐에 새로운 요소가 추가되면 배열의 인덱스를 증가시켜야 합니다.

    Q->Rear = CheckIdx(Q->Rear, Q);는 ++Index가 곧 Rear이므로 Rear을 ++Index로 표현합니다.
    CheckIdx 함수에서는 ++Index를 계산하고 배열의 첫번째로 돌아가는 경우를 처리합니다.

    Q->Array[Q->Rear] = X;는 새로운 요소를 큐에 추가하는 코드입니다.
    Rear이 가리키는 위치에 새로운 요소를 추가합니다.
    */
}

//! ... 큐삭제
ElementType Dequeue(Queue Q) {
    ElementType Y = -9999; //에러값 Y는 -9999로 정의
    if (isEmpty(Q)) { //만약 큐가 비어있다면
        printf("Queue is empty\n");
        return Y; //에러값 -9999를 리턴
    }

    //큐가 비어있지 않은 경우, 큐의 맨 앞 원소를 반환하고 삭제
    Q->Size = Q->Size - 1; //배열의 인덱스를 감소시킵니다 (Q->Size-- 로 표현가능) 
    Y = GetFront(Q); //Y는 Q의 가장 앞줄의 인덱스를 가집니다
    Q->Front = CheckIdx(Q->Front, Q); //Q의 ++Front 가 레이어 최대사이즈에 도달하면 0 아니라면 Front값
    /*
    Dequeue 함수에서는 큐의 맨 앞 원소를 삭제한 후,
    CheckIdx 함수를 사용하여 Front 값을 갱신하고
    CheckIdx 함수는 Rear 값을 증가시키기 위해 사용됩니다.
    */
    return Y;
}

//! ... 맨 앞 큐를 받아옴
ElementType GetFront(Queue Q) {
    return(Q->Array[Q->Front]); //Front는 정수 1값(초기값 기준)
    //Array[1] 임
}

//! ... 맨 뒤 큐를 받아옴
ElementType GetRear(Queue Q) {
    return(Q->Array[Q->Rear]); //Rear은 정수 0값(초기값 기준)
}

//! ... 큐 값만 출력 (어레이에 저장된 값만 출력)
//큐 값이 저장된 Size 크기만큼만 출력
void PrintQueue(Queue Q) {
    int i = 0;
    int idx = Q->Front; //인덱스는 Q의 맨 앞

    while (i < Q->Size) { //0부터 Q의 현재 큐가 채워진 배열 사이즈만큼 반복
        printf(" %d ", Q->Array[idx]); //증가된 idx값
        idx = CheckIdx(idx, Q); //?CheckIdx(++Index==Capacity)부분에서 인덱스 이미 증가한상태
        i++;
    }
    printf("\n");
}

//! ... 값이 비어있어도 전체 출력
//최대 크기 전부 출력
void PrintArray(Queue Q) {
    for (int i = 0; i < Q->Capacity; i++) {
        printf(" %d ", Q->Array[i]);
    } //최대 크기만큼 그냥 출력
}

int main() {
    Queue Q;

    Q = CreateQueue(10);

    Enqueue(1, Q);
    Enqueue(3, Q);
    Enqueue(4, Q);
    PrintQueue(Q);
    PrintArray(Q);
    printf("\n#####1#####\n");
    Enqueue(5, Q);
    Enqueue(8, Q);
    Enqueue(10, Q);
    Enqueue(11, Q);
    Enqueue(12, Q);
    Enqueue(14, Q);
    Enqueue(16, Q);
    PrintQueue(Q);
    PrintArray(Q);
    printf("\n#####2#####\n");
    Dequeue(Q);
    Dequeue(Q);
    PrintQueue(Q);
    PrintArray(Q);

    return 0;
}