#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_node *node;
struct s_node{
  int ra, nota;
  char *nome;
  node ant, prox;
};
void check() {
	printf("check\n");
}
//cria e retorna um novo nó
node newNode(int ra, int nota, char *nome) {
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
  if (*lista == NULL) {
  	*lista = x;
  	x->ant = NULL;
  	return;
  }
  node aux = *lista;
  for (; aux->prox != NULL; aux = aux->prox);
  aux->prox = x;
  x->ant = aux;
}

//busca um ra na lista e retorna a posição
void searchNode(node *head, int ra) {
  if (*head  == NULL) return;

  node aux = *head;
  int pos = 0;
  while(aux && aux->ra != ra){
    aux = aux->prox;
    pos++;
  }

  printf("Pos=%d\n", aux ? pos : -1);
}

/*Compara 2 nós:
Campo:
	1 - Compara os RAs
	2 - Compara os nomes
*/
int compare(node a, node b, int campo) {
  if (campo == 1) {
    return a->ra > b->ra;
  }
  else {
    return strcmp(a->nome, b->nome);
  }
}

//Ordena a lista por inserção
long int insertionSort(node *head, int campo) {
  long int comp = 0;
	int tmpRA, tmpNota;
	char *tmpNome;
	if (*head != NULL) {
		for (node i = (*head)->prox;i != NULL;i = i->prox) {
			node j = i->ant;
			while (j != NULL && ++comp && compare(j, i, campo) > 0) {
				j = j->ant;
			}
			j = j == NULL ? *head : j->prox;
			if (i != j) {
				tmpRA = i->ra;
				tmpNome = i->nome;
				tmpNota = i->nota;

				i->ra = j->ra;
				i->nome = j->nome;
				i->nota = j->nota;

				j->ra = tmpRA;
				j->nome = tmpNome;
				j->nota = tmpNota;
			}
		}
	}
  return comp;
}

//Ordena a lista por seleção
long int selectionSort(node *head, int campo) {
  if (*head == NULL) return 0;

  node i = *head;
  long int comp = 0;
  int tmpRA, tmpNota;
  char *tmpNome;

	for (; i->prox != NULL; i = i->prox){
	node min = i;
	node j = i->prox;

		for (; j != NULL; j = j->prox){
			if (compare(min, j, campo) >  0){
			min = j;
			}
			comp++;
		}

		if (min->ra != i->ra){
			tmpRA = i->ra;
			tmpNome = i->nome;
			tmpNota = i->nota;

			i->ra = min->ra;
			i->nome = min->nome;
			i->nota = min->nota;

			min->ra = tmpRA;
			min->nome = tmpNome;
			min->nota = tmpNota;
		}

	}

	return comp;
}

/*Ordena a lista:
Algoritmos:
  1: Ordenação por seleção
  2: Ordenação por inserção
Campo chave:
  1: RA
  2: Nome
*/
long int ordenaLista(int algoritmo, int campo, node* head) {
  if (*head == NULL) return 0;

  long int comp;  //número de comparações

  if (algoritmo == 1){  //Ordenação por seleção
    comp = selectionSort(head, campo);
  }else if (algoritmo == 2){  //Ordena por inserção
    comp = insertionSort(head, campo);
  }

  return comp;
}

//printa lista
void printList(node lista) {
  if (lista == NULL) return;
  printf("[%d %s %d]\n", lista->ra, lista->nome, lista->nota);
  printList(lista->prox);
}

//deleta um no
void deleteNode(node *x) {
	node aux = *x;
	*x = (*x)->prox;
	if ((*x)->prox != NULL) {
		(*x)->ant = NULL;
	}
	free(aux);
}

int main(int argc, char const *argv[]) {
  char op;
  node lista = NULL;
  while (scanf("\n%c", &op) != -1) {
    int ra, nota, alg, cam;
    char *nome = malloc(51 * sizeof(char));
    switch (op) {
      case 'I':
        scanf("%d %s %d", &ra, nome, &nota);
        insertNode(&lista, newNode(ra, nota, nome));
      break;
      case 'O':
        scanf("%d %d", &alg, &cam);
        printf("Comparacoes=%ld\n", ordenaLista(alg, cam, &lista));
      break;
      case 'B':
        scanf("%d", &ra);
        searchNode(&lista, ra);
      break;
      case 'M':
        printList(lista);
      break;
      case 'P':
        // while(lista != NULL) {
        // 	deleteNode(&lista);
        // }
        return 0;
      break;
    }
  }
}
