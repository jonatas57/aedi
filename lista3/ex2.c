#include <stdio.h>
#include <stdlib.h>

void check(){
  printf("check\n");
}

typedef struct linkMat mat;
typedef struct linkHead head;
typedef struct linkNode node;
struct linkMat{
  int tam[2];
  head *lc[2];
};
struct linkHead{
  int ind;
  head *next;
  node *node;
};
struct linkNode{
  int data, pos[2];
  node *next[2];
};

void test(mat *M){
  printf("M->lc[0] = %p\n", M->lc[0]);
  printf("M->lc[1] = %p\n", M->lc[1]);
  printf("linhas:\n");
  for (head *h = M->lc[0];h != NULL;h = h->next){
    printf("%p: (%d, ?)->next = %p, node = %p\n", h, h->ind, h->next, h->node);
    for (node *n = h->node;n != NULL;n = n->next[0]){
      printf("-%p: (%d, %d) = %d, v %p, > = %p\n", n, n->pos[0], n->pos[1], n->data, n->next[0], n->next[1]);
    }
  }
  printf("colunas:\n");
  for (head *h = M->lc[1];h != NULL;h = h->next){
    printf("%p: (?, %d)->next = %p, node = %p\n", h, h->ind, h->next, h->node);
    for (node *n = h->node;n != NULL;n = n->next[1]){
      printf("-%p: (%d, %d) = %d, > %p, v = %p\n", n, n->pos[0], n->pos[1], n->data, n->next[0], n->next[1]);
    }
  }
}
void insertNode(mat *M, int data, int x, int y) {
  node *n = malloc(sizeof(node));
  n->data = data;
  n->pos[0] = x;
  n->pos[1] = y;
  n->next[0] = NULL;
  n->next[1] = NULL;
  for (int a = 0;a < 2;a++){
    head **aux = &M->lc[a];
    for (;*aux != NULL && (*aux)->ind < n->pos[a] && (*aux)->next != NULL && (*aux)->next->ind <= n->pos[a];aux = ((*aux)->next));
    if (*aux == NULL || (*aux)->ind > n->pos[a]){
      head *h = malloc(sizeof(head));
      h->ind = n->pos[a];
      h->node = n;
      h->next = *aux;
      *aux = h;
    }
    else if ((*aux)->ind == n->pos[a]){
      node *aux2;
      for (aux2 = (*aux)->node;aux2->pos[(a + 1) % 2] < n->pos[(a + 1)%2] && aux2->next[a] != NULL && aux2->next[a]->pos[(a + 1)%2] < n->pos[(a + 1)%2];aux2 = aux2->next[a]);
      if (aux2->next[a] == NULL){
        aux2->next[a] = n;
        n->next[a] = NULL;
      }
      else if (aux2->pos[(a + 1) % 2] < n->pos[(a + 1)%2]) {
        /* code */
      }
      else if (aux2->next[a]->pos[(a + 1)%2] == n->pos[(a + 1)%2]) {
        aux2->next[a]->data = data;
        free(n);
      }
      else {
        n->next[a] = aux2->next[a];
        aux2->next[a] = n;
      }
    }
    else if ((*aux)->next == NULL){
      head *h = malloc(sizeof(head));
      h->ind = n->pos[a];
      h->node = n;
      h->next = NULL;
      (*aux)->next = h;
    }
    else {
      head *h = malloc(sizeof(head));
      h->ind = n->pos[a];
      h->node = n;
      h->next = (*aux)->next;
      (*aux)->next = h->next;
    }
  }
}
void printMat(mat *M) {
  printf("\n");
  int x = M->tam[0], y = M->tam[1];
  head *aux = M->lc[0];
  node *n = NULL;
  for (int i = 0;i < x;i++) {
    int p = 0;
    if (aux == NULL){
      p = 1;
    }
    else if (i == aux->ind) {
      n = aux->node;
      aux = aux->next;
    }
    for (int j = 0;j < y;j++) {
      if (p || n == NULL || j < n->pos[1]){
        printf("0 ");
      }
      else {
        printf("%d ", n->data);
        n = n->next[0];
      }
    }
    printf("\n");
  }
  printf("\n");
}
void printTransp(mat *M) {
  printf("\n");
  int x = M->tam[0], y = M->tam[1];
  head *aux = M->lc[1];
  node *n = NULL;
  for (int i = 0;i < y;i++) {
    int p = 0;
    if (aux == NULL){
      p = 1;
    }
    else if (i == aux->ind) {
      n = aux->node;
      aux = aux->next;
    }
    for (int j = 0;j < x;j++) {
      if (p || n == NULL || j < n->pos[0]){
        printf("0 ");
      }
      else {
        printf("%d ", n->data);
        n = n->next[1];
      }
    }
    printf("\n");
  }
  printf("\n");
}
mat* initMat(int x, int y){
  mat *M = malloc(sizeof(mat));
  if(M != NULL){
    M->tam[0] = x;
    M->tam[1] = y;
    M->lc[0] = NULL;
    M->lc[1] = NULL;
    for (int i = 0;i < x;i++) {
      for (int j = 0;j < y;j++) {
        int num;
        scanf("%d", &num);
        if (num != 0) {
          insertNode(M, num, i, j);
        }
      }
    }
  }
  return M;
}

int main() {
  int x, y;
  printf("Dimensoes da matriz: ");
  scanf("%d %d", &x, &y);
  mat *m = initMat(x, y);
  int p = 5;
  while (p){
    int a, b, c;
    switch (p){
      case 1:
      scanf("%d %d %d", &a, &b, &c);
      insertNode(m, a, b, c);
      break;
      case 2:
      printMat(m);
      break;
      case 3:
      printTransp(m);
      break;
      case 4:
      test(m);
      break;
    }
    printf("1-inserir, 2-print, 3-print transposta, 4-teste, 0-sair\n");
    scanf("%d", &p);
  }
  return 0;
}