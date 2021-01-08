#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>


struct _node;
typedef struct _node* Position;
typedef struct _node {
	int coef;
	Position left;
	Position right;
}Node;


Position createNode(int);
Position insertNode(Position, int);

Position deleteTree(Position);


Position findNode(Position, int);
Position findMin(Position);

Position deleteNode(Position, int);
Position RealDeleteNode(Position);

void printList(Position);
void printNode(Position);


int main(void) {
	Position root = NULL;
	Position temp = NULL;

	root = insertNode(root, 4);

	root = insertNode(root, 2);
	root = insertNode(root, 15);

	root = insertNode(root, 1);
	root = insertNode(root, 3);
	root = insertNode(root, 10);
	root = insertNode(root, 20);

	root = insertNode(root, 6);
	root = insertNode(root, 11);

	root = insertNode(root, 7);

	root = insertNode(root, 8);

	root = insertNode(root, 9);

	printList(root);
	temp = findNode(root, 10);

	root = deleteNode(root,10);


	printList(root);
	temp = findNode(root, 10);

	deleteTree(root);

	system("pause");
	return EXIT_SUCCESS;
}

Position deleteTree(Position root) {
	if (root != NULL){
		root->left  = deleteTree(root->left);
		root->right = deleteTree(root->right);
		free(root);
	}
	return NULL;
}


Position insertNode(Position root, int coef) {

	if (root == NULL) {
		return createNode(coef);
	}

	if (root->coef > coef) {
		root->left = insertNode(root->left, coef);
	}
	else if (root->coef < coef) {
		root->right = insertNode(root->right, coef);
	}

	return root;
}

Position createNode(int k) {

	Position el = NULL;
	el = (Position)malloc(sizeof(Node));

	if (NULL == el) {
		printf("Memory allocation failed!\r\n");
		return NULL;
	}
	el->coef = k;
	el->left = NULL;
	el->right = NULL;

	return el;
}

void printList(Position head) {
	if (head == NULL) {
		puts("");
		return;
	}
	printList(head->left);
	printNode(head);
	printList(head->right);
}

void printNode(Position head) {
	if (head == NULL) {
		puts("");
		return;
	}
	printf("\t%d", head->coef);
}

Position findNode(Position root, int coef) {

	if (root == NULL) {
		printf("\nElement %d nije pronadjen.\n", coef);
		return NULL;
	}

	if (root->coef > coef) {
		return findNode(root->left, coef);
	}
	else if (root->coef < coef) {
		return findNode(root->right, coef);
	}
	else {
		printf("\nElement je pronadjen \nvrijednost: %d adresa:\t%p\n", root->coef, root);
		return root;
	}

}

Position deleteNode(Position root, int coef) {

	if (root == NULL) {
		printf("\nElement %d nije pronadjen.\n", coef);
		return NULL;
	}

	if (root->coef > coef) {
		root->left= deleteNode(root->left, coef);
	}
	else if (root->coef < coef) {
		root->right= deleteNode(root->right, coef);
	}
	else {
		
		root = RealDeleteNode(root);
	}
	return root;
}

Position RealDeleteNode(Position node) {

	Position temp = NULL;

	if (node->left == NULL && node->right == NULL) {
		free(node);
		node = NULL;
	}
	else if (node->left == NULL) {
		temp = node->right;
		node->coef = temp->coef;
		node->right = temp->right;
		free(temp);
		temp = NULL;
	}
	else if (node->right == NULL) {
		temp = node->left;
		node->coef = temp->coef;
		node->left = temp->left;
		free(temp);
		temp = NULL;
	}
	else if (node->left != NULL && node->right != NULL) {

		temp = findMin(node->left);
		node->coef = temp->coef;
		node->left = deleteNode(node->left, temp->coef);

	}

	return node;
}



Position findMin(Position root) {

	if (root->right == NULL)
		return root;


	return findMin(root->right);

}


