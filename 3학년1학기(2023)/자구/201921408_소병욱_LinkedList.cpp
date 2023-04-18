//미디어기술콘텐츠학과 201921408 소병욱

#define _CRT_SECURE_NO_WARNINGS //보안경고 무시
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;


typedef int ElementID;
typedef int ElementStatus;
struct Node;
typedef struct Node* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef const char* ElementChar;

// ====================================노드 선언===========================================
struct Node {
    ElementChar name;
    ElementID Element;
    ElementStatus Status; // 0 혹은 1
    Position Next;
};

// ====================================함수 선언===========================================
List CreatList(); // 배열 생성
Position Insert(ElementChar name, ElementID X, ElementStatus Status, List L, Position P);  // 노드 삽입
int Delete(ElementID X, List L); // 노드 삭제
Position FindPrevious(ElementID X, List L);
Position Find(ElementID X, List L); // 배열 찾기
void PrintList(List L); // 배열 출력
void PrintNode(List L); // 노드 출력
void StatusCheck(ElementStatus Status, List L); //상태(status) 확인 및 출력
void StatusDelete(ElementStatus Status, List L); //상태(status) 삭제

// ================================Linked List 생성 함수=======================================
List CreatList() {

    List L;
    // malloc : 요청한 크기의 바이트 할당 후 시작 주소 리턴
    L = (List)malloc(sizeof(struct Node)); // Node의 크기만큼 동적 할당

    // . 은 클래스의 멤버를 직접 접근
    // -> 은 포인터를 통해 멤버를 접근
    L->name = ""; // dummy head 생성
    L->Element = 0; // dummy head 생성
    L->Status = NULL;
    L->Next = NULL; // 아무것도 가르키지않는다.

    return L;
}
// ================================ 노드 삽입 함수 =======================================
Position Insert(ElementChar name, ElementID X, ElementStatus Status, List L, Position P) {
    // P -> P2

    Position Tmp; // 삽입할 빈 노드
    Tmp = (Position)malloc(sizeof(struct Node));

    Tmp->Element = X; // 학생 ID
    Tmp->name = name; // 이름
    Tmp->Status = Status; // 0 혹은 1
    Tmp->Next = P->Next; // Tmp -> P2
    P->Next = Tmp; // P -> Tmp

    // P -> Tmp -> P2
    return Tmp;
}

// ============================해당 값의 위치를 찾는 함수===================================
Position FindPrevious(ElementID X, List L) {

    Position P = L;
    // P의 다음 노드가 없고 P의 다음 노드가 원하는 값을 가질 때까지 반복한다
    while (P->Next != NULL && P->Next->Element != X)
        P = P->Next; // 처음부터 탐색

    return P;

}
// ================================ 노드 삭제 함수 =======================================
//(해당 과제에선 StatusDelete를 따로 사용)
int Delete(ElementID X, List L) {

    // P->Tmp->P2
    Position P, Tmp;
    P = FindPrevious(X, L);

    // P->P2로 변경
    Tmp = P->Next;
    P->Next = Tmp->Next;

    free(Tmp);

    // P->P2, Tmp (X)
    return 1;

}

// ================================= 요소 탐색 함수 ========================================
Position Find(ElementID X, List L) {

    Position P = L;
    while (P->Element != X)
        if (P->Next != NULL)
            P = P->Next;

    return P;
}


// ================================= 요소 출력 함수 ========================================
void PrintList(List L) {

    Position P = L;
    // 다음 노드가 없을 때까지 출력 
    while (P->Next != NULL) {
        printf("%d -> ", P->Next->Element); // 처음 값은 dummy head
        P = P->Next;
    }

}

// ================================= 노드 탐색 함수 ========================================
void PrintNode(List L) {

    Position P = L;

    // 다음 노드가 없을 때까지 출력 
    while (P->Next != NULL) {
        printf("\n%s, %d, %d \n ", P->Next->name, P->Next->Element, P->Next->Status); // 처음 값은 dummy head
        P = P->Next;
    }
}

// ================================= 상태 확인 함수 ========================================
void StatusCheck(ElementStatus Status, List L) {
    Position P = L;

    // 다음 노드가 없을 때까지 출력
    while (P->Next != NULL) {
        if (P->Next->Status == Status) {
            printf("\n%d : %d\n ", P->Next->Element, P->Next->Status); // 처음 값은 dummy 
        }
        P = P->Next;
    }
}

// ================================= 요소 삭제 함수 ========================================
/*
현재 노드의 다음 노드가 없을 때까지 반복문을 실행하면서 현재 노드의 상태가 1인 경우에는
이전 노드의 다음 포인터를 현재 노드의 다음 포인터로 바꾸고 현재 노드를 삭제합니다.
상태가 1이 아닌 경우에는 현재 노드와 이전 노드의 포인터를 다음 노드로 이동합니다.

이 코드는 현재 노드를 가리키는 포인터 P와 이전 노드의 다음 포인터를 가리키는 포인터 PP를 사용합니다.
현재 노드의 상태가 1인 경우에는 *PP를 현재 노드의 다음 포인터로 업데이트하고 현재 노드를 삭제합니다.
상태가 1이 아닌 경우에는 P와 PP를 다음 노드로 이동합니다.
*/
void StatusDelete(ElementStatus Status, List L) {
    Position P = L;
    Position* PP = &L;

    while (P != NULL) {
        if (P->Status == Status) {
            *PP = P->Next;
            free(P);
            P = *PP;
        }
        else {
            P = P->Next;
            PP = &(*PP)->Next;
        }
    }
}
// ================================= 메인 함수 ========================================
int main() {

    List L;
    L = CreatList();

    cout << endl;;
    cout << "#### 연결리스트 추가 및 요소 출력 ####" << endl;;
    PrintList(L);
    cout << endl;;
    Insert("Gildong Hong", 123456789, 0, L, L);
    Insert("Gildong Kim", 234567891, 1, L, L);
    Insert("Byunguk So", 201921408, 1, L, L);
    Insert("Gildong Lee", 345678912, 0, L, L);
    Insert("Gildong Park", 456789123, 1, L, L);
    Insert("Gildong Choi", 567891234, 0, L, L);
    PrintList(L);
    printf("\n======================================================\n");
    cout << endl;;
    cout << endl;;
    cout << "#### 노드출력 ####" << endl;;

    PrintNode(L);
    printf("\n======================================================\n");
    cout << endl;;
    cout << endl;;
    cout << "#### 스테이터스 체크 ####" << endl;;
    StatusCheck(1, L); // 스테이터스 출력
    StatusDelete(1, L); // 스테이터스 삭제
    cout << endl;;
    cout << ">>> 1값을 가진 모든 스테이터스 삭제" << endl;;
    cout << ">>> 아래에 아무값도 출력되지 않고 === 구분선이 나온다면 스테이터스 삭제완료" << endl;;
    StatusCheck(1, L); // 스테이터스 출력 재확인
    printf("\n======================================================\n");
    cout << endl;;
    cout << endl;;
    cout << "#### 마지막으로 연결리스트 & 노드출력 ####" << endl;;
    cout << endl;;
    cout << ">리스트 요소" << endl;;
    cout << endl;;
    PrintList(L);
    cout << endl;;
    cout << endl;;
    cout << ">노드 전체 정보" << endl;;
    PrintNode(L);
    return 0;
}