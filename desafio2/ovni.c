#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct linkNode linkNode;
typedef struct ovni ovni;
struct ovni {
	int vel, cap, pra;
	double ef;
	char *mod;
};
struct linkNode {
	ovni *data;
	linkNode *next, *prev;
};

void check() {
	printf("check\n");
}
void test(linkNode *t) {
	if (t == NULL) return;
	for (;t != NULL;t = t->next) {
		printf("%p = %p <- (%p) -> %p\n", t, t->prev, t->data, t->next);
	}
}
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
		x->prev = NULL;
	}
	return x;
}
linkNode** insertNode(linkNode *list, linkNode *last, linkNode *x) {
	linkNode **aux = malloc(2 * sizeof(linkNode*));
	if (last == NULL) {
		aux[0] = x;
		aux[1] = x;
	}
	else {
		last->next = x;
		x->prev = last;
		aux[0] = list;
		aux[1] = x;
	}
	return aux;
}
void printList(linkNode *list) {
	for (;list != NULL;list = list->next) {
		printf("[M=%s V=%d KM-L=%.2f C=%d E=%d]\n", list->data->mod, list->data->vel, list->data->ef, list->data->cap, list->data->pra);
	}
}
int compare(ovni *a, ovni *b, int m, int o) {
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
			comp = (a->ef > b->ef ? 1 : -1);
			comp *= (o ? 1 : -1);
		}
		return comp;
	}
	else if (m == 6) {
		comp = a->pra > b->pra ? 1 : -1;
	}
	return comp * (o ? -1 : 1);
}
void swap(ovni *a, ovni *b) {
	ovni *tmp = a;
	a = b;
	b = tmp;
}
void quicksort(linkNode *list, linkNode *last, int m, int ord) {
	if (list == NULL || list == last || last == NULL || list == last->next) return;
	linkNode *pivo = list, *aux = list;
	for (linkNode *tmp = list->next;tmp != last->next;tmp = tmp->next) {
		if (compare(pivo->data , tmp->data, m, ord) > 0) {
			aux = aux->next;
			swap(aux->data, tmp->data);
		}
	}
	printf("quick\n");
	printList(list);
	swap(pivo->data, aux->data);
	quicksort(list, aux->prev, m, ord);
	quicksort(aux->next, last, m, ord);
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
			char *m = malloc(51 * sizeof(char));
			int v, c, p;
			double k;
			scanf("%s %d %lf %d %d", m, &v, &k, &c, &p);
			linkNode **aux = malloc(2 * sizeof(linkNode*));
			aux = insertNode(list, last, newNode(m, v, k, c, p));
			list = aux[0];
			last = aux[1];
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
