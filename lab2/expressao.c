#include <stdio.h>
#include <stdlib.h>

typedef struct pilha pilha;
typedef struct LinkedNode LinkedNode;

struct LinkedNode{
  double data;
  LinkedNode* next;
};
struct pilha {
  int tamanho;
  LinkedNode *topo;
};

void initPilha(pilha *p){
  p->topo = NULL;
  p->tamanho = 0;
}
LinkedNode* novo(double d){
  LinkedNode* tmp = malloc(sizeof(LinkedNode));
  if (tmp != NULL){
    tmp->data = d;
    tmp->next = NULL;
  }
  return tmp;
}
void empilhar(pilha *p, LinkedNode *x) {
  if(p->topo == NULL) {
    p->topo = x;
    p->tamanho++;
  }
  else {
    x->next = p->topo;
    p->topo = x;
    p->tamanho++;
  }
}
double desempilhar(pilha *p){
  double n;
  LinkedNode *x;
  if (p->topo != NULL){
    x = p->topo;
    n = x->data;
    p->topo = p->topo->next;
    free(x);
    p->tamanho--;
  }
  return n;
}

double funf(double a, double b, double c){
  return (a * a) - ((double)b / 2) + c;
}
double fung(double a, double b, double c){
  return (a * b) + c;
}
double funh(double a){
  return 3 * a;
}
double soma(double a, double b){
  return a + b;
}
double subt(double a, double b){
  return a - b;
}


int main(){
  int e = 0;
  char *s;
  pilha p;
  s = malloc(101 * sizeof(char));
  initPilha(&p);
  scanf("%s", s);
  double r;
  for (int i = 0;s[i] != '\0' && e == 0;i++){
    if (s[i] >= 48 && s[i] <= 57) {
      empilhar(&p, novo(s[i] - 48));
    }
    else {
      switch (s[i]) {
        case 'f':
        if (p.tamanho >= 3) {
          r = funf(desempilhar(&p), desempilhar(&p), desempilhar(&p));
        }
        else {
          e = 1;
        }
        break;
        case 'g':
        if (p.tamanho >= 3) {
          r = fung(desempilhar(&p), desempilhar(&p), desempilhar(&p));
        }
        else {
          e = 1;
        }
        break;
        case 'h':
        if (p.tamanho >= 1) {
          r = funh(desempilhar(&p));
        }
        else {
          e = 1;
        }
        break;
        case '+':
        if (p.tamanho >= 2) {
          r = soma(desempilhar(&p), desempilhar(&p));
        }
        else {
          e = 1;
        }
        break;
        case '-':
        if (p.tamanho >= 2) {
          r = subt(desempilhar(&p), desempilhar(&p));
        }
        else {
          e = 1;
        }
        break;
      }
      empilhar(&p, novo(r));
    }
  }
  if (p.tamanho == 1 && e == 0) {
    printf("%.2f\n", desempilhar(&p));
  }
  else {
    printf("ERRO\n");
  }
  return 0;
}
