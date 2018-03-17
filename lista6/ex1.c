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
TreeNode* removeNode(TreeNode **t, key k) {
  TreeNode *x = *t;
  while (x != NULL && x->pLeft->k != k && x->pRight->k != k) {
    x = x->k > k ? x->pLeft : x->pRight;
  }
  if (x != NULL) {
    TreeNode **tmp = x->pLeft->k == k ? &x->pLeft : &x->pRight;
    x = *tmp;
    if ((*tmp)->pRight == NULL && (*tmp)->pLeft == NULL) {
      *tmp = NULL;
    }
    else if ((*tmp)->pRight == NULL) {
      *tmp = (*tmp)->pLeft;
    }
    else if ((*tmp)->pLeft == NULL) {
      *tmp = (*tmp)->pRight;
    }
    else {
      TreeNode *s = (*tmp)->pRight;
      while (s->pLeft->pLeft != NULL);
      (*tmp)->k = s->pLeft->k;
      (*tmp)->v = s->pLeft->v;
      free(s->pLeft);
      s->pLeft = NULL;
    }
  }
  return x;
}

int main() {
	TreeNode *t = NULL;
  int p = 1000;
  while (p != 0) {
    key a;
    if (p == 1) {
      printf("insere a: ");
      scanf(" %c", &a);
      insertNode(&t, newNode(a, 0));
    }
    else if (p == 2) {
      printf("remove a: ");
      scanf(" %c", &a);
      free(removeNode(&t, a));
    }
    else if (p == 3) {
      inOrder(t);
      printf("\n");
    }
    else if (p == 4){
      test(t, 0);
    }
    printf("\n1-insere\n2-remove\n3-print\n4-teste\n0-sair\n");
    printf("scan p: ");
    scanf("%d", &p);
  }
	return 0;
}

// 1 P 1 H 1 D 1 A 1 C 1 E 1 O 1 I 1 M 1 L 1 N 1 T 1 S 1 U 1 Y
