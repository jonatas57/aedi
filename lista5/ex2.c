#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void check(){
  printf("check\n");
}

typedef struct queue queue;
typedef struct LinkedNode LinkedNode;

struct LinkedNode{
  char data;
  LinkedNode* next;
};
struct queue {
  int tam;
  LinkedNode *top, *end;
};

void initFila(queue *p){
  p->top = NULL;
  p->end = NULL;
  p->tam = 0;
}
LinkedNode* newNode(char d){
  LinkedNode* tmp = malloc(sizeof(LinkedNode));
  if (tmp != NULL){
    tmp->data = d;
    tmp->next = NULL;
  }
  return tmp;
}
void enqueue(queue *p, LinkedNode *x) {
  if(p->top == NULL) {
    p->top = x;
    p->end = x;
  }
  else {
    p->end->next = x;
    p->end = x;
  }
  p->tam++;
}
char dequeue(queue *p){
  char n;
  LinkedNode *x;
  if (p->top != NULL){
    x = p->top;
    n = x->data;
    p->top = p->top->next;
    free(x);
    p->tam--;
  }
  return n;
}
void printQueue(queue q) {
  for (LinkedNode *x = q.top;x != q.end;x = x->next) {
    printf("%c", x->data);
  }
  printf("%c\n", q.end->data);
}

int main(){
	int lcd[16][9] = {{0,1,0,1,0,1,1,1,1},{0,0,0,0,0,1,0,0,1},{0,1,0,0,1,1,1,1,0},{0,1,0,0,1,1,0,1,1},{0,0,0,1,1,1,0,0,1},{0,1,0,1,1,0,0,1,1},{0,1,0,1,1,0,1,1,1},{0,1,0,0,0,1,0,0,1},{0,1,0,1,1,1,1,1,1},{0,1,0,1,1,1,0,1,1},{0,1,0,1,1,1,1,0,1},{0,0,0,1,1,0,1,1,1},{0,1,0,1,0,0,1,1,0},{0,0,0,0,1,1,1,1,1},{0,1,0,1,1,0,1,1,0},{0,1,0,1,1,0,1,0,0}};
	queue n, hex;
  char c;
  initFila(&n);
	while (scanf("%c", &c) != 0 && c != 'b') {
    if (n.top != NULL || c != '0') {
      enqueue(&n, newNode(c));
    }
  }
  initFila(&hex);
  int aux = 0;
  for (int i = 4 - (n.tam % 4);n.top != NULL;i = (i + 1) % 4) {
    int j = dequeue(&n);
    aux += j * (pow(2, (3 - 1)));
    if (i == 3) {
      enqueue(&hex, newNode((aux >= '0' && aux <= '9') ? (aux + '0') : (aux + 'a' - 10)));
      printQueue(hex);
    }
  }
  queue lin[3];
  initFila(&lin[0]);initFila(&lin[1]);initFila(&lin[2]);
  char std[10]={" _ |_||_|"};
  printQueue(hex);
  while (hex.top != NULL) {
    char s = dequeue(&hex);
    if(s >= '0' && s <= '9'){
			s -= 48;
		}
		else{
			s -= 87;
		}
    for (int i = 0;i < 9;i++){
			enqueue(&lin[i / 3], newNode((lcd[(int)s][i]) ? (std[i]) : (' ')));
		}
  }
	for (int i = 0;i < 3;i++) {
    while (lin[i].top != NULL) {
      printf("%c", dequeue(&lin[i]));
    }
    printf("\n");
  }
	return 0;
}
