#include <stdio.h>
#include <stdlib.h>

typedef struct contato contato;
struct contato{
  char nome[50], tel[10], email[50];
};

contato * realocar(contato *age, int q){
  contato *nage=(contato*)malloc((q+50)*sizeof(contato));
  if(nage != NULL){
    for (int i=0;i<q;i++){
      nage[i]=age[i];
    }
    free(age);
  }
  return nage;
}

int main() {
  int o;
  char menu[97]="Menu:\n1 - Inserir contato\n2 - Buscar nome\n3 - Buscar telefone\n4 - Mostrar agenda\n0 - Sair\n";
  contato *agenda;
  agenda = (contato*)malloc(50 * sizeof(contato));
  int qtd = 0;
  while (printf("%s", menu) && scanf("%d", &o) && o) {
    if (o == 1){
      if(qtd % 50 == 0){
        agenda = realocar(agenda, qtd);
      }
      printf("Nome: ");
      scanf("%s", &agenda[qtd].nome);
      printf("Telefone: ");
      scanf("%s", agenda[qtd].tel);
      printf("E-mail: ");
      scanf("%s", &agenda[qtd].email);
      qtd++;
    }
    else if (o == 2){

    }
    else if (o == 3){

    }
    else {
      printf("%-50s%-10s%s\n", "Nome", "Telefone", "E-mail");
      for(int i=0;i<qtd;i++){
        printf("%-50s%-10s%s\n", agenda[i].nome, agenda[i].tel, agenda[i].email);
      }
    }
  }
  return 0;
}
