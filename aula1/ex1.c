#include <stdio.h>

int main(){
  unsigned long long int n;
  char hex[17] = "";
  scanf("%d", &n);
  sprintf(hex, "%llx", n);
  printf("%llx\n", n);
  printf("[%s]\n", hex);
  return 0;
}
