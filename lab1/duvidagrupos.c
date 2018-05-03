#include <stdio.h>
#include <stdlib.h>

typedef struct listNode no;

struct listNode{
  int ra, CodTopico;
  no* next;
};

no* newNode(int ra, int top){
  no* x = malloc(sizeof(no));
  x->ra = ra;
  x->CodTopico = top;
  x->next = NULL;
  return x;
}
void printList(no *ini){
  for(;ini != NULL;ini = ini->next){
    printf("%d %d\n", ini->ra, ini->CodTopico);
  }
}
void insertNode(no **ini, no *x){
  if (*ini == NULL){
    *ini = x;
  }
  else {
    no *aux;
    for (aux = *ini;aux != NULL && aux->next != NULL && (aux->ra != x->ra || aux->next->ra == x->ra);aux = aux->next);
    x->next = aux->next;
    aux->next = x;
  }
}

int main() {
  no *list = NULL;
  int ra, top;
  while(scanf("%d %d", &ra, &top) != 0 && (ra != -1 || top != -1)){
    insertNode(&list, newNode(ra, top));
  }
  printList(list);
  return 0;
}
