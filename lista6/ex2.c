#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode TreeNode;
typedef char key;
typedef int value;

struct TreeNode {
	key k;
  value v;
  TreeNode *pLeft, *pRight;
};

void check() {
	printf("check\n");
}
void test(TreeNode *t, int a) {
  if (t == NULL) return;
  for(int i = 0;i < a;i++){
    printf("-");
  }
  printf("%p == %c, %p <- -> %p\n", t, t->k, t->pLeft, t->pRight);
  test(t->pLeft, a + 1);
  test(t->pRight, a + 1);
}

TreeNode* newNode(key k, value v) {
  TreeNode *x = malloc(sizeof(TreeNode));
  x->k = k;
  x->v = v;
  x->pLeft = NULL;
  x->pRight = NULL;
  return x;
}
void insertNode(TreeNode **t, TreeNode *x) {
  if (*t == NULL) {
    *t = x;
  }
  else if ((*t)->k > x->k) {
    insertNode(&(*t)->pLeft, x);
  }
  else if ((*t)->k < x->k) {
    insertNode(&(*t)->pRight, x);
  }
  else {
    (*t)->v = x->v;
    free(x);
  }
}
void removeNode(TreeNode **t, key k) {
  TreeNode *x = *t, **prev = t;
	while (x != NULL) {
		int p;
		if (x->k < k) {
			prev = &x->pRight;
			x = x->pRight;
			p = 1;
		}
		else if (x->k > k) {
			prev = &x->pLeft;
			x = x->pLeft;
			p = 0;
		}
		else {
			if (x->pLeft == NULL) {
				p ? (*prev = x->pRight) : (*prev= x->pRight);
				free(x);
			}
			else if (x->pRight == NULL) {
				p ? (*prev = x->pLeft) : (*prev = x->pLeft);
				free(x);
			}
			else {
				TreeNode *aux = x->pRight, *aux2 = x;
				for (;aux->pLeft != NULL;aux2 = aux, aux = aux->pLeft);
				key a = aux->k;
				x->v = aux->v;
				removeNode(&aux2, aux->k);
				x->k = a;
			}
			x = NULL;
		}
	}
}
TreeNode* minNode(TreeNode *t) {
	TreeNode *x = t;
	for (;x != NULL && x->pLeft != NULL;x = x->pLeft);
	return x;
}
TreeNode* maxNode(TreeNode *t) {
	TreeNode *x = t;
	for (;x != NULL && x->pRight != NULL;x = x->pRight);
	return x;
}
TreeNode* prevNode(TreeNode *t) {
	if (t == minNode(t)) return NULL;
	return maxNode(t->pLeft);
}
TreeNode* nextNode(TreeNode *t) {
	if (t == maxNode(t)) return NULL;
	return minNode(t->pRight);
}
TreeNode* searchTree(TreeNode *t, key k) {
  if (t == NULL){
    return t;
  }
  if (t->k > k) {
    return searchTree(t->pLeft, k);
  }
  else if (t->k < k) {
    return searchTree(t->pRight, k);
  }
  else {
    return t;
  }
}

void inOrder(TreeNode *t) {
  if (t == NULL) {
    return;
  }
  inOrder(t->pLeft);
  printf("%c ", t->k);
  inOrder(t->pRight);
}

int main() {
	TreeNode *t = NULL;
  int p = 1000;
  while (p != 0) {
    key a;
    if (p == 1) {
      scanf(" %c", &a);
      insertNode(&t, newNode(a, 0));
    }
    else if (p == 2) {
      inOrder(t);
      printf("\n");
    }
    else if (p == 3) {
      test(t, 0);
    }
    else if (p == 4){
			printf("%c\n", minNode(t)->k);
    }
		else if (p == 5){
      printf("%c\n", maxNode(t)->k);
    }
		else if (p == 6){
			scanf(" %c", &a);
      printf("%c\n", prevNode(searchTree(t, a))->k);
    }
		else if (p == 7){
			scanf(" %c", &a);
      printf("%c\n", nextNode(searchTree(t, a))->k);
    }
    printf("1-insere, 2-print, 3-teste, 4-min, 5-max, 6-ant, 7-suc, 0-sair\n");
    scanf("%d", &p);
  }
	return 0;
}
