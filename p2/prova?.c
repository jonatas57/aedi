#include <stdio.h>
#include <stdlib.h>

typedef struct linkNode linkNode;
struct linkNode {
  int data;
  linkNode *next, *prev;
};

linkNode* newNode(int data) {
  linkNode *x = malloc(sizeof(linkNode));
  x->data = data;
  x->next = NULL;
  x->prev = NULL;
  return x;
}
linkNode** insertNode(linkNode *list, linkNode *x, linkNode *last) {
  linkNode **ret = malloc(2 * sizeof(linkNode *));
  if (list == NULL) {
    ret[0] = x;
    ret[1] = x;
  }
  else {
    last->next = x;
    x->prev = last;
    last = x;
    ret[0] = list;
    ret[1] = last;
  }
  return ret;
}
void swap(linkNode *x, linkNode *y) {
  int tmp = x->data;
  x->data = y->data;
  y->data = tmp;
}
void quicksort(linkNode *list, linkNode *last) {
  if (list == NULL || last == NULL || list == last || last->next == list) return;
  linkNode *pivo = list, *aux = list;
  for (linkNode *tmp = list;tmp != NULL;tmp = tmp->next) {
    if (tmp->data < pivo->data) {
      swap(tmp, aux->next);
      aux = aux->next;
    }
  }
  swap(pivo, aux);
  quicksort(list, aux->prev);
  quicksort(aux->next, last);
}
void printList(linkNode *list) {
  for (;list != NULL;list = list->next) {
    printf("%d ", list->data);
  }
  printf("\n");
}

int main(int argc, char const *argv[]) {
  linkNode *list = NULL, *last = NULL;
  int op;
  while (scanf("%d", &op) && op != 0) {
    if (op == 1) {
      int a;
      scanf("%d", &a);
      linkNode **aux = insertNode(list, newNode(a), last);
      list = aux[0];
      last = aux[1];
    }
    else if (op == 2) {
      printList(list);
    }
    else if (op == 3) {
      quicksort(list, last);
    }
  }
  return 0;
}
