#include <stdio.h>
#include <stdlib.h>
#include "piezisa.h"

int main(){
  
  int n, q;
  scanf("%d", &n);
  int* v = (int*)malloc(sizeof(int) * n);

  for(int i = 0;i < n;i++){
    scanf("%d", &v[i]);
  }

  scanf("%d", &q);

  int* l = (int*)malloc(sizeof(int) * q);
  int* r = (int*)malloc(sizeof(int) * q);
  for(int i = 0;i < q;i++){
    scanf("%d %d", &l[i], &r[i]);
  }

  int* answers = (int*)malloc(sizeof(int) * q);

  solve(n, v, q, l, r, answers);

  for(int i = 0;i < q;i++){
    printf("%d\n", answers[i]);
  }

  free(answers);
  free(l);
  free(r);
  free(v);

  return 0;
}
