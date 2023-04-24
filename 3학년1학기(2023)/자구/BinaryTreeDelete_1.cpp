#include <stdio.h>
#include <stdlib.h>

struct TreeNode; // 구조체 트리노드
typedef int ElementType; //  이진탐색트리의 노드에 저장되는 데이터의 타입
typedef struct TreeNode* PtrToNode; // 이진탐색트리의 노드를 가르키기 위한 포인터
typedef PtrToNode BinarySearchTree; // 포인터를 이용하여 이진탐색트리를 구현할 때 사용

//! 2진 트리기 때문에 좌측노드는 루트노드보다 작아야하고 우측노드는 루트노드보다 커야함
struct TreeNode {
    ElementType Element; //원소
    BinarySearchTree Left; //왼쪽 자식 노드
    BinarySearchTree Right; // 우측 자식 노드
};

//! 함수 선언부
BinarySearchTree CreateTree(ElementType X); // 트리 생성 X값은 Root가 됩니다
BinarySearchTree Insert(ElementType X, BinarySearchTree T); // 트리T에 요소 X 삽입
PtrToNode Find(ElementType X, BinarySearchTree T); // x가 자리할 수 있는 해당하는 위치 탐색
PtrToNode FindMin(BinarySearchTree T); // 트리 T에서 최소값 탐색
PtrToNode FindMax(BinarySearchTree T); // 트리 T에서 최대값 탐색
BinarySearchTree Delete(ElementType X, BinarySearchTree T); //트리 T에서 요소 X값 삭제

//! 트리 생성
//~ X값은 Root가 됩니다
BinarySearchTree CreateTree(ElementType X) {
    BinarySearchTree T;
    T = (BinarySearchTree)malloc(sizeof(struct TreeNode));
    T->Element = X; // 원소 할당
    T->Left = NULL; // 왼쪽 자식 노드 초기화
    T->Right = NULL; // 오른쪽 자식 노드 초기화

    return T; //요소 X가 Root로 존재하고 좌측과 우측에 각각 NULL을 가진 노드 생성
}

//! 트리 삽입 함수
//~ 트리T에 요소 X 삽입
BinarySearchTree Insert(ElementType X, BinarySearchTree T) {
    
    // 트리가 비어있다면 트리를 생성시킨다
    if (T == NULL) 
    {
        
        return CreateTree(X); //트리 생성
        T = (BinarySearchTree)malloc(sizeof(struct TreeNode));
        T->Element = X;
		T->Left = NULL;
		T->Right = NULL;
    }
    // x보다 트리의 원소가 클 경우 Left로 이동한 후 함수를 실행시킵니다
    else if (X< T->Element) 
        T->Left = Insert(X, T->Left);
    
    // x보가 트리의 원소보다 클 경우 Right로 이동한 후 함수를 실행시킵니다
    else if (X> T->Element) 
        T->Right = Insert(X, T->Right);

    return T; //T 반환
}

//! X에 해당하는 위치를 찾는 함수
//~ x가 자리할 수 있는 해당하는 위치 탐색
PtrToNode Find(ElementType X, BinarySearchTree T) {
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
//~ 트리 T에서 최소값 탐색
PtrToNode FindMin(BinarySearchTree T)
{
    //T가 비어있을경우에는 최소값도 존재할 수 없기에 그냥 코드종료
    if (T == NULL) return;

    //T의 왼쪽값(작은값) 이 이제 없네?
    //-> 그럼 T 반환해
    else if (T->Left == NULL)
        return T;

    //더 작은 값이 있어? 그럼 계속 T의 왼쪽값을 재귀함수에 넣어 최소값 찾아라
    else
        return FindMin(T->Left);
}

//! T에서 최대값을 찾으러감
//~ 트리 T에서 최대값 탐색
PtrToNode FindMax(BinarySearchTree T)
{
    //T가 비어있을경우에는 최대값도 존재할 수 없기에 그냥 코드종료
    if (T == NULL) return;

    //T의 오른쪽값이(큰값) 이 이제 없네?
    //-> 그럼 T 반환해
    else if (T->Right == NULL)
        return T;

    //더 큰 값이 있어? 그럼 계속 T의 오른쪽값을 재귀함수에 넣어 최대값 찾아라
    else
        return FindMax(T->Right);
}

//! 트리 삭제 함수
//~ 트리 T에서 특정값 X를 삭제
//? 아래 if문들이 사실상 필터 역할을 해준다.
BinarySearchTree Delete(ElementType X, BinarySearchTree T)
{
    PtrToNode Tmp; //Tmp는 Tree 노드를 가르킨다

    //* 1. 트리가 비었을 경우
    if (T == NULL) return; //Tree가 비어있기에 아무것도 반환하지 않는다
    
    //X가 T보다 작다!\
    -> 왼쪽 이동
    else if (X < T->Element)
        T->Left = Delete(X, T->Left); 
        //내 왼쪽값을 지울거야, 노드 T를 왼쪽으로 이동한 값과 X값을 함수에 넣어 재귀시켜줘
    
    //X가 T보다 크다!\
    -> 오른쪽 이동
    else if (X > T->Element)
        T->Right = Delete(X, T->Right);
        //내 오른쪽값을 지울거야, 노드 T를 오른쪽으로 이동한 값과 X값을 함수에 넣어 재귀시켜줘
    
    //~-> 여기 if문까지 필터가 걸러지면 요소 X를 찾았다는것
    //* 4. T의 왼쪽, 오른쪽 자식노드가 모두 존재할 경우
    // X의 위치가 도달했을 때, 더이상 다음 노드가 없거나\
    1개 있거나 or 2개 있을때에 대한 처리과정\
    한마디로 서브트리가 있을때 처리과정
    else if (T->Left && T->Right)
    {
        Tmp = FindMin(T->Right); //오른쪽 서브트리의 최소값을 찾아 찾은 값을 Tmp에 저장
        T->Element = Tmp->Element; //T는 서브트리 오른쪽 가장 작은값인 Tmp값으로 업데이트
        T->Right = Delete(T->Element, T->Right); //T의 하위 노드에서 자신과 같은값을 삭제
        //T Element는 결국 최소값이며, 최소값은 이미 복사되었기때문에 중복을 막고자함
    }
    
    //* 2. 노드가 없을경우
    //* 3. 노드가 하나 있을 경우
    else
    {
        Tmp = T;
        if (T->Left == NULL) //왼쪽 자식이 없어?
            T = T->Right; //현재 T에 오른쪽 자식 노드로 대체
        
        else if (T->Right == NULL) //오른쪽 자식이 없어?
            T = T->Left; //현재 T에 왼쪽 자식 노드로 대체
        
        /*이진탐색트리에서는 왼쪽 자식 노드가 부모 노드보다 작은 값을 가지고 있기 때문*/
        
        free(Tmp); //Tmp 메모제를 삭제
    }
    return T;
}

// 메인 함수
int main() {

   // 아직 작성 안함

    return 0;
}