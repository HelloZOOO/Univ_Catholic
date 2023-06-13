#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 100

typedef char element; // char를 걍 element로 부르기로 했습니다.

//* =========== 배열 스택  ===========
element stack[STACK_SIZE]; //Int형 배열 100을 선언 (총 크기 400)
int top = -1; // 첫 상태는 스택에 최상단 값이 없다는 -1 을 넣어줌
//* =================================

//* =========== 함수 구현부 ===========
int isEmpty();
int isFull();
void push(element item); // int item 이 인자로 들어가는 push 함수
element pop(); //어처피 top을 고정적으로 pop하기 때문에 인자는 필요 없음 
element peek(); //어처피 top을 고정적으로 peek하기 때문에 인자는 필요 없음
void printStack();
int main(void);
int testPair(char *exp); // 괄호 확인 코드
element evalPostfix(char *exp); // 후위 표기법 변환 함수
//* =================================

//~1.스택 공백 확인
int isEmpty(){
    if(top == -1) return 1; //스택이 비어있다면 (-1 이라면) 1을 리턴
    else return 0; //그 외는 그냥 리턴
}

//~2.포화 상태 확인
int isFull(){
    if(top == STACK_SIZE - 1) return 1; // 스택의 최상단값이 스택 최대 사이즈와 동일합니까? (0부터 시작하기에 -1)
    else return 0; // 꽉찬거 아니면 그냥 리턴
}

//~3.스택 삽입 함수 구현
void push(element item){
    if (isFull()){
        printf("꽉찼다");
        return; // stack이 이미 꽉찬상태
    } 
    stack[++top] = item; // 꽉 안찼으면 한개의 top이 증가한 배열 값에 item 값 넣기
    //!top을 먼저 증가시킨 후 (전위 연산) 현재 top에 원소 삽입
}

//~4.pop 구현
element pop(){
    if (isEmpty()){
        printf("비었다");
        return 0; // 0은 왜 반환함? 함수 선언할때 pop
    }
    return stack[top--]; //먼저 현재 위치한 top값 부터 삭제하고 후위연산으로 Top 감소
    //! 현재 top의 원소를 삭제한 후에 top 감소 (후위 연산)
}

//~5. peek 구현 (Top 출력)
element peek(){
    if(isFull()){
        printf("꽉찼다");
        exit(1); //exit() 쓸때 0은 정상 종료 1은 비정상 종료라는데?
        /*
        return 0;을 사용하는 대신 exit(1)을 사용하는 이유는 exit(1)이 프로그램의 실행을 즉시 종료하기 때문입니다. 
        return 0;은 함수의 종료를 나타내는 반환 값이지만, 프로그램의 실행을 종료하지는 않습니다. 
        따라서 스택이 가득 찼을 때 peek 함수는 프로그램의 실행을 즉시 종료하기 위해 exit(1)을 사용합니다.
        */
    }
    return stack[top];
}

//~6. 스택 출력
void printStack() {
	printf("\n STACK [");
	for (int i = 0; i <= top; i++) {
	    printf("%d", stack[i]);
	}
	printf("] ");
}

//~7. 수식 괄호 검사하는 연산
int testPair(char *exp) {
    char symbol,open_pair; 
    int i,length = strlen(exp);
    top = NULL; //top은 비워둠
    // char형 포인터 매개변수로받은 수식 exp의 길이를 계산하여 lengt에 저장
    // i 에도 저장해서 for문 돌릴때 이용

    for (i = 0; i < length; i++) {
        symbol = exp[i];
        switch (symbol)
        {
        // * 1. 왼쪽 괄호는 스택에 삽입
        case '(':
        case '[':
        case '{':
            push(symbol); break;
        // * 2-0. if 오른쪽 괄호를 만나면
        case ')':
        case ']':
        case '}':
            if(top == NULL) return 0; // top가 NULL이면 스택이 비어있는거라 코드 종료
            else{
                open_pair = pop(); // * 2-1 스택에서 마지막으로 읽은 괄호 pop
                
                // * 2-2 괄호 쌍이맞는지 검사
                // 만약 pop된 괄호가 닫는 괄호가 아니라 여는괄호일떄 코드가종료
                if
                (
                    (open_pair == '(' && symbol != ')') ||
                    (open_pair == '[' && symbol != ']') ||
                    (open_pair == '{' && symbol != '}')
                )
                return 0; // 2-2 코드 종료
            
            // * 2-3 닫는괄호가 들어와 쌍이맞는다면 다음 symbol 검사를 계속함
            else break;
            }
            //수식검사 종료후 스택이 비어있으면 1을반환
            if (top == NULL) return 1;
            else return 0; // 공백이 아니면 0반환
            
        }
    }
}

//~8. 후위 표기법 변환 함수
element evalPostfix(char *exp){
    int opr1,opr2,value,i = 0;

    //char 형 포인터 매개변수로 받은 수식 exp의 길이를계싼하여 length변수에 저장
    int length = strlen(exp);
    char symbol;
    top = NULL;

    for (i = 0; i < length; i++)
    {
        symbol = exp[i];
        //! i번째 배열의 값이 기호라면?
        if 
        ((symbol != '+' && symbol!= '-' && 
        symbol!= '*' && symbol!= '/'))
        {
            value = symbol - '0';
            push(value);
        }
        //! i번째 배열의 값이 정수라면?
        else
        {
            opr2 = pop();
            opr1 = pop();                        
            switch (symbol)
            {
            case '+':
                value = opr1 + opr2;
                push(value);
                break;
            case '-':
                value = opr1 - opr2;
                push(value);
                break;
            case '*':
                value = opr1 * opr2;
                push(value);
                break;
            case '/':
                value = opr1 / opr2;
                push(value);
                break;
            }
        }
    }

    return pop();
};


int main(void) {
    int result;
	char *express = "35*62/-";
	printf("후위 표기식 : %s", express);
	
	result = evalPostfix(express);
	printf("\n\n연산 결과 => %d\n", result);
}
