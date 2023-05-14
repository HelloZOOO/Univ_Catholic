#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//! 노드 구조체 선언
struct node {
    char data;
    struct node* next;
};

//! 큐 구조체 선언
struct queue {
    struct node* front;
    struct node* rear;
};

//! 영어 소문자인지 확인하는 함수
int is_valid_character(char c) {
    return islower(c) != 0;  // 문자가 소문자인지 확인
}

//! 큐에 노드 삽입 함수
void enqueue(struct queue* q, char c) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));

    if (new_node == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    new_node->data = c;
    new_node->next = NULL;

    if (q->front == NULL) {
        q->front = new_node;
        q->rear = new_node; // 첫 번째 노드가 추가될 때 rear 포인터를 설정합니다.
    }
    else {
        q->rear->next = new_node;
        q->rear = new_node;
    }
}


//! 큐에서 노드 삭제 함수
char dequeue(struct queue* q) {
    // 큐가 비어있는 경우 오류 메시지 출력
    if (q->front == NULL) {
        printf("큐 안에 존재하는 문자가 없습니다.\n");
        return '\0';
    }

    char c = q->front->data; // 큐의 맨 앞 노드의 데이터를 가져옴
    struct node* temp = q->front; // 큐의 맨 앞 노드를 삭제
    q->front = q->front->next;

    free(temp); // 삭제된 노드의 메모리를 해제

    return c; // 큐의 맨 앞 노드의 데이터를 반환
}

//! 큐를 출력하는 함수
void print_queue(struct queue* q) {
    // 큐가 비어있는 경우 오류 메시지 출력
    if (q->front == NULL) {
        printf("큐가 비어있습니다.\n");
        return;
    }

    // 큐의 첫 번째 노드부터 마지막 노드까지 출력
    struct node* current = q->front;
    while (current != NULL) {
        printf("%c ", current->data);
        current = current->next;
    }

    printf("\n");
}

//! 큐의 길이를 구하는 함수
int get_queue_length(struct queue* q) {
    int count = 0;
    struct node* current = q->front;
    struct node* tmp = current;

    // 큐가 비어있는 경우 0을 반환
    if (q->front == NULL) {
        printf("큐가 비어있습니다.\n");
        return 0;
    }

    printf("\n 큐의 맨앞 : ");
    printf("%c", current->data); // 현재 데이터의 값을 출력 (첫번째 노드)

    // 큐의 길이를 계산
    while (current != NULL) {
        count++;
        tmp = current; // 현재 노드를 현재->데이터가 아닌 tmp에 할당합니다.
        current = current->next;

        if (current == NULL) {
            printf("\n 큐의 맨뒤 : ");
            printf("%c", tmp->data); // tmp의 데이터값을 출력합니다 (current를 출력하면 NULL 을 출력하게 됨)
        }
    }

    // 큐의 길이를 반환
    return count;
}

int main() {
    // 빈 큐 생성
    struct queue q;
    q.front = NULL;
    q.rear = NULL;

    // 메뉴 선택
    int choice;
    char c;

    printf("1. Enqueue\n2. Dequeue\n3. Print queue\n4. Get queue length\n");
    for (int i = 0; i < 10; i++) {
        printf("\n-------------\n");
        printf("\n %d 번째 메뉴를 선택하세요 : ", i + 1);
        scanf_s("%d", &choice);

        // 유효한 메뉴를 선택하지 않은 경우 오류 메시지 출력
        while (choice < 1 || choice > 4) {
            printf("\n 입력 에러! 1에서 4 사이의 값을 입력하세요 : ");
            scanf_s("%d", &choice);
            if (islower(c) == 0 || isalpha(c) == 0)
            {
                printf("\n\n ERROR! 메뉴 선택시 문자 입력 금지 \n\n");
                break;
            }
        }

        switch (choice) {
        case 1:
            printf("\n\n1.큐 삽입\n\n");
            printf(">> 문자 입력 : ");
            scanf_s(" %c", &c);

            while (!is_valid_character(c)) {
                printf("\n - 입력 에러! 영어 소문자만 입력하세요 : ");
                scanf_s(" %c", &c);
            }

            enqueue(&q, c);
            break;

        case 2:
            printf("\n\n2.큐 front 삭제\n\n");
            c = dequeue(&q);
            if (c != '\0') {
                printf(">> 큐에서 front에 있는 %c 를 삭제합니다.\n", c);
            }
            break;

        case 3:
            printf("\n\n3.큐 출력\n\n>> ");
            print_queue(&q);
            break;

        case 4:
            printf("\n\n4.큐 요소 출력\n\n");
            printf("\n>> 해당 큐는 %d 개의 요소를 가지고있습니다.\n", get_queue_length(&q));
            break;
        }
        printf("\n-------------\n");
    }

    printf(" >>>> END \n");
    printf("\n================\n");
    print_queue(&q);
    printf("\n================\n");
    return 0;
}