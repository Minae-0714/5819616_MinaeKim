/*#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int data; //노드에 저장할 수 있는 값
	struct TreeNode* left, * right; //트리의 왼쪽, 오른쪽을 가르키는 포인터
}TreeNode;

//재귀적인방법
void Pre_Order_By_Pointer(TreeNode* np);
void In_Order_By_Pointer(TreeNode* np);
void Post_Order_By_Pointer(TreeNode* np);

//우선 배열을 사용하는 방법 Tree in Array
void main() {
	int Tree[8] = { -1, 10, 5, 9, 6, 3, -1, 7 }; //트리 표현
	TreeNode n1, n2, n3, n4, n5, n6;
	n1.data = 10, n1.left = &n2, n1.right = &n3;
	n2.data = 5, n2.left = &n4, n2.right = &n5;
	n3.data = 9, n3.left = NULL, n3.right = &n6;
	n4.data = 6, n4.left = NULL, n4.right = NULL;
	n5.data = 3, n5.left = NULL, n5.right = NULL;
	n6.data = 7, n6.left = NULL, n6.right = NULL;

	printf("전위순회 : ");
	Pre_Order_By_Pointer(&n1);
	printf("\n중위순회 : ");
	In_Order_By_Pointer(&n1);
	printf("\n후위순회 : ");
	Post_Order_By_Pointer(&n1);
}

void Pre_Order_By_Pointer(TreeNode* np) { //전위순회
	if (np != NULL) { //노드포인터가 NULL이 아니면 출력
		printf("[%2d]", np->data);
		Pre_Order_By_Pointer(np->left);
		Pre_Order_By_Pointer(np->right);
	}
}

void In_Order_By_Pointer(TreeNode* np) { //중위순회
	if (np != NULL) { //노드포인터가 NULL이 아니면 출력
		In_Order_By_Pointer(np->left);
		printf("[%2d]", np->data);
		In_Order_By_Pointer(np->right); //왼쪽 프린트하고 오른쪽 프린트 
	}
}

void Post_Order_By_Pointer(TreeNode* np) { //후위순회
	if (np != NULL) { //노드포인터가 NULL이 아니면 출력
		Post_Order_By_Pointer(np->left);
		Post_Order_By_Pointer(np->right);
		printf("[%2d]", np->data);
	}
}

/*void Pre_Order_By_Pointer(int index) { //배열로 나타내는 방법?
	if (Tree[index] != -1) { //Tree 전역변수로 바꾸고
		printf("[%2d]", Tree[index]);
		Pre_Order_By_Pointer(index*2); //왼쪽은 *2
		Pre_Order_By_Pointer(index*2+1); //오른쪽은 *2+1 (트리 그림 참고)
	}
}*/