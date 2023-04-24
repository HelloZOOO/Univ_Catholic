#include <stdio.h>
#include <stdlib.h>

struct TreeNode;
typedef int ElementType;
typedef struct TreeNode *PtrToNode;
typedef PtrToNode BinarySearchTree;

struct TreeNode{
	ElementType Element;
	BinarySearchTree Left;
	BinarySearchTree Right;
};

BinarySearchTree CreateTree(ElementType X);
BinarySearchTree Insert(ElementType X, BinarySearchTree T);
PtrToNode Find(ElementType X, BinarySearchTree T);
PtrToNode FindMin(BinarySearchTree T);
PtrToNode FindMax(BinarySearchTree T);
BinarySearchTree Delete(ElementType X, BinarySearchTree T);

BinarySearchTree CreateTree(ElementType X){
	BinarySearchTree T;
	T = (BinarySearchTree)malloc(sizeof(struct TreeNode));
	T->Element = X;
	T->Left = NULL;
	T->Right = NULL;
	
	return T;
}

BinarySearchTree Insert(ElementType X, BinarySearchTree T){
	if(T==NULL){
		T = (BinarySearchTree)malloc(sizeof(struct TreeNode));
		T->Element = X;
		T->Left = NULL;
		T->Right = NULL;
	}
	else if(X < T->Element){
		T->Left = Insert(X, T->Left);
	}
	else if(X > T->Element){
		T->Right = Insert(X, T->Right);
	}
	return T;
}

PtrToNode Find(ElementType X, BinarySearchTree T){
	if(T==NULL) return;
	else if(X < T->Element){
		return Find(X, T->Left);
	}
	else if(X > T->Element){
		return Find(X, T->Right);
	}
	else{
		return T;
	}
}

PtrToNode FindMin(BinarySearchTree T){
	if(T==NULL) return;
	else if(T->Left == NULL){
		return T;
	}
	else{
		return FindMin(T->Left);
	}
}

PtrToNode FindMax(BinarySearchTree T){
	if(T==NULL) return;
	else if(T->Right == NULL){
		return T;
	}
	else{
		return FindMax(T->Right);
	}
}

BinarySearchTree Delete(ElementType X, BinarySearchTree T){
	PtrToNode Tmp;
	if(T==NULL) return;
	else if(X<T->Element){
		T->Left = Delete(X, T->Left);
	}
	else if(X>T->Element){
		T->Right = Delete(X, T->Right)
	}
	else if(T->Left && T->Right){
		Tmp = FindMin(T->Right);
		T->Element = Tmp->Element;
		T->Right = Delete(T->Element, T->Right);
	} else{
		Tmp = T;
		if(T->Left==NULL){
			T = T->Right;
		}
		else if(T->Right==NULL){
			T = T->Left;
		}
		free(Tmp);
	}
	return T;
}


int main(){
	
	
	return 0;
}
