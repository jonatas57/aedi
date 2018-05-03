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
      scanf(" %c", &a);
      removeNode(&t, a);
    }
    else if (p == 3) {
      inOrder(t);
      printf("\n");
    }
    else if (p == 4){
      test(t, 0);
    }
    printf("1-insere, 2-remove, 3-print, 4-teste, 0-sair\n");
    scanf("%d", &p);
  }
	return 0;
}
