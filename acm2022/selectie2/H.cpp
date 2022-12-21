#include <bits/stdc++.h>

using namespace std;

int main(){

  int t;

  scanf("%d", &t);

  for(int test = 1;test <= t;test++){
    int n;
    scanf("%d", &n);
    vector<int> prefix_sums(n + 1, 0);
    for(int i = 1;i <= n;i++){
      int value;
      scanf("%d", &value);
      prefix_sums[value] += 1;
    }

    for(int i = 1;i <= n;i++) {
      prefix_sums[i] += prefix_sums[i - 1];
      //suppose i divines
      if(prefix_sums[i] == i){
        printf("Case %d: %d\n",test, i);
        break;
      }
    }
  }

  return 0;
}
