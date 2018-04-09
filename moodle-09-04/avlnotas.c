#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct avlNode avlNode;

struct avlNode {
  int key, value;
  int height, fb;
  avlNode *left, *right;
};

void check() {
  printf("check\n");
}
void test(avlNode *t, int h) {
  if (t == NULL) return;
  for (int i = 0;i < h;i++) {
    printf("-");
  }
  printf("%p -> (%d, %d), %p <- -> %p\n", t, t->key, t->value, t->left, t->right);
  test(t->left, h + 1);
  test(t->right, h + 1);
}

avlNode* newNode(int key, int value) {
  avlNode *x = malloc(sizeof(avlNode));
  x->key = key;
  x->value = value;
  x->left = NULL;
  x->right = NULL;
  x->height = 0;
  return x;
}
int updateNode(avlNode *t) {
  if (t == NULL) {
    return -1;
  }
  else {
    int a = updateNode(t->left), b = updateNode(t->right);
    t->fb = (t->left == NULL ? -1 : t->left->height)-(t->right == NULL ? -1 : t->right->height);
    t->height = (a > b ? a : b) + 1;
    return t->height;
  }
}
void rotateLeft(avlNode **a) {
  avlNode *aux = (*a)->left;
  (*a)->left = aux->right;
  aux->right = *a;
  updateNode(*a);
  *a = aux;
}
void rotateRight(avlNode **a) {
  avlNode *aux = (*a)->right;
  (*a)->right = aux->left;
  aux->left = *a;
  updateNode(*a);
  *a = aux;
}
void balanceNode(avlNode **a) {
  printf("[No desbalanceado: %d]\n", (*a)->key);
  if ((*a)->fb > 1) {
    if ((*a)->fb * (*a)->left->fb < 0) {
      printf("[Rotacao: DE]\n");
      rotateRight(&(*a)->left);
    }
    else {
      printf("[Rotacao: SE]");
      rotateLeft(a);
    }
  }
  else {
    if ((*a)->fb * (*a)->right->fb < 0) {
      printf("[Rotacao: DD]");
      rotateLeft(&(*a)->right);
    }
    else {
      printf("[Rotacao: SD]");
      rotateRight(a);
    }
  }
  printf("[x=%d y=%d z=%d]\n", (*a)->left->key, (*a)->key, (*a)->right->key);
}
int insertNode(avlNode **a, avlNode *x) {
  int r = 1;
  if (*a == NULL) {
    *a = x;
  }
  else if ((*a)->key < x->key) {
    r = insertNode(&(*a)->right, x);
  }
  else if ((*a)->key > x->key) {
    r = insertNode(&(*a)->left, x);
  }
  updateNode(*a);
  return r *= ((*a)->fb >= -1 || (*a)->fb <= 1) ? 1 : 0;
}
void removeNode(avlNode **endt, avlNode *t, int key) {
  if (t == NULL) return;
  if (t->key < key) {
    removeNode(&t->right, t->right, key);
  }
  else if (t->key > key) {
    removeNode(&t->left, t->left, key);
  }
  else {
    if (t->left == t->right) {
      free(t);
      *endt = NULL;
    }
    else if (t->left == NULL) {
      *endt = t->right;
      free(t);
      updateNode(*endt);
      t = *endt;
      if (t->fb > 1 || t->fb < -1) balanceNode(endt);
    }
    else if (t->right == NULL) {
      *endt = t->left;
      free(t);
      updateNode(*endt);
      t = *endt;
      if (t->fb > 1 || t->fb < -1) balanceNode(endt);
    }
    else {
      avlNode *aux = t->right, **endaux = &aux;
      for (;aux->left != NULL;aux = aux->left, endaux = &aux->left);
      t->key = aux->key;
      t->value = aux->value;
      removeNode(endaux, aux, aux->key);
      updateNode(t);
      if (t->fb > 1 || t->fb < -1) balanceNode(endt);
    }
  }
}
int* searchNode(avlNode *t, int key) {
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
void postOrder(avlNode **t) {
  if (*t == NULL) return;
  postOrder(&(*t)->left);
  postOrder(&(*t)->right);
  printf("%d ", (*t)->key);
  removeNode(t, *t, (*t)->key);
}

int main() {
  char op;
  avlNode *raTree = NULL;
  while (scanf("\n%c", &op) != 0) {
    int ra, nota, *aux;
    if (op == 'I') {
      scanf("%d %d", &ra, &nota);
      int x = insertNode(&raTree, newNode(ra, nota));
      if (x) {
        printf("[Ja esta balanceado]\n");
      }
      else {
        balanceNode(&x);
      }
    }
    else if (op == 'R') {
      scanf("%d", &ra);
      removeNode(&raTree, raTree, ra);
    }
    else if (op == 'B') {
      scanf("%d", &ra);
      aux = searchNode(raTree, ra);
      printf("C=%d Nota=%d\n", aux[0], aux[1]);
    }
    else if (op == 'A') {
      printf("A=%d\n", updateNode(raTree));
    }
    else if (op == 'T') {
      updateNode(raTree);
      printf("-------------------\n");
      test(raTree, 0);
      printf("-------------------\n");
    }
    else if (op == 'P') {
      printf("[");
      postOrder(&raTree);
      printf("]\n");
      return 0;
    }
  }
}
