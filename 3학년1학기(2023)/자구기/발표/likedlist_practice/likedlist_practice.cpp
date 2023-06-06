#include <iostream>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* link;
} Node;

Node* getNode() {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->link = NULL;
    return new_node;
}

void insertTicket(Node* L, Node* pre, int x)
{
    Node* new_node = getNode();
    new_node->data = x;

    if (pre == NULL)
    {
        new_node->link = L;
        L = new_node;
    }
    else
    {
        new_node->link = pre->link;
        pre->link = new_node;
    }
}

int main()
{
    // 0부터 9까지의 정수값을 가진 10개의 리스트를 미리 만듭니다.
    Node* head = getNode();
    head->data = 0;
    Node* tail = head;

    for (int i = 1; i < 10; i++) {
        Node* new_node = getNode();
        new_node->data = i;
        tail->link = new_node;
        tail = new_node;
    }

    // 리스트 출력
    Node* curr = head;
    while (curr != NULL) {
        std::cout << curr->data << " ";
        curr = curr->link;
    }

    // 사용자의 입력값을 받아 리스트를 삽입하는 코드입니다.
    int x;
    std::cout << "삽입할 값을 입력하세요: ";
    std::cin >> x;

    insertTicket(head, NULL, x);

    // 리스트 출력
    while (curr != NULL) {
        std::cout << curr->data << " ";
        curr = curr->link;
    }

}