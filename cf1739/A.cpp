#include <bits/stdc++.h>

using namespace std;

int main(){

  int t;
  
  scanf("%d", &t);

  while(t--){
    int n, m;
    scanf("%d %d", &n, &m);
    printf("%d %d\n", (n + 1) / 2, (m + 1) / 2);
  }

  return 0;
}
