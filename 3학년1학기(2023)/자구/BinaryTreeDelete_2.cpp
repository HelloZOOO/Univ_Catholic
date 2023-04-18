#define _CRT_SECURE_NO_WARNINGS
#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>
#include <string.h>
#include <algorithm>
#include <stdbool.h>
#include <stdlib.h>
#include <stack>
#include <queue>
#include <vector>
#include <utility>
#include <functional>
#include <map>
#include <stdio.h>
#include <unordered_set>
#include <set>
using namespace std;

struct TreeNode;
typedef int ElementType;
typedef struct TreeNode *PtrToNode;
typedef PtrToNode BinarySearchTree;

struct TreeNode {
   ElementType Element; // 원소
   BinarySearchTree Left; // 왼쪽 자식 노드
   BinarySearchTree Right; // 오른쪽 자식 노드
};

// 함수 선언
BinarySearchTree CreateTree(ElementType X); // 트리 생성
BinarySearchTree Insert(ElementType X, BinarySearchTree T); // 트리 삽입
PtrToNode Find(ElementType X, BinarySearchTree T); // X에 해당하는 위치 찾기
PtrToNode FindMin(BinarySearchTree T); // 최솟값 찾기
PtrToNode FindMax(BinarySearchTree T); // 최댓값 찾기
BinarySearchTree Delete(ElementType X, BinarySearchTree T); // 트리 삭제


// 트리 생성 함수
BinarySearchTree CreateTree(ElementType X) {

    BinarySearchTree T;
   T = (BinarySearchTree)malloc(sizeof(struct TreeNode)); // 메모리 할당
   T->Element = X; // 원소 할당
   T->Left = NULL; // 왼쪽 자식 노드 초기화
   T->Right = NULL; // 오른쪽 자식 노드 초기화

    return T;

}


// 트리 삽입 함수
BinarySearchTree Insert(ElementType X, BinarySearchTree T) {

   // 트리가 비어있다면 -> 트리 생성
    if (T == NULL) {
        return CreateTree(X);
    }
    // X < 트리의 원소 -> Left로 이동 후 함수 실행
    else if (X < T->Element) {
        T->Left = Insert(X, T->Left);
    }
    // X > 트리의 원소 -> Right로 이동 후 함수 실행
    else if (X > T->Element) {
        T->Right = Insert(X, T->Right);
    }

    return T;

}


// X에 해당하는 위치 찾기 함수
PtrToNode Find(ElementType X, BinarySearchTree T) {

   // 트리가 비어있다면 NULL
    if (T == NULL) 
        return;
    // X < T의 원소 -> Left로 이동
    else if (X < T->Element) 
        return Find(X, T->Left);
    // X > T의 원소 -> Right로 이동
    else if (X > T->Element) 
        return Find(X, T->Right);
    // X == T의 원소 -> T 반환
    else 
        return T;

}

// 최솟값 찾기 함수
PtrToNode FindMin(BinarySearchTree T) {

    if (T == NULL) 
        return;
    else if (T->Left == NULL) 
        return T;
    else 
        return FindMin(T->Left);
    }

// 최댓값 찾기 함수
PtrToNode FindMax(BinarySearchTree T) {

    if (T == NULL) 
        return;
    else if (T->Right == NULL) 
        return T;
    else 
        return FindMax(T->Right);

    }


// 트리 삭제 함수
BinarySearchTree Delete(ElementType X, BinarySearchTree T) {

    PtrToNode Tmp;
    // 1. 트리가 비어있을 경우
    if (T == NULL)
        return;

    // X의 위치로 이동하는 과정
    // X < T의 원소 -> 왼쪽 노드로 이동 후 함수 실행
    else if (X < T->Element)
        T->Left = Delete(X, T->Left);
    // X > T의 원소 -> 오른쪽 노드로 이동 후 함수 실행
    else if (X > T->Element)
        T->Right = Delete(X, T->Right);

    // X의 위치가 도달했을 때, 노드가 없거나 / 1개 있거나 / 2개 있거나 에 대한 처리과정
    // 4. T의 왼쪽, 오른쪽 자식노드가 모두 존재할 경우
    else if (T->Left && T->Right) {
        Tmp = FindMin(T->Right); // 오른쪽 서브트리의 최솟값 찾기
        T->Element = Tmp->Element; // T의 원소 = Tmp의 원소 업데이트
        T->Right = Delete(T->Element, T->Right); // T의 오른쪽 자식노드에서 다시 Delete함수 실행
    }
    // 2. 노드가 없을 경우
    // 3. 노드가 하나 있을 경우
    else {
        Tmp = T;
        // 왼쪽 자식노드가 없을 경우
        if (T->Left == NULL)
            T = T->Right; // T = T의 오른쪽 자식노드 업데이트
        // 오른쪽 자식노드가 없을 경우
        else if (T->Right == NULL)
            T = T->Left; // T = T의 왼쪽 자식노드 업데이트
        free(Tmp); // Tmp 메모리 삭제
    }
    return T;
}


// 메인 함수
int main() {

   // 아직 작성 안함

    return 0;
}