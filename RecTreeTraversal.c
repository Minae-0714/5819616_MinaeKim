/*#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int data; //��忡 ������ �� �ִ� ��
	struct TreeNode* left, * right; //Ʈ���� ����, �������� ����Ű�� ������
}TreeNode;

//������ι��
void Pre_Order_By_Pointer(TreeNode* np);
void In_Order_By_Pointer(TreeNode* np);
void Post_Order_By_Pointer(TreeNode* np);

//�켱 �迭�� ����ϴ� ��� Tree in Array
void main() {
	int Tree[8] = { -1, 10, 5, 9, 6, 3, -1, 7 }; //Ʈ�� ǥ��
	TreeNode n1, n2, n3, n4, n5, n6;
	n1.data = 10, n1.left = &n2, n1.right = &n3;
	n2.data = 5, n2.left = &n4, n2.right = &n5;
	n3.data = 9, n3.left = NULL, n3.right = &n6;
	n4.data = 6, n4.left = NULL, n4.right = NULL;
	n5.data = 3, n5.left = NULL, n5.right = NULL;
	n6.data = 7, n6.left = NULL, n6.right = NULL;

	printf("������ȸ : ");
	Pre_Order_By_Pointer(&n1);
	printf("\n������ȸ : ");
	In_Order_By_Pointer(&n1);
	printf("\n������ȸ : ");
	Post_Order_By_Pointer(&n1);
}

void Pre_Order_By_Pointer(TreeNode* np) { //������ȸ
	if (np != NULL) { //��������Ͱ� NULL�� �ƴϸ� ���
		printf("[%2d]", np->data);
		Pre_Order_By_Pointer(np->left);
		Pre_Order_By_Pointer(np->right);
	}
}

void In_Order_By_Pointer(TreeNode* np) { //������ȸ
	if (np != NULL) { //��������Ͱ� NULL�� �ƴϸ� ���
		In_Order_By_Pointer(np->left);
		printf("[%2d]", np->data);
		In_Order_By_Pointer(np->right); //���� ����Ʈ�ϰ� ������ ����Ʈ 
	}
}

void Post_Order_By_Pointer(TreeNode* np) { //������ȸ
	if (np != NULL) { //��������Ͱ� NULL�� �ƴϸ� ���
		Post_Order_By_Pointer(np->left);
		Post_Order_By_Pointer(np->right);
		printf("[%2d]", np->data);
	}
}

/*void Pre_Order_By_Pointer(int index) { //�迭�� ��Ÿ���� ���?
	if (Tree[index] != -1) { //Tree ���������� �ٲٰ�
		printf("[%2d]", Tree[index]);
		Pre_Order_By_Pointer(index*2); //������ *2
		Pre_Order_By_Pointer(index*2+1); //�������� *2+1 (Ʈ�� �׸� ����)
	}
}*/