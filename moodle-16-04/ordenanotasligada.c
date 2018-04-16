#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_node *node;
struct s_node{
  int ra, nota;
  char *nome;
  no ant, prox;
};

//cria um novo nó e retorna ele
node newNode(int ra, int nota, char *nome){
  node x = (node) malloc(sizeof(struct s_node));

  if(x != NULL) {
    x->ra = ra;
    x->nota = nota;
    x->nome = nome;
    x->prox = NULL;
    x->ant = NULL;
  }
  return x;
}
//insere um no
void insertNode(node* lista, node x) {
  node aux = *lista;
  for (aux != NULL && aux->prox != NULL;aux = aux->prox);
  aux->prox = x;
  x->ant = aux;
}

//busca um ra na lista e retorna a posição
void searchNode(node *head, int ra){
  if (*head  == NULL) return NULL;

  node aux = *head;
  int pos = 0;
  while(aux && aux->ra != ra){
    aux = aux->prox;
    pos++;
  }

  if (aux){  //nó existe
    printf("%d\n", pos);
  }else{  //nó não existe
    printf("-1\n");
  }
}

int compare(void* a, void* b, int campo) {
  if (campo == 1) {
    return *(int *)a > *(int *)b;
  }
  else {
    return strcmp((char *)a, (char *)b) + 1;
  }
}
long int insertionSort(no *head, int campo) {
  long int comp = 0;
  for (node i = (*head)->prox;i != NULL;i = i->prox) {
    node j = i->ant;
    void *key = (campo == 1) ? &i->ra : &i->nome;
    while (j != NULL && ++comp && compare((campo == 1 ? &j->ra : &j->nome), key, campo)) {
      j = j->ant;
    }

  }
  return comp;
}


//Ordena a lista por seleção
long int selectionSort(no *head, int campo){
  if (*head == NULL) return 0;

  node aux = *head;
  long int comp = 0;

  for (; aux->prox != NULL; aux = aux->prox){
    node min = aux;
    node tmp = aux->prox;

    for (; tmp != NULL; tmp = tmp->prox){
      if (min > tmp){
        min = tmp;
        comp++;
      }

      if (min != aux){
        tmp = aux;
        aux = min;

      }

    }
}

/*Ordena a lista:
Algoritmos:
  1: Ordenação por seleção
  2: Ordenação por inserção
Campo chave:
  1: RA
  2: Nome
*/
long int ordenaLista(int algoritmo, int campo, no* head){
  if (*head == NULL) return NULL;

  long int comp;  //número de comparações

  if (algoritmo == 1){  //Ordenação por seleção
    comp = selectionSort(no* head, int campo);
  }else if (algoritmo == 2){  //Ordena por inserção
    comp = insertionSort(no *head, int campo);
  }

  return comp;
}

//printa lista
void printList(node lista) {
  if (lista == NULL) return;
  printf("[%d %s %d]\n", lista->ra, lista->nome, lista->nota);
  printList(lista->prox);
}

int main(int argc, char const *argv[])
{
  char op;
  node lista = NULL;
  while (scanf("\n%c", &op) != -1) {
    int ra, nota, alg, cam;
    char *nome = malloc(51 * sizeof(char));
    switch (op) {
      case 'I':
        scanf("%d %s %d", ra, nome, nota);
        insertNode(&lista, newNode(ra, nota, nome));
      break;
      case 'O':
        scanf("%d %d", &alg, &cam);
        printf("Comparacoes=%ld\n", ordenaLista(alg, cam, &lista));
      break;
      case 'B':
        scanf("%d", &ra);
        printf("Pos=");
        searchNode(&lista, ra);
      break;
      case 'M':
        printList(lista);
      break;
      case 'P':
        while(lista != NULL) {
          deleteNode(&lista);
        }
        return 0;
      break;
    }
  }
}
