#include <stdio.h>
#include <stdlib.h>

typedef struct avlNode avlNode;
struct avlNode {
	int key;
	int height, fb;
	avlNode *left, *right;
};
void test(avlNode *t, int a) {
	if (t == NULL) return;
	for (int i = 0;i < a; i++) {
		printf("-");
	}
	printf("%p = %d, %p <--> %p, (%d, %d)\n", t, t->key, t->left, t->right, t->height, t->fb);
	test(t->left, a + 1);
	test(t->right, a + 1);
}

avlNode* newNode(int key) {
	avlNode *x = malloc(sizeof(avlNode));
	if (x != NULL) {
		x->key = key;
		x->height = 0;
		x->fb = 0;
		x->left = NULL;
		x->right = NULL;
	}
	return x;
}//
int updateNode(avlNode *t) {
	int x = -1;
	if (t != NULL) {
		int a = updateNode(t->left), b = updateNode(t->right);
		t->height = (a > b ? a : b) + 1;
		t->fb = a - b;
		x = t->height;
	}
	return x;
}
void insertNode(avlNode **t, int key) {
	if (*t == NULL) {
		*t = newNode(key);
	}
	else if ((*t)->key < key) {
		insertNode(&(*t)->right, key);
	}
	else if ((*t)->key > key) {
		insertNode(&(*t)->left, key);
	}
}
void removeNode(avlNode **endt, avlNode *t, int key) {
	if (t != NULL) {
		if (t->key > key) {
			removeNode(&t->left, t->left, key);
		}
		else if (t->key < key) {
			removeNode(&t->right, t->right, key);
		}
		else {
			if (t->left == NULL) {
				*endt = t->right;
				free(t);
			}
			else if (t->right == NULL) {
				*endt = t->left;
				free(t);
			}
			else {
				avlNode *x = t->right, **endx = &t->right;
				for (;x->left != NULL;endx = &x->left, x = x->left);
				t->key = x->key;
				removeNode(endx, x, x->key);
			}
		}
	}
}
void inOrder(avlNode *t) {
	if (t == NULL) return;
	inOrder(t->left);
	printf("%d ", t->key);
	inOrder(t->right);
}
int fbCheck(avlNode *t) {
	int x = 1;
	if (t != NULL) {
		x = (t->fb <= 1 && t->fb >= -1 ? 1 : 0) * fbCheck(t->left) * fbCheck(t->right);
	}
	return x;
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
			case 'F':
			updateNode(t);
			key = fbCheck(t);
			printf(" %s AVL\n", key ? "É" : "Não é");
			break;
			case 'P':
			printTree(t);
			printf("\n");
			break;
			case 'T':
			test(t, 0);
			break;
			default:
			printf("ERRO\n");
			break;
		}
	}
}
