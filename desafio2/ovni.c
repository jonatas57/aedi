#include <stdio.h>
#include <stdlib.h>

typedef struct linkNode ovni;
struct linkNode {
	int vel, cap, pra;
	double ef;
	char *mod;
	linkNode *next;
};

ovni* newNode(char *m, int v, double k, int c, int p);
ovni* insertNodd(linkNode *list, linkNode *x);
void printList(linkNode *list);
int compare(a, b);
void qsort();
void sort(linkNode *list, int m);
void freeList(linkNode *list);

int main() 
	ovni *d = NULL;
	int op;
	while (scanf("%d", &op) != -1) {
		if (op == 1) {
			char *m;
			int v, c, p;
			double k;
			scanf("%s %d %f %d %d", &m, &v, &k, &c, &p);
			d = insertNode(d, newNode(m, v, k, c, p);
		}
		else if (op == 2) {
			printList(d);
		}
		else if (op == 8) {
			int m;
			scanf("%d", &m);
			sort(d, m);
		}
		else if (op == 0) {
			freeList(d);
			return 0;
		}
	}
}