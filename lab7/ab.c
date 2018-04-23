#include <stdio.h>
#include <stdlib.h>

typedef struct linkedNode linkedNode;

struct linkedNode {
  int ra, nota;
  linkedNode* next;
};
void check() {
  printf("check\n");
}
void test(linkedNode *list) {
  if (list == NULL) return;
  printf("%p = (%d, %d), -> %p", list, list->ra, list->nota, list->next);
  test(list->next);
}

//Cria e retorna o nó
linkedNode* newNode(int ra, int nota){
  linkedNode* x = malloc(sizeof(linkedNode));
  x->ra = ra;
  x->nota = nota;
  x->next = NULL;
  return x;
}

//Imprime a lista
void printList(linkedNode *ini){
  printf("[LISTA]\n");
  for(;ini != NULL;ini = ini->next){
    printf("[%d %d]\n", ini->ra, ini->nota);
  }
}

//Insere nó na ultima posição da lista
void insertNode(linkedNode **last, linkedNode *x){
  *last = x;
  *last = (*last)->next;
}

//Remove o primeiro nó de uma lista
linkedNode* removeNode(linkedNode **head) {
  linkedNode *x = *head;
  (*head) = (*head)->next;
  return x;
}

/*Compara dois números.
comp:
  0 - Crescente
  1 - Decrescente
*/
int comp(int ra_1, int ra_2, int compare){
  return compare ? ra_1 > ra_2 : ra_1 < ra_2;
}

void merge(linkedNode **head_1, linkedNode **head_2, int compare){
  linkedNode *aux = NULL;
  while (*head_1 != NULL || *head_2 != NULL) {
    if (*head_2 == NULL || (*head_1 != NULL && comp((*head_1)->ra, (*head_2)->ra, compare))) {
      insertNode(&aux, removeNode(head_1));
    }
    else {
      insertNode(&aux, removeNode(head_2));
    }
  }
  *head_1 = aux;
}
void mergeSort(linkedNode** head_1, linkedNode **last, int qtd, int compare){
  if (qtd == 1) return;

  linkedNode **head_2 = head_1;
  int mid = qtd/2;
  // printf("%d %d\n", qtd, mid);
  for (int i = 0; i <= mid; i++){
    head_2 = &(*head_2)->next;
  }
//   printf("qtd = %d ------------------------------------\n", qtd);
//   test(*head_1);
//   printf("---------------------------------------------\n");
  mergeSort(head_1, head_2, mid, compare);
  mergeSort(head_2, last, qtd-mid, compare);

  merge(head_1, head_2, last, compare);
}

//Deleta uma lista
void freeList(linkedNode **head){
  if (*head == NULL) return;

  linkedNode *aux = *head;
  while (*head != NULL){
    aux = *head;
    *head = (*head)->next;
    free(aux);
  }
}

int main() {
  linkedNode *list = NULL, *last = list;
  int op, qtd = 0;
  while (scanf("%d", &op) != -1) {
    if (op == 1) {
      int ra, nota;
      scanf("%d %d", &ra, &nota);
      insertNode(&last, newNode(ra, nota));
      qtd++;
    }
    else if (op == 2) {
      printList(list);
    }
    else if (op == 6) {
      mergeSort(&list, &last, qtd, 0);
      printf("ok\n");
    }
    else if (op == 9) {
      mergeSort(&list, &last, qtd, 1);
      printf("ok2\n");
    }
    else if (op == 0) {
      freeList(&list);
      return 0;
    }
  }
}
