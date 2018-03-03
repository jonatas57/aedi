#include <stdio.h>
#include <stdlib.h>

void check(){
  printf("check\n");
}

typedef struct linkMat mat;
typedef struct linkHead head;
typedef struct linkNode node;
struct linkMat{
  int nlin, ncol;
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

void insertNode(mat *M, int data, int x, int y){
  node N = {data, {x, y}, {NULL, NULL}};
  for (int a = 0;a < 2;a++){
    check();
    head *tmp;
    check();
    for (tmp = M->lc[a];tmp!=NULL&&tmp->next!=NULL&&tmp->ind<N.pos[x]&&tmp->ind!=N.pos[a];tmp = tmp->next);
    check();
    if (tmp == NULL){
      head h = {N.pos[a], NULL, &N};
      M->lc[a] = &h;
    }
    else if (tmp->next == NULL){
      head h = {N.pos[a], NULL, &N};
      tmp->next = &h;
    }
    else if (tmp->next->ind > N.pos[x]){
      head h = {N.pos[a], tmp->next, &N};
      tmp->next = &h;
    }
    else {
      node *aux;
      for (aux = tmp->node;aux->next[a]!=NULL&&aux->next[a]->pos[a]<N.pos[a];aux = aux->next[a]);
      if (aux == tmp->node){
        N.next[a] = aux;
        tmp->node = &N;
      }
      else if (aux->next[a] == NULL){
        aux->next[a] = &N;
      }
      else {
        N.next[a] = aux->next[a];
        aux->next[a] = &N;
      }
    }
    check();
  }
}
mat* initMat(int x, int y){
  mat M = {x, y, {NULL, NULL}};
  for (int i = 0;i < x;i++){
    for (int j = 0;j < y;j++){
      int num;
      scanf("%d", &num);
      if(num != 0){
        insertNode(&M, num, i, j);
      }
    }
  }
  mat *m = &M;
  return m;
}
void printMat(mat *M){
  int x = M->nlin, y = M->ncol;
  head *h = M->lc[0];
  node *n = NULL;
  for (int i = 0;i < x;i++){
    int p;
    if (h == NULL){
      p = 1;
    }
    else if (h->ind == i){
      p = 0;
      n = h->node;
      h = h->next;
    }
    for (int j = 0;j < y;j++){
      if (p || n == NULL || n->pos[1] != j){
        printf("0 ");
      }
      else {
        printf("%d ", n->data);
        n = n->next[0];
      }
    }
    printf("\n");
  }
}

int main() {
  int x, y;
  scanf("%d %d", &x, &y);
  mat *m = initMat(x, y);
  int p = 9;
  while(p){
    if(p == 1){
      int d, a, b;
      scanf("%d %d %d", &d, &a, &b);
      insertNode(m, d, a, b);
    }
    else if (p == 2){
      printMat(m);
    }
    printf("1-inserir\n2-print\n0-sair\n");
    scanf("%d", &p);
  }
  return 0;
}
