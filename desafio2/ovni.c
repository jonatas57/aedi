#include <stdio.h>
#include <stdlib.h>

typedef struct linkNode linkNode;
typedef struct ovni ovni;
struct ovni {
	int vel, cap, pra;
	double ef;
	char *mod;
};
struct linkNode {
	ovni *data;
	linkNode *next;
};

linkNode* newNode(char *m, int v, double k, int c, int p) {
	linkNode *x = malloc(sizeof(linkNode));
	ovni *o = malloc(sizeof(ovni));
	if (x != NULL && o != NULL) {
		o->mod = m;
		o->vel = v;
		o->ef = k;
		o->cap = c;
		o->pra = p;
		x->data = o;
		x->next = NULL;
	}
	return x;
}
linkNode* insertNode(linkNode *list, linkNode *last, linkNode *x) {
	if (last == NULL) {
		last = x;
		return x;
	}
	last->next = x;
	last = x;
	return list;
}
void printList(linkNode *list) {
	for (;list != NULL;list = list->next) {
		printf("[M=%s V=%d KM-L=%.2f C=%d E=%d]\n", list->mod, list->vel, list->ef, list->cap, list->pra);
	}
}
int compare(ovni a, ovni b, int m, int o) {
	int comp;
	if (m == 1) {
		comp = strcmp(a->mod, b->mod);
	}
	else if (m == 2) {
		comp = a->cap > b->cap ? 1 : -1;
	}
	else if (m == 5) {
		if (a->pra > b->pra) comp = 1;
		else if (a->pra < b->pra) comp = -1;
		else {
			comp * (a->ef > b->ef ? 1 : -1);
			comp * (o ? 1 : -1);
		}
		return comp;
	}
	else if (m == 6) {
		comp = a->pra > b->pra ? 1 : -1;
	}
	return comp * (o ? -1 : 1);
}
void quicksort(linkNode *list, linkNode *last, int m, int ord) {
	
}
void sort(linkNode *list, linkNode *last, int m) {
	printf("[O=%d]\n", m);
	int ord = m % 2;
	m /= 10;
	quicksort(list, last, m, ord);
	printList(list);
}
void freeList(linkNode *list) {
	if (list == NULL) return;
	freeList(list->next);
	free(list);
}

int main() {
	linkNode *list = NULL, *last = NULL;
	int op;
	while (scanf("%d", &op) != -1) {
		if (op == 1) {
			char *m;
			int v, c, p;
			double k;
			scanf("%s %d %lf %d %d", m, &v, &k, &c, &p);
			list = insertNode(list, last, newNode(m, v, k, c, p));
		}
		else if (op == 2) {
			printf("[DISCOS]\n");
			printList(list);
		}
		else if (op == 8) {
			int m;
			scanf("%d", &m);
			sort(list, last, m);
		}
		else if (op == 0) {
			freeList(list);
			return 0;
		}
	}
}
