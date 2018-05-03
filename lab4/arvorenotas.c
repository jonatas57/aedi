#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct treeNode treeNode;

struct treeNode {
  int key, value;
  int height;
  treeNode *left, *right;
};

void check() {
  printf("check\n");
}
void test(treeNode *t, int h) {
  if (t == NULL) return;
  for (int i = 0;i < h;i++) {
    printf("-");
  }
  printf("%p -> (%d, %d), %p <- -> %p\n", t, t->key, t->value, t->left, t->right);
  test(t->left, h + 1);
  test(t->right, h + 1);
}

treeNode* newNode(int key, int value) {
  treeNode *x = malloc(sizeof(treeNode));
  x->key = key;
  x->value = value;
  x->left = NULL;
  x->right = NULL;
  x->height = 0;
  return x;
}
void insertNode(treeNode **t, treeNode *x) {
  if (*t == NULL) {
    *t = x;
  }
  else if (x->key > (*t)->key) {
    insertNode(&(*t)->right, x);
  }
  else if (x->key < (*t)->key) {
    insertNode(&(*t)->left, x);
  }
  else {
    (*t)->value = x->value;
    free(x);
  }
}
void removeNode(treeNode **t, int key) {
  treeNode *x = *t, **prev = t;
	while (x != NULL) {
		int p;
		if (x->key < key) {
			prev = &x->right;
			x = x->right;
			p = 1;
		}
		else if (x->key > key) {
			prev = &x->left;
			x = x->left;
			p = 0;
		}
		else {
			if (x->left == NULL) {
				p ? (*prev = x->right) : (*prev= x->right);
				free(x);
			}
			else if (x->right == NULL) {
				p ? (*prev = x->left) : (*prev = x->left);
				free(x);
			}
			else {
				treeNode *aux = x->right, *aux2 = x;
				for (;aux->left != NULL;aux2 = aux, aux = aux->left);
				int a = aux->key;
				x->value = aux->value;
				removeNode(&aux2, aux->key);
				x->key = a;
			}
			x = NULL;
		}
	}
}
int* searchNode(treeNode *t, int key) {
  int *aux = malloc(2 * sizeof(int));
  aux[0] = 0;
  aux[1] = -1;
  if (t != NULL) {
    if (t->key > key) {
      aux = searchNode(t->left, key);
    }
    else if (t->key < key) {
      aux = searchNode(t->right, key);
    }
    else {
      aux[1] = t->value;
    }
    aux[0]++;
  }
  return aux;
}
int height(treeNode *t) {
  if (t == NULL) {
    return -1;
  }
  else {
    int a = height(t->left), b = height(t->right);
    t->height = (a > b ? a : b) + 1;
    return t->height;
  }
}

int main() {
  char op;
  treeNode *raTree = NULL;
  while (scanf("\n%c", &op) && op != 'P') {
    int ra, nota, *aux;
    switch (op) {
      case 'I':
      scanf("%d %d", &ra, &nota);
      insertNode(&raTree, newNode(ra, nota));
      break;
      case 'R':
      scanf("%d", &ra);
      removeNode(&raTree, ra);
      break;
      case 'B':
      scanf("%d", &ra);
      aux = searchNode(raTree, ra);
      printf("C=%d Nota=%d\n", aux[0], aux[1]);
      break;
      case 'A':
      printf("A=%d\n", height(raTree));
      break;
      case 'T':
      height(raTree);
      printf("-------------------\n");
      test(raTree, 0);
      printf("-------------------\n");
      break;
    }
  }
  return 0;
}
