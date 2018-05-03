#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode TreeNode;
typedef struct LinkedNode LinkedNode;

void check() {
  printf("check\n");
}

struct TreeNode {
  int key;
  TreeNode *left, *right;
};
struct LinkedNode {
  int data;
  LinkedNode *next;
};

void testA(TreeNode *t, int a) {
  if (t == NULL) return;
  for(int i = 0;i < a;i++){
    printf("-");
  }
  printf("%p == %d, %p <- -> %p\n", t, t->key, t->left, t->right);
  testA(t->left, a + 1);
  testA(t->right, a + 1);
}
void testL(LinkedNode *x) {
  for (;x!=NULL;x = x->next) {
    printf("%p = %d -> %p\n", x, x->data, x->next);
  }
}
void printList(LinkedNode *ini){
  for(;ini != NULL;ini = ini->next){
    printf("%d ", ini->data);
  }
  printf("\n");
}

TreeNode* newTNode(int k) {
  TreeNode *x = malloc(sizeof(TreeNode));
  x->key = k;
  x->left = NULL;
  x->right = NULL;
  return x;
}
void insertTNode(TreeNode **t, TreeNode *x) {
  if (*t == NULL) {
    *t = x;
  }
  else if ((*t)->key > x->key) {
    insertTNode(&(*t)->left, x);
  }
  else if ((*t)->key < x->key) {
    insertTNode(&(*t)->right, x);
  }
  else {
    free(x);
  }
}
LinkedNode* newLNode(int ra){
  LinkedNode* x = malloc(sizeof(LinkedNode));
  x->data = ra;
  x->next = NULL;
  return x;
}
void insertLNode(LinkedNode **ini, LinkedNode *x){
  if (*ini == NULL){
    *ini = x;
  }
  else {
    LinkedNode **aux = ini;
    for (;*aux != NULL && (*aux)->data < x->data;aux = &(*aux)->next);
    x->next = *aux;
    *aux = x;
  }
}
int searchTree(TreeNode *t, int ra, int qtd) {
  if (t == NULL) {
    return qtd;
  }
  qtd++;
  if (t->key == ra) return qtd;
  return ra < t->key ? searchTree(t->left, ra, qtd) : searchTree(t->right, ra, qtd);
}
int searchList(LinkedNode *l, int ra, int qtd) {
  if (l == NULL) {
    return qtd;
  }
  qtd++;
  if (l->data == ra) return qtd;
  return ra < l->data ? qtd : searchList(l->next, ra, qtd);
}

int main() {
  int ra;
  char op;
  LinkedNode *lista = NULL;
  TreeNode *arvore = NULL;
  while (scanf(" %c %d", &op, &ra) && (op != 'P' || ra != 0)) {
    if (op == 'I') {
      insertTNode(&arvore, newTNode(ra));
      insertLNode(&lista, newLNode(ra));
    }
    else if (op == 'B') {
      printf("L=%d A=%d\n", searchList(lista, ra, 0), searchTree(arvore, ra, 0));
    }
    else if (op == 'T'){
      printf("arvore: \n");
      testA(arvore, 0);
      printf("lista:\n");
      testL(lista);
    }
  }
  return 0;
}
