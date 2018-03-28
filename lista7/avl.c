#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct avlNode avlNode;
typedef char key;

struct avlNode {
  int h;
  key k;
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
  printf("%p == %c, %p <- -> %p, h = %d\n", t, t->k, t->left, t->right, t->h);
  test(t->left, a + 1);
  test(t->right, a + 1);
}
void inOrder(avlNode *a) {
  if (a == NULL) return;
  inOrder(a->left);
  printf("%c", a->k);
  inOrder(a->right);
}

avlNode* newNode(key k) {
  avlNode *x = malloc(sizeof(avlNode));
  x->k = k;
  x->h = 0;
  x->left = NULL;
  x->right = NULL;
  return x;
}
int updateHeight(avlNode *a) {
  if (a == NULL) return -1;
  int x = updateHeight(a->left), y = updateHeight(a->right);
  a->h = (x > y ? x : y) + 1;
  return a->h;
}
void rotateLeft(avlNode **a) {
  avlNode *aux = (*a)->left;
  (*a)->left = aux->right;
  aux->right = *a;
  updateHeight(*a);
  *a = aux;
}
void rotateRight(avlNode **a) {
  avlNode *aux = (*a)->right;
  (*a)->right = aux->left;
  aux->left = *a;
  updateHeight(*a);
  *a = aux;
}
void insertNode(avlNode **a, avlNode *x) {
  if (*a == NULL) {
    *a = x;
  }
  else if ((*a)->k < x->k) {
    insertNode(&(*a)->right, x);
  }
  else if ((*a)->k > x->k) {
    insertNode(&(*a)->left, x);
  }
  updateHeight(*a);
  int fb = ((*a)->left == NULL ? -1 : (*a)->left->h)-((*a)->right == NULL ? -1 : (*a)->right->h);
  if (fb > 1) {
    rotateLeft(a);
  }
  else if (fb < -1){
    rotateRight(a);
  }
}

int main() {
  avlNode *t = NULL;
  key a;
  while (scanf("%c\n", &a) != 0 && a != '!') {
    insertNode(&t, newNode(a));
  }
  test(t, 0);
  inOrder(t);
  printf("\n");
	return 0;
}
