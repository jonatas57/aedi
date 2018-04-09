#include <stdio.h>
#include <stdlib.h>

typedef struct avlNode avlNode;
struct avlNode {
	int key, value;
	int height, fb;
	avlNode *left, *right;
};
void check(){
  printf("check\n");
}
void test(avlNode *t, int a) {
  if (t == NULL) return;
  for(int i = 0;i < a;i++){
    printf("-");
  }
  printf("%p == %d, %p <- -> %p, h = %d, fb = %d\n", t, t->key, t->left, t->right, t->height, t->fb);
  test(t->left, a + 1);
  test(t->right, a + 1);
}

int* updateNode(avlNode **t);//apenas inicialização

avlNode* newNode(int key, int value) {
	avlNode *x = malloc(sizeof(avlNode));
	if (x != NULL) {
		x->key = key;
		x->value = value;
		x->height = 0;
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
  updateNode(t);
  *t = aux;
}
void rotateLeft(avlNode **t) {
  avlNode *aux = (*t)->right;
  (*t)->right = aux->left;
  aux->left = *t;
  updateNode(t);
  *t = aux;
}
void balanceNode(avlNode **t) {
	printf("[No desbalanceado: %d]\n", (*t)->key);
	if ((*t)->fb > 1) {
		if ((*t)->fb * (*t)->left->fb < 1) {
			printf("[Rotacao: DD]\n");
			rotateLeft(&(*t)->left);
			rotateRight(&(*t));
		}
		else {
			printf("[Rotacao: SD]\n");
			rotateRight(&(*t));
		}
	}
	else {
		if ((*t)->fb * (*t)->right->fb < 1) {
			printf("[Rotacao: DE]\n");
			rotateRight(&(*t)->right);
			rotateLeft(&(*t));
		}
		else {
			printf("[Rotacao: SE]\n");
			rotateLeft(&(*t));
		}
	}
	printf("[x=%d y=%d z=%d]\n", (*t)->left->key, (*t)->key, (*t)->right->key);
}
int* updateNode(avlNode **t) {
	int *x =malloc(2 * sizeof(int)), r = 1;
	x[0] = -1;
	x[1] = 1;
	if (*t != NULL) {
		int *a = updateNode(&(*t)->left), *b = updateNode(&(*t)->right);
		(*t)->height = (a[0] > b[0] ? a[0] : b[0]) + 1;
		(*t)->fb = a[0] - b[0];
		if ((*t)->fb > 1 || (*t)->fb < -1) {
			balanceNode(t);
			r = 0;
		}
		x[0] = (*t)->height;
		x[1] = r;
	}
	return x;
}
int insertNode(avlNode **t, int key, int value) {
	int r = 1;
	if (*t == NULL) {
		*t = newNode(key, value);
	}
	else if ((*t)->key < key) {
		r *= insertNode(&(*t)->right, key, value);
	}
	else if ((*t)->key > key) {
		r *= insertNode(&(*t)->left, key, value);
	}
	else {
		(*t)->value = value;
	}
	r *= updateNode(t)[1];
	return r;
}
void removeNode(avlNode **endt, avlNode *t, int key) {
	if (t == NULL) return;
	if (t->key > key) {
		removeNode(&t->right, t->right, key);
	}
	else if (t->key < key) {
		removeNode(&t->left, t->left, key);
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
			removeNode(endx, x, x->key);
		}
	}
	updateNode(endt);
}
int* searchNode(avlNode *t, int key) {
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
void postOrder(avlNode **t) {
	if (*t == NULL) return;
	postOrder(&(*t)->left);
	postOrder(&(*t)->right);
	printf("%d ", (*t)->key);
	removeNode(t, *t, (*t)->key);
}

int main() {
	avlNode *raTree = NULL;
	char op;
	while (scanf("\n%c", &op) != 0) {
		if (op == 'I') {
			int ra, nota;
			scanf("%d %d", &ra, &nota);
			int r = insertNode(&raTree, ra, nota);
			if (r) printf("[Ja esta balanceado]\n");
		}
		else if (op == 'R') {
			int ra;
			scanf("%d\n", &ra);
			removeNode(&raTree, raTree, ra);
			test(raTree, 0);
		}
		else if (op == 'B') {
			int ra;
			scanf("%d\n", &ra);
			int *x = searchNode(raTree, ra);
			printf("C=%d Nota=%d\n", x[0], x[1]);
		}
		else if (op == 'A') {
			printf("A=%d\n", updateNode(&raTree)[0]);
		}
		else if (op == 'P') {
			printf("[");
			postOrder(&raTree);
			printf("]\n");
			return 0;
		}
	}
}
