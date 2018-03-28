#include <stdio.h>
#include <stdlib.h>

void check() {
	printf("check\n");
}

typedef struct matriz mat;
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
void test(mat *M){
  printf("M->lc[0] = %p\n", M->lc[0]);
  printf("M->lc[1] = %p\n", M->lc[1]);
  printf("linhas:\n");
  for (head *h = M->lc[0];h != NULL;h = h->next){
    printf("%p: (%d, ?)->next = %p, node = %p\n", h, h->index, h->next, h->node);
    for (node *n = h->node;n != NULL;n = n->next[0]){
      printf("-%p: (%d, %d) = %d, v %p, > = %p\n", n, n->pos[0], n->pos[1], n->data, n->next[0], n->next[1]);
    }
  }
  printf("colunas:\n");
  for (head *h = M->lc[1];h != NULL;h = h->next){
    printf("%p: (?, %d)->next = %p, node = %p\n", h, h->index, h->next, h->node);
    for (node *n = h->node;n != NULL;n = n->next[1]){
      printf("-%p: (%d, %d) = %d, > %p, v = %p\n", n, n->pos[0], n->pos[1], n->data, n->next[0], n->next[1]);
    }
  }
}

node* newNode(int data) {
	node *x = malloc(sizeof(node));
	x->data = data;
	x->next[0] = NULL;
	x->next[1] = NULL;
	return x;
}
void initMat(mat *m, int l, int c) {
	m->tam[0] = l;
	m->tam[1] = c;
	m->lc[0] = NULL;
	m->lc[1] = NULL;
}
void insertNode(mat *m, node *x, int a, int b) {
	x->pos[0] = a;
	x->pos[1] = b;
	for (int i = 0;i < 2;i++) {
		head **h = &m->lc[i];
		int p = 1;
		while (p) {
			check();
			if (*h == NULL) {
				head *new = malloc(sizeof(head));
				new->index = x->pos[i];
				new->next = NULL;
				new->node = x;
				*h = new;
				p = 0;
			}
			else if ((*h)->index == x->pos[i]) {
				node **n = &(*h)->node;
				if ((*n)->pos[(i + 1) % 2] > x->pos[(i + 1) % 2]) {
					x->next[i] = *n;
					*n = x;
				}
				else if ((*n)->pos[(i + 1) % 2] == x->pos[(i + 1) % 2]) {
					(*n)->data = x->data;
					free(x);
				}
				else if ((*n)->next == NULL) {
					(*n)->next[i] = x;
				}
				else if ((*n)->next[i]->pos[(i + 1) % 2] > x->pos[(i + 1) % 2]) {
					x->next[i] = (*n)->next[i];
					(*n)->next[i] = x;
				}
				n = &(*n)->next[(i + 1) % 2];
			}
			else if ((*h)->next->index > x->pos[i]) {
				head *new = malloc(sizeof(head));
				new->index = x->pos[i];
				new->next = (*h)->next;
				new->node = x;
				(*h)->next = new;
				p = 0;
			}
			h = &(*h)->next;
		}
	}
	test(m);
}
void printMat(mat *m) {
	if (m == NULL) return;
	int x = m->tam[0], y = m->tam[1];
	head *aux = m->lc[0];
	for (int i = 0;i < x;i++) {
		printf("[");
		node *naux = aux->node;
		for (int j = 0;j < y;j++) {
			if (naux == NULL || j < naux->pos[1]) {
				printf("0 ");
			}
			else {
				printf("%d ", naux->data);
				naux = naux->next[1];
			}
		}
		printf("]\n");
	}
}
mat* multMat(mat *a, mat *b) {
	mat *m = NULL;
	if (a->tam[1] == b->tam[0]) {
		int x = a->tam[0], y = b->tam[1], z = a->tam[1];
		for (int i = 0;i < x;) {
			head *ha = a->lc[0];
			if (ha != NULL || ha->index == i) {
				for (int j = 0;j < y;j++, i++) {
					head *hb = b->lc[1];
					if (hb != NULL || hb->index == j) {
						int s = 0;
						node *na = ha->node, *nb = hb->node;
						for (int k = 0;k < z;k++) {
							if (na->pos[1] == k && nb->pos[0] == k) {
								s += na->pos[1] * nb->pos[k];
							}
							else if (na->pos[1] == k) {
								na = na->next[0];
							}
							else if (nb->pos[0] == k) {
								nb = nb->next[1];
							}
						}
						if (s != 0) insertNode(m, newNode(s), i, j);
					}
				}
			}
			ha = ha->next;
		}
	}
	return m;
}

int main() {
	int la, ca, na, lb, cb, nb;
  mat *A = malloc(sizeof(mat)), *B = malloc(sizeof(mat));
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
	while (scanf("\n%c", &op) && op != 'S') {
		mat *M = NULL;
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
			case 'T':
			printf("teste A:---------------------\n");
			test(A);
			printf("teste B:---------------------\n");
			test(B);
			printf("teste M:---------------------\n");
			test(M);
			break;
		}
	}
	return 0;
}
