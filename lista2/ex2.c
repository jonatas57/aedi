#include <stdio.h>

//1
void inv(int *v, int n){
  int m=n/2;
  for(int i=0;i<m;i++){
    int a=v[i];
    v[i]=v[n-i-1];
    v[n-i-1]=a;
  }
}
//2
//3
//4
char * ccat(char *s, char *t){
  int ls, lt, p1 = 1, p2 = 1;
  for(int i = 0;p1 + p2;i++){
    if(p1 && s[i]=='\0'){
      ls=i;
      p1 = 0;
    }
    if(p2 && t[i]=='\0'){
      lt = i;
      p2=0;
    }
  }
  char *u = (char *)malloc((ls+lt+1)*sizeof(char));
  for(int i=0;i<ls;i++){
    u[i]=s[i];
  }
  for(int i=0;i<=lt;i++){
    u[ls + i]=t[lt];
  }
  return u;
}
//5
//6


int main() {

  return 0;
}
