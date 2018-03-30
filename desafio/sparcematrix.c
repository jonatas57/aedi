#include <stdio.h>
#include <stdlib.h>

typedef struct matriz matriz;
typedef struct head head;
typedef struct node node;

struct matriz {
  int tam[2];
  head *lc[2];
};
struct head {
  int index;
  head *next;
  node *node;
};
struct node {
  int data, pos[2];
  node *next[2];
};

node* newNode(int data) {
	node *x = malloc(sizeof(node));
	x->data = data;
	x->next[0] = NULL;
	x->next[1] = NULL;
	return x;
}
void initMat(matriz *m, int l, int c) {
	m->tam[0] = l;
	m->tam[1] = c;
	m->lc[0] = NULL;
	m->lc[1] = NULL;
}
void insertNode(matriz *M, node *n, int x, int y) {
  n->pos[0] = x;
  n->pos[1] = y;
  for (int a = 0;a < 2;a++) {
    head **aux = &M->lc[a];
    for (;*aux != NULL && (*aux)->index < n->pos[a] && (*aux)->next != NULL;aux = &(*aux)->next);
    if (*aux == NULL || (*aux)->index > n->pos[a]) {
      head *h = malloc(sizeof(head));
      h->index = n->pos[a];
      h->node = n;
      h->next = *aux;
      *aux = h;
    }
    else if ((*aux)->index == n->pos[a]) {
      node **aux2 = &(*aux)->node;
      for (;(*aux2)->pos[(a + 1) % 2] < n->pos[(a + 1) % 2] && (*aux2)->next[a] != NULL;aux2 = &(*aux2)->next[a]);
      if ((*aux2)->pos[(a + 1) % 2] == n->pos[(a + 1) % 2]){
        (*aux2)->data = n->data;
        free(n);
      }
      else if ((*aux2)->pos[(a + 1) % 2] > n->pos[(a + 1) % 2]) {
        n->next[a] = *aux2;
        *aux2 = n;
      }
      else {
        (*aux2)->next[a] = n;
      }
    }
    else {
      head *h = malloc(sizeof(head));
      h->index = n->pos[a];
      h->node = n;
      h->next = (*aux)->next;
      (*aux)->next = h;
    }
  }
}
void printMat(matriz *M) {
  int x = M->tam[0], y = M->tam[1];
  head *aux = M->lc[0];
  node *n = NULL;
  for (int i = 0;i < x;i++) {
    int p = 0;
    if (aux == NULL){
      p = 1;
    }
    else if (i == aux->index) {
      n = aux->node;
      aux = aux->next;
    }
		printf("[");
    for (int j = 0;j < y;j++) {
      if (p || n == NULL || j < n->pos[1]){
        printf("0 ");
      }
      else {
        printf("%d ", n->data);
        n = n->next[0];
      }
    }
    printf("]\n");
  }
}
matriz* multMat(matriz *a, matriz *b) {
	matriz *m = malloc(sizeof(matriz));
	initMat(m, a->tam[0], b->tam[1]);
	for (head *i = a->lc[0];i != NULL;i = i->next) {
		for (head *j = b->lc[1];j != NULL;j = j->next) {
			int s = 0;
			for (node *x = i->node, *y = j->node;x != NULL && y != NULL;) {
				if (x->pos[1] > y->pos[0]) {
					y = y->next[1];
				}
				else if (x->pos[1] < y->pos[0]){
					x = x->next[0];
				}
				else {
					s += x->data * y->data;
					x = x->next[0];
					y = y->next[1];
				}
			}
			insertNode(m, newNode(s), i->index, j->index);
		}
	}
	return m;
}

int main() {
	int la, ca, na, lb, cb, nb;
  matriz *A = malloc(sizeof(matriz)), *B = malloc(sizeof(matriz));
	scanf("%d %d %d %d %d %d", &la, &ca, &na, &lb, &cb, &nb);
	initMat(A, la, ca);
	initMat(B, lb, cb);
	int l, c, n;
	for (int i = 0;i < na;i++) {
		scanf("%d %d %d", &l, &c, &n);
		insertNode(A, newNode(n), l, c);
	}
	for (int i = 0;i < nb;i++) {
		scanf("%d %d %d", &l, &c, &n);
		insertNode(B, newNode(n), l, c);
	}
	char op;
	matriz *M = NULL;
	while (scanf("\n%c", &op) && op != 'S') {
		switch (op) {
			case 'A':
			printMat(A);
			break;
			case 'B':
			printMat(B);
			break;
			case 'M':
			M = multMat(A, B);
			printMat(M);
			break;
		}
		printf("\n");
	}
	return 0;
}
