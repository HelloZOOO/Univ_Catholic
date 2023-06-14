//이진트리 탐색 구현

#include<stdio.h>
#include<stdlib.h>

typedef char element; // char는 곧 element
typedef struct treeNode{
    char key;
    treeNode* left;
    treeNode* right;
}treeNode;

//!키값 x를 찾는 연산
treeNode* searchBST(treeNode* root, char x){
    treeNode* p;
    p = root; //~ *root의 *p니까 사실상 **root 이중 포인터다
    while(p!= NULL){ //현재 위치한 루트가 빌때까지 반복
        if(x < p->key) p = p->left; //*탐색값이 기존 값보다 작으면 좌측으로이동
        else if(x == p->key) return p; //*찾던값이면 p 반환
        else p = p->right; //*좌측에서 하나도 못찾으면 우측으로 이동
    }
    printf("Not Found\n"); //찾았으면 위 while문에서 return되었음
    return p;
}

//!현재 포인터가 위치한 노드값과 비교하여 노드 x를 삽입하는연산
treeNode* insertNode(treeNode* p, char x){
    treeNode* newNode;

    //~포인터가 가르키는 위치가 비어있다면? (말단 or 빈 트리라면)
    if(p==NULL){
        newNode = (treeNode*)malloc(sizeof(treeNode));
        newNode->key = x;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    //~비어있는 트리가 아니라면 재귀함수를 통해 비교연산
    else if(x < p->key) p->left = insertNode(p->left, x);
    else if(x > p->key) p->right = insertNode(p->right, x);
    else printf("이미 같은 키가 존재합니다\n");

    return p;
}

//! 노드 삭제하는 연산
void deleteNode(treeNode* root, element key){
    treeNode* parent,*p, *succ, *succ_parent;
    treeNode* child;

    parent = NULL;
    p = root;
    //~삭제할노드의 위치 탐색
    while((p!=NULL)&&(p->key!=key)){
        parent = p;
        if(key < p->key) p = p->left;
        else p = p->right;
    }

    //~삭제할 노드가 없으면
    if(p==NULL){
        printf("Not Found\n");
        return;
    }

    //~삭제 노드가 리프 노드인 경우
    //*현위치에서 p는 좌 우 가 둘다 비어있네?
    if(p->left == NULL && p->right == NULL){ 
        //* 너 부모 없지? 부모가 있으면 너가 루트노드인거잖아.
        if(parent != NULL){ 
            //*부모의 좌/우측이 p너야? 그럼 부모의 좌/우측을 지워.한마디로 널 죽인다는거지
            if(parent->left == p) parent->left = NULL; 
            else parent->right = NULL;
        }
        else root = NULL;
    }

    //~삭제할노드가 자식노드를 한 개 가진 경우
    //*현위치 p에서 좌측이나 우측노드가 비어있을때
    else if((p->left == NULL)||(p->right == NULL)){
        //* 뭐야 좌/우측에 자식놈 숨겨뒀네? child에 저장해둬
        if(p->left != NULL) child = p->left;
        else child = p->right;

        //* p 네놈이 루트노드인지 확인(부모가 NULL이면 루트노드임)
        if (parent!= NULL) {
            //*좌/우측자식놈이 이제 p를 대체한다. p 넌 죽어도 그 의지를 자식들이 이어가게 될거야
            if(parent->left == p) parent->left = child;
            else parent->right = child;
        }
        //* 부모가 삭제된거면 자식이 루트가 된거지 (총 노드가 2개라 가능 부모1 자식1)
        else root = child; 
    }

    //~삭제할노드가자식 노드를 두개 가진 경우
    else{
        succ_parent = p;
        succ = p->left;

        //*왼쪽서브 트리에서 후계자 탐색
        //*왼쪽서브 트리에서 가장 큰 후계자가 루트로 상속 하기 위해 오른쪽으로 쭉 이동
        
        //* 우측 있지? (너 우측 말단노드 아니지?)
        while(succ->right!= NULL){
            succ_parent = succ; //* 부모는 자식이 됨
            succ = succ->right; //* 자식은 자신의 우측으로 이동함
        }
        
        //* 후계자가 삭제할 노드의 왼쪽 자식인 경우 후계자의 왼쪽 자식을 삭제할 노드의 왼쪽 자식으로 대체
        if(succ_parent->left == succ) succ_parent->left = succ->left;
        //* 후계자가 삭제할 노드의 오른쪽 자식인 경우 후계자의 왼쪽 자식을 삭제할 노드의 오른쪽 자식으로 대체
        else succ_parent->right = succ->left;
        p->key = succ->key;//* 후계자의 값을 삭제할 노드에 대입
        p = succ;//* p를 후계자로 대체합니다.
    }
    free(p); // * 대의를 위해 죽어라 "p"
}

//!트리를 중위 순회하며 출력하는 연산 LDR
void displayInorder(treeNode* root){
    if(root){
        displayInorder(root->left);
        printf("%c ", root->key);
        displayInorder(root->right);
    }
}


void menu() {
printf("\n*---------------------------*");
printf("\n\t1 : 트리 출력");
printf("\n\t2 : 문자 삽입");
printf("\n\t3 : 문자 삭제");
printf("\n\t4 : 문자 검색");
printf("\n\t5 : 종료");
printf("\n*---------------------------*");
printf("\n메뉴입력 >> ");
}

int main() {
treeNode* root = NULL;
treeNode* foundedNode = NULL;
char choice, key;

// [그림 7-38]과 같은 초기 이진 탐색 트리를 구성하고 
// 노드 G를 루트 노드 포인터 root로 지정
root = insertNode(root, 'G');
insertNode(root, 'I'); insertNode(root, 'H');
insertNode(root, 'D'); insertNode(root, 'B');
insertNode(root, 'M'); insertNode(root, 'N');
insertNode(root, 'A'); insertNode(root, 'J');
insertNode(root, 'E'); insertNode(root, 'Q');


while (1) {
menu();
scanf(" %c", &choice);

switch (choice - '0') {
case 1:printf("\t[이진 트리 출력]  ");
displayInorder(root);  printf("\n");
break;

case 2:printf("삽입할 문자를 입력하세요 : ");
scanf(" %c", &key);
insertNode(root, key);
break;

case 3:printf("삭제할 문자를 입력하세요 : ");
scanf(" %c", &key);
deleteNode(root, key);
break;

case 4: printf("찾을 문자를 입력하세요 : ");
scanf(" %c", &key);
foundedNode = searchBST(root, key);
if (foundedNode != NULL)
printf("\n %c를 찾았습니다! \n", foundedNode->key);
else  printf("\n 문자를 찾지 못했습니다. \n");
break;

case 5: return 0;

default: printf("없는 메뉴입니다. 메뉴를 다시 선택하세요! \n");
break;
}
}
}