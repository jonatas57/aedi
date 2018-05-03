#include <stdio.h>
#include <stdlib.h>

typedef struct pilha pilha;
typedef struct fila fila;
typedef struct fpilha fpilha;
struct pilha {
  int *data, tam, qtd, *top;
};
struct fila {
  int *data, *head, *tail, tam, qtd;
};
struct fpilha {
  int *data1, *data2, *top1, *top2;
};

void check(){
  printf("check\n");
}
void test(fpilha *f) {
  int b = (((f->top1 == f->data1 && f->top2 == f->data2) || f->top1 != f->data1) ? 1 : 0);
  int *head = b ? f->data1 : f->top2 + 1, *tail = b ? f->top1 - 1 : f->data2;
  printf("f->head = %p\n", head);
  for (;head != tail + 1;head++) {
    printf("-%p = %d\n", head, *head);
  }
  printf("-f->tail = %p\n", tail);
}
//1------
pilha* initPilha(int n) {
  pilha *p = malloc(sizeof(pilha));
  p->tam = n;
  p->qtd = 0;
  p->data = malloc(n * sizeof(pilha));
  p->top = p->data;
  return p;
}
void push(pilha *p, int d) {
  if (p->qtd != p->tam){
    *p->top = d;
    p->top++;
    p->qtd++;
  }
  else {
    p->tam *= 2;
    int *v = malloc(p->tam * sizeof(int));
    for (int i = 0;p->data + i != p->top;i++) {
      v[i] = p->data[i];
    }
    free(p->data);
    p->data = v;
    p->top = p->data + p->qtd;
    push(p, d);
  }
}
int pop(pilha *p) {
  if (p->qtd != 0) {
    p->top--;
    p->qtd--;
    return *p->top;
  }
  return -1;
}
void freePilha(pilha *p) {
  if (p->tam > p->qtd) {
    int *v = malloc(p->qtd * sizeof(int));
    for (int i = 0;p->data + i != p->top;i++) {
      v[i] = p->data[i];
    }
    free(p->data);
    p->data = v;
    p->top = p->data + p->qtd;
    p->tam = p->qtd;
  }
}
void printPilha(pilha *p) {
  for (int *i = p->data;i != p->top;i++) {
    printf("%d ", *i);
  }
  printf("\n");
}
//2------
fila* initFila(int n) {
  fila *f = malloc(sizeof(fila));
  f->tam = n;
  f->qtd = 0;
  f->data = malloc((n + 1) * sizeof(pilha));
  f->head = f->data;
  f->tail = f->data;
  return f;
}
void enqueue(fila *f, int d) {
  if (f->qtd != f->tam){
    *f->tail = d;
    f->tail++;
    f->qtd++;
  }
  else {
    f->tam *= 2;
    int *v = malloc((f->tam + 1) * sizeof(int));
    for (int *i = f->head, j = 0;i != f->tail;i++, j++) {
      if (i == f->data + f->tam + 1) {
        i -= f->qtd;
      }
      v[j] = *i;
    }
    free(f->data);
    f->data = v;
    f->head = f->data;
    f->tail = f->data + f->qtd;
    enqueue(f, d);
  }
}
int dequeue(fila *f) {
  if (f->qtd != 0) {
    int x = *f->head;
    f->head = f->head == f->data + f->tam + 1 ? f->data : f->head + 1;
    f->qtd--;
    return x;
  }
  return -1;
}
void freeFila(fila *f) {
  if (f->tam > f->qtd) {
    int *v = malloc(f->qtd * sizeof(int));
    for (int *i = f->head, j = 0;i != f->tail;i++, j++) {
      if (i == f->data + f->tam + 1) {
        i -= f->qtd;
      }
      v[j] = *i;
    }
    free(f->data);
    f->data = v;
    f->head = f->data;
    f->tail = f->data + f->qtd;
    f->tam = f->qtd;
  }
}
void printFila(fila *f) {
  for (int *i = f->head;i != f->tail;i++) {
    if (i == f->data + f->tam + 1) {
      i -= f->qtd;
    }
    printf("%d ", *i);
  }
  printf("\n");
}
//3------
fpilha* initfPilha(int n) {
  fpilha *p = malloc(sizeof(fpilha));
  p->data1 = malloc((n + 1) * sizeof(pilha));
  p->data2 = p->data1 + n;
  p->top1 = p->data1;
  p->top2 = p->data2;
  return p;
}
void enq(fpilha *f, int n) {
  if (f->top1 != f->top2) {
    if (f->top2 == f->data2) {
      *f->top1 = n;
      f->top1++;
    }
    else {
      while (f->top2 != f->data2) {
        f->top2++;
        *f->top1 = *f->top2;
        f->top1++;
      }
      enq(f, n);
    }
  }
}
int deq(fpilha *f) {
  if (f->top1 != f->data1 || f->top2 != f->data2) {
    if (f->top1 == f->data1) {
      f->top2++;
      return *f->top2;
    }
    else {
      while (f->top1 != f->data1) {
        f->top1--;
        *f->top2 = *f->top1;
        f->top2--;
      }
      return deq(f);
    }
  }
  return -1;
}

int main() {
  fpilha *f;
  f = initfPilha(20);
  int b = 50;
  while (b) {
    printf("1-enqueue, 2-dequeue, 3-test\n");
    scanf("%d", &b);
    int a;
    switch (b) {
      case 1:
      scanf("%d", &a);
      enq(f, a);
      break;
      case 2:
      printf("retirando %d\n", deq(f));
      break;
      case 3:
      test(f);
      break;
    }
  }
  return 0;
}
