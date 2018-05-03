#include <stdio.h>
#include <stdlib.h>

typedef struct avlNode avlNode;
struct avlNode {
	int key;
	avlNode *left, *right;
};

avlNode* newNode(int key) {
	avlNode *x = malloc(sizeof(avlNode));
	if (x != NULL) {
		x->key = key;
		x->left = NULL;
		x->right = NULL;
	}
	return x;
}
void rotateRight(avlNode **t) {
  avlNode *aux = (*t)->left;
  (*t)->left = aux->right;
  aux->right = *t;
  *t = aux;
}
void rotateLeft(avlNode **t) {
  avlNode *aux = (*t)->right;
  (*t)->right = aux->left;
  aux->left = *t;
  *t = aux;
}
int insertNode(avlNode **t, int key) {
	int r = 1;
	if (*t == NULL) {
		*t = newNode(key);
	}
	else if ((*t)->key < key) {
		r *= insertNode(&(*t)->right, key);
	}
	else if ((*t)->key > key) {
		r *= insertNode(&(*t)->left, key);
	}
	return r;
}
int searchNode(avlNode *t, int key) {
	int x = 0;
	if (t != NULL) {
		if (t->key < key) {
			x = searchNode(t->right, key);
		}
		else if (t->key > key) {
			x = searchNode(t->left, key);
		}
		else {
			x = 1;
		}
	}
	return x;
}
void makeRoot(avlNode **t, int key) {
	int b = searchNode(*t, key);
	if (!b) {
		insertNode(t, key);
	}
	while ((*t)->key != key) {
		(*t)->key > key ? rotateRight(t) : rotateLeft(t);
	}
}
void printTree(avlNode *t) {
	if (t == NULL) return;
	printTree(t->left);
	printf("%d ", t->key);
	printTree(t->right);
}

int main() {
	avlNode *t = NULL;
	char op;
	while (scanf("\n%c", &op) && op != 'S') {
		int key;
		switch (op) {
			case 'I':
			scanf("%d", &key);
			insertNode(&t, key);
			break;
			case 'R':
			scanf("%d", &key);
			makeRoot(&t, key);
			break;
			case 'P':
			printf("root = %d\n", t == NULL ? -1 : t->key);
			printTree(t);
			printf("\n");
			break;
			default:
			printf("ERRO\n");
			break;
		}
	}
}
