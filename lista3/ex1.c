#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedNode no;

struct LinkedNode{
  int data;
  no* next;
};

no* novo(int d){
  no* tmp = malloc(sizeof(no));
  if (tmp != NULL){
    tmp->data = d;
    tmp->next = NULL;
  }
  return tmp;
}

void printList(no* list){
  for(;list!=NULL;list=list->next){
    printf("%d ", list->data);
  }
  printf("\n");
}
//1)
void insertNode(no** ini, no* novo, int p) {
  no* tmp = *ini;
  for (int i = 1;i < p && tmp != NULL && tmp->next != NULL;i++, tmp=tmp->next);
  if(tmp == NULL){
    *ini = novo;
  }else{
    novo->next=tmp->next;
    tmp->next=novo;
  }
}
//2)
void concatList(no *list1, no *list2){
  no* final = list1;
  for(;final!=NULL && final->next != NULL;final = final->next);
  final->next = list2;
}
//3)
void invertList(no** ini){

}
//4)
no* divideList(no* list){
  int i, j;
  no *list2, *tmp;
  for(i=0, tmp = list;tmp!=NULL&&tmp->next!=NULL;i++, tmp=tmp->next);
  i/=2;
  for (tmp = list, j = 1;j < i && tmp != NULL && tmp->next != NULL;j++, tmp=tmp->next);
  list2 = tmp->next;
  tmp->next = NULL;
  return list2;
}
//5)

//apenas slide
//4)
void removeFirst(no** list){
  if(*list!=NULL){
    no* tmp=*list;
    *list=tmp->next;
    free(tmp);
  }
}
//5)
void removeLast(no** list){
  no* tmp=*list;
  for(;tmp!=NULL&&tmp->next!=NULL&&tmp->next->next!=NULL;tmp=tmp->next);
  free(tmp->next);
  tmp->next=NULL;
}
//7)
void removeNode(no** ini, int p) {
  no* tmp = *ini;
  for (int i = 1;i < p && tmp != NULL && tmp->next != NULL;i++, tmp=tmp->next);
  if(tmp != NULL){
    no* tmp2=tmp->next;
    tmp->next=tmp2->next;
    free(tmp2);
  }
}


int main(int argc, char const *argv[]) {
  no *list = NULL, *list2 = NULL;
  for(int i=1;i<=9;i++){
    insertNode(&list, novo(i), i-1);
  }
  printf("lista: ");
  printList(list);
  removeNode(&list, 5);
  printf("lista 2: ");
  printList(list);
  return 0;
}
