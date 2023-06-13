//큐를 이용해서 단어 출력하기

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define Q_SIZE 4 //큐 사이즈는 4입니다

//! 타입 선언
typedef char element; // element = char
typedef struct {
    element queue[Q_SIZE];
    int front, rear; //큐의 front와 rear을 정수형으로 정의 
} QueueType; // QueueType = queue[],front,rear을 포함함

//! 함수 정의
QueueType *createQueue();
int isEmpty(QueueType *Q); //1.큐가 비었는지 확인하는 함수
int isFull(QueueType *Q); //2.큐가 꽉찼는지 확인하는 함수
void enQueue(QueueType *Q, element item); //3.큐 내용 추가 (rear 증가)
element deQueue(QueueType *Q); //4. 큐 내용 삭제 (front 증가)
element peek(QueueType *Q); //5. 큐 rear 출력 (혹은 전체 배열중 가장 끝 배열 출력?)
void printQ(QueueType *Q); //6. 큐 출력

//! 공백 Q 생성 front = -1 rear = 0
QueueType *createQueue() {
    QueueType *Q;
    Q = (QueueType *)malloc(sizeof(QueueType));
    Q->front = -1;
    Q->rear = -1;
    return Q;
}

//! Q가 공백인가?
int isEmpty(QueueType *Q) {
    //원형큐가 아닌 이상 front와 rear이 같다는것은 큐가 초기상태 즉 비었다는 것
    if (Q->front == Q->rear){
        printf("Q is empty\n");
        return 1;
    }
    else return 0;
}

//! Q는 꽉 찼는가?
// 원형큐가 아니기때문에 나머지 연산을 사용하지 않는다
// 인덱스는 0부터 시작하기 때문에 rear가 최대 사이즈 - 1에 도달하면코드는종료된것
int isFull(QueueType *Q) {
    if (Q->rear == (Q_SIZE - 1)) {
        printf("Q is full\n");
        return 1;
    }
    else return 0;
}

//! Q에 item 삽입
void enQueue(QueueType *Q, element item) {
    if(isFull(Q)) return;
    else{
        Q->rear++; //큐를 먼저 증가시켜둬야 나중에 아이템을 추가할때 기존 아이템이 삭제될 일 없다
        Q->queue[Q->rear] = item; // Q[rear] 에 item을 넣음 처음에는 Q[0] = item
    }
}

//! Q에서 front 내용 삭제
// enQueue는 void인데 왜 deQueue는 반환값이 char입니까?
element deQueue(QueueType *Q) {
    if(isEmpty(Q)) exit(1);
    else{
        Q->front++;
        return Q->queue[Q->front]; // frront에 
    }
}

//! Q의 가장 앞 원소를 출력
element peek(QueueType *Q) {
    if(isEmpty(Q)) exit(1);
    else return Q->queue[Q->front+1]; // 큐기 때문에 rear이 아닌 front를 출력해야한다
    //front에 1을 더해준 이유는 front를 그대로 출력하면 그곳은 이미 삭제된 노드..
}

void printQ(QueueType *Q) {
    printf("Q : [");
    for (int i = Q->front + 1; i <= Q->rear; i++)
        printf("%3c ", Q->queue[i]);
    printf("]\n");
}

int main(void) {
	QueueType *Q1 = createQueue();// 큐 생성
	element data;
	printf("\n ***** 순차 큐 연산 ***** \n");
	printf("\n 삽입 A>>");  enQueue(Q1, 'A'); printQ(Q1);
	printf("\n 삽입 B>>");  enQueue(Q1, 'B'); printQ(Q1);
	printf("\n 삽입 C>>");  enQueue(Q1, 'C'); printQ(Q1);
	data = peek(Q1);printf("\t\t\t\tpeek item : %c \n", data);

	printf("\n 삭제 >>"); data = deQueue(Q1); printQ(Q1);
	printf("\t\t\t\t삭제 데이터 : %c", data);
	printf("\n 삭제 >>"); data = deQueue(Q1); printQ(Q1);
	printf("\t\t\t\t삭제 데이터 : %c", data);
	printf("\n 삭제 >>");  data = deQueue(Q1); printQ(Q1);
	printf("\t\t\t\t삭제 데이터 : %c", data);

	printf("\n 삽입 D>>"); enQueue(Q1, 'D'); printQ(Q1);
	printf("\n 삽입 E>>"); enQueue(Q1, 'E'); printQ(Q1);
}
