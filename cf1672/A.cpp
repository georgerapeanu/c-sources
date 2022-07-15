#include <bits/stdc++.h>

using namespace std;

int main(){
  int t;

  scanf("%d", &t);

  while(t--){
    int n;
    scanf("%d", &n);

    int ans = 0;

    while(n--){
      int value;
      scanf("%d", &value);
      ans ^= ((value & 1) ^ 1);
    }
    printf(ans == 0 ? "maomao90\n":"errorgorn\n");
  }
  return 0;
}
