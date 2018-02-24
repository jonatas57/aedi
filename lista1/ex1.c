#include <stdio.h>
#include <stdlib.h>

int main(){
  int k, m, *s;
  scanf("%d %d", &m, &k);
  s = (int *)malloc(m * sizeof(int));
  for (int i = 0;i < m;i++){
    scanf("%d", s + i);
  }
  int p = 0;
  for(int i = 0, j = 1;j <= m;j++){
    if (s[j] == s[j - 1] + 1){
      p = 1;
    }
    else {
      if (p) {
        p = 0;
        if (j - i <= k) {
          for(int l = i;l < j;l++){
            printf("%d ", s[l]);
          }
          printf("\n");
        }
        else {
          for (int a = i;a <= j - k;a++){
            for (int b = 0;b < k;b++){
              printf("%d ", s[a + b]);
            }
            printf("\n");
          }
        }
      }
      i = j;
    }
  }
  return 0;
}
