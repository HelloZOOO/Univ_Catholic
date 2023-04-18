#include <stdio.h>
#include <stdlib.h>

struct TreeNode;
typedef int ElementType;
typedef struct TreeNode* ptrToNode;
typedef ptrToNode BinarySearchTree;

//! 2진 트리기 때문에 좌측노드는 루트노드보다 작아야하고 우측노드는 루트노드보다 커야함
struct TreeNode {
    ElementType Element; //원소
    BinarySearchTree Left; //왼쪽 자식 노드
    BinarySearchTree Right; // 우측 자식 노드
};

//! 함수 선언부
BinarySearchTree CreateTree(ElementType X);
BinarySearchTree Insert(ElementType X, BinarySearchTree T);
ptrToNode Find(ElementType X, BinarySearchTree T);
ptrToNode FindMin(BinarySearchTree T);
ptrToNode FinMax(BinarySearchTree T);
BinarySearchTree Delete(ElementType X, BinarySearchTree T);

//! 트리 생성
BinarySearchTree CreateTree(ElementType X) {
    BinarySearchTree T;
    T = (BinarySearchTree)malloc(sizeof(struct TreeNode));
    T->Element = X; // 원소 할당
    T->Left = NULL; // 왼쪽 자식 노드 초기화
    T->Right = NULL; // 오른쪽 자식 노드 초기화

    return T;
}

//! 트리 삽입 함수
BinarySearchTree Insert(ElementType X, BinarySearchTree T) {
    
    // 트리가 비어있다면 트리를 생성시킨다
    if (T == NULL) 
        return CreateTree(X);
    
    // x보다 트리의 원소가 클 경우 Left로 이동한 후 함수를 실행시킵니다
    else if (X< T->Element) 
        T->Left = Insert(X, T->Left);
    
    // x보가 트리의 원소보다 클 경우 Right로 이동한 후 함수를 실행시킵니다
    else if (X> T->Element) 
        T->Right = Insert(X, T->Right);

    return T; //T 반환
}

//! X에 해당하는 위치를 찾는 함수
ptrToNode Find(ElementType X, BinarySearchTree T) {
    // 트리가 비어있다면 그냥 코드종료
    if (T == NULL) 
        return;
    
    // (X < T) X가 T의 원소보다 작다면 X를 Left로 이동
    else if (X < T->Element) 
        return Find(X, T->Left);
    
    // (X > T) X가 T의 원소보다 크다면 X를 Right로 이동
    else if (X > T->Element) 
        return Find(X, T->Right);
    
    // (X == T) 라면 원소 T를 그냥 반환
    else 
        return T;
}

//! T에서 최소값을 찾으러감
ptrToNode FindMin(BinarySearchTree T)
{
    //T가 비어있을경우에는 최소값도 없기에 그냥 코드종료
    if (T == NULL) return;

    //T의 왼쪽값(작은값) 이 이제 없네?
    //-> 그럼 T 반환해
    else if (T->Left == NULL)
        return T;

    //아니면 계속 T의 왼쪽값으로 재귀함수로 이동해서 최소값 찾아라
    else
        return FindMin(T->Left);
}

ptrToNode FindMax(BinarySearchTree T)
{
    if (T == NULL) return;
    else if (T->Right == NULL)
    {
        return T;
    }
    else
    {
        return FindMax(T->Right);
    }
}

BinarySearchTree Delete(ElementType X, BinarySearchTree T)
{
    ptrToNode Tmp;
    if (T == NULL) return; //Tree가 비어있기에 아무것도 반환하지 않는다
    else if (X < T->Element)
    {
        T->Left = Delete(X, T->Left);
    }
    else if (X > T->Element)
    {
        T->Right = Delete(X, T->Right);
    }
    else if (T->Left && T->Right)
    {
        Tmp = FindMin(T->Right); //오른쪽 서브트리의 최소값을 찾아 찾은 값을 Tmp에 저장
        T->Element = Tmp->Element; //Tmp를 엘리먼트로 업데이트해주고
        T->Right = Delete(T->Element, T->Right); //T의 오른쪽을
    }
    else
    {
        Tmp = T;
        if (T->Left == NULL)
        {
            T = T->Right;
        }
        else if (T->Right == NULL)
        {
            T = T->Left;
        }
        free(Tmp); //Tmp 메모제를 삭제
    }
    return T;
}