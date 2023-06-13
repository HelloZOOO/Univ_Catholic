//원형큐 구현

#include <stdio.h>
#include <stdlib.h>
#define cQ_SIZE 4

typedef char element;
typedef struct {
    element data[cQ_SIZE];
    int front,rear;
} QueueType;

//! 함수 정의
QueueType *createQueue();
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
element deQueue(QueueType *cQ);
element peek(QueueType *cQ);
void printQ(QueueType *cQ);

//! 큐 생성
//* 원형 큐는 -1이라는 개념이 없기 때문에 0부터 시작한다
QueueType *createQueue() {
    QueueType *cQ;
    //~메모리 QueueType의 시작지점부터 2비트인 char QueueType만큼 메모리를 할당하겠다
    cQ = (QueueType *)malloc(sizeof(QueueType));
    cQ->front = 0;
    cQ->rear = 0;
    return cQ;
}

//! 큐가 비어있는가?
// * 나머지 연산자를 이용한 값이 front와같을 순 있지만, front와 rear가 같다는 것은 초기상태라는 의미
int isEmpty(QueueType *cQ) {
    if(cQ->front == cQ->rear){
        printf("Queue is empty\n");
        return 1;
    }
    else return 0;
}

//! 큐가 꽉 찼는가?
int isFull(QueueType *cQ) {
    if(((cQ->rear + 1) % cQ_SIZE) == cQ->front) {
        printf("Queue is full\n");
        return 1;
    }
    else return 0;
}

//! 큐 삽입
void enQueue(QueueType *cQ, element item) {
    if(isFull(cQ)) exit(1);
    else{
        cQ->rear = (cQ->rear+1) % cQ_SIZE;
        cQ->data[cQ->rear] = item;
    }
}

//! 큐 삭제
element deQueue(QueueType *cQ) {
    if(isEmpty(cQ)) exit(1);
    else{
        cQ->front = (cQ->front + 1) % cQ_SIZE;
        return cQ->data[cQ->front];
    }
}

//! 큐 의 첫번째 값 출력
element peek(QueueType *cQ) {
    if(isEmpty(cQ)) exit(1);
    else return cQ->data[(cQ->front+1) % cQ_SIZE];
}

//! 원형 큐 출력
void printQ(QueueType *cQ) {

    int i,first,last;
    first = (cQ->front + 1) % cQ_SIZE;
    last = (cQ->rear + 1) % cQ_SIZE;
    i = first;

    printf("Queue: [");
    while (i != last) {
        printf("%2c ", cQ->data[i]);
        i=(i+1) % cQ_SIZE;
    }
    printf("]\n");
}

int main(void) {
	QueueType *cQ = createQueue();
	element data;
	printf("\n ***** 원형 큐의 연산 *****\n");
	printf("\n 삽입 A>>"); enQueue(cQ, 'A'); printQ(cQ);
	printf("\n 삽입 B>>"); enQueue(cQ, 'B'); printQ(cQ);
	printf("\n 삽입 C>>"); enQueue(cQ, 'C'); printQ(cQ);
	data = peek(cQ);printf(" peek item : %c \n", data);

	printf("\n 삭제 >>"); data = deQueue(cQ); printQ(cQ);
	printf("\t\t\t\t\t\t 삭제 데이터 : %c", data);
	printf("\n 삭제 >>"); data = deQueue(cQ); printQ(cQ);
	printf("\t\t\t\t\t\t 삭제 데이터 : %c", data);
	printf("\n 삭제 >>"); data = deQueue(cQ); printQ(cQ);
	printf("\t\t\t\t\t\t 삭제 데이터 : %c", data);

	printf("\n 삽입 D>>"); enQueue(cQ, 'D'); printQ(cQ);
	printf("\n 삽입 E>>"); enQueue(cQ, 'E'); printQ(cQ);

}
