#include <stdio.h>
#include <stdlib.h>

typedef struct avlNode avlNode;
struct avlNode {
	char *key;
	int value;
	int height, fb;
	avlNode *left, *right;
};

int* updateNode(avlNode **t);//apenas inicialização

avlNode* newNode(char *key) {
	avlNode *x = malloc(sizeof(avlNode));
	if (x != NULL) {
		x->key = malloc(51 * sizeof(char));
		x->key = key;
		x->height = 0;
		x->value = 1;
		x->fb = 0;
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
int* balanceNode(avlNode **t) {
	if ((*t)->fb > 1) {
		if ((*t)->fb * (*t)->left->fb < 0) {
			rotateLeft(&(*t)->left);
			rotateRight(t);
		}
		else {
			rotateRight(t);
		}
	}
	else {
		if ((*t)->fb * (*t)->right->fb < 0) {
			rotateRight(&(*t)->right);
			rotateLeft(t);
		}
		else {
			rotateLeft(t);
		}
	}
	return updateNode(t);
}
int* updateNode(avlNode **t) {
	int *x = malloc(2 * sizeof(int));
	x[0] = -1;
	x[1] = 1;
	if (*t != NULL) {
		int *a = updateNode(&(*t)->left), *b = updateNode(&(*t)->right);
		(*t)->height = (a[0] > b[0] ? a[0] : b[0]) + 1;
		(*t)->fb = a[0] - b[0];
		x[1] *= a[1] * b[1];
		if ((*t)->fb > 1 || (*t)->fb < -1) {
			balanceNode(t);
			x[1] = 0;
		}
		x[0] = (*t)->height;
	}
	return x;
}
int insertNode(avlNode **t, char *key) {
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
	else {
		(*t)->value++;
	}
	r *= updateNode(t)[1];
	return r;
}
int removeNode(avlNode **endt, avlNode *t, char *key) {
	int r = 1;
	if (t != NULL) {
		if (t->key > key) {
			r *= removeNode(&t->left, t->left, key);
		}
		else if (t->key < key) {
			r *= removeNode(&t->right, t->right, key);
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
				t->value = x->value;
				r *= removeNode(endx, x, x->key);
			}
		}
		r *= updateNode(endt)[1];
	}
	return r;
}
int* searchNode(avlNode *t, char *key) {
	int *aux = malloc(2 * sizeof(int));
	aux[0] = 0;
	aux[1] = -1;
	if (t != NULL) {
		if (t->key < key) {
			aux = searchNode(t->right, key);
		}
		else if (t->key > key) {
			aux = searchNode(t->left, key);
		}
		else {
			aux[1] = t->value;
		}
		aux[0]++;
	}
	return aux;
}
void printTree(avlNode *t) {
	if (t == NULL) return;
	printTree(t->left);
	printf("%s %d\n", t->key, t->value);
	printTree(t->right);
}

int main() {
	char p[51];
	avlNode *w = NULL;
	while (scanf("%s", p) != -1) {
		printf("%s\n", p);
		insertNode(&w, p);
	}
	printTree(w);
}
