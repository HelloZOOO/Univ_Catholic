//이진트리의 순회 실습

#include <stdio.h>
#include <stdlib.h>

//! 구조체 트리노드는 data와 또다른 구조체 트리노드를 가르킨다
typedef struct treeNode {
    char data;
    struct treeNode *left;
    struct treeNode *right;
} treeNode;

//! 인수data를 루트 노드로 하여 왼쪽서브 트리와 오른쪽 서브 트리를 연결하는 연산
treeNode *makeRootNode(char data, treeNode *leftNode, treeNode *rightNode) {
    treeNode *root = (treeNode *)malloc(sizeof(treeNode));
    root->data = data;
    root->left = leftNode;
    root->right = rightNode;
    return root;
}

//! 전위 순회 DLR
void preOrder(treeNode *root) {
    //~현재 루트라면
    if(root) {
        printf("%c ", root->data); //~현재 root를 출력
        preOrder(root->left); //~좌측 노드의 root를 출력
        preOrder(root->right); //~우측 노드의 root를 출력
    }
    //~아니면 재귀함수를 빠져나감
}

//! 중위 순회 LDR
void inOrder(treeNode *root) {
    if(root) {
        inOrder(root->left); //~일단 트리의 가장 좌측까지 이동
        printf("%c ", root->data); //~현재 root를 출력
        inOrder(root->right); //~우측 노드의 우측으로 이동
    }
}

//! 후위 순회 LRD
void postOrder(treeNode *root) {
    if(root) {
        postOrder(root->left); //~좌측 끝으로 이동
        postOrder(root->right); //~우측 끝으로 이동
        printf("%c ", root->data); //~현재 root를 출력
    }
}

int main() {
    // * 리프 노드라 좌 우 둘 다 NULL
    treeNode *n7 = makeRootNode('D', NULL, NULL);
    treeNode *n6 = makeRootNode('C', NULL, NULL);
    treeNode *n5 = makeRootNode('B', NULL, NULL);
    treeNode *n4 = makeRootNode('A', NULL, NULL);

    // * 부모 노드라 좌 우 값을 가지고있음
    treeNode *n3 = makeRootNode('/', n6, n7);
    treeNode *n2 = makeRootNode('*', n4, n5);
    treeNode *n1 = makeRootNode('-', n2, n3);

    printf("\npreOrder : ");
    preOrder(n1);

    printf("\ninOrder : ");
    inOrder(n1);

    printf("\npostOrder : ");
    postOrder(n1);

    printf("\n *n1 :  %d",*n1);
    printf("\n n1 :  %d",n1);

    return 0;
}