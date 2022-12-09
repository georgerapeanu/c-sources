#include <bits/stdc++.h>

using namespace std;

int main(){

  int n;
  long long l , u;

  scanf("%d %lld %lld", &n, &l, &u);
  vector<long long> elems(n, 0);
  for(auto &it:elems){
    scanf("%lld", &it);
    it = (l <= it && it <= u ? 1:(it < l ? 0:2));
  }

  vector<int> right(n, 0);

  for(int i = n - 1;i >= 0;i--){
    right[i] = ((i + 1 < n ? right[i + 1]:0) + 1) * (elems[i] < 2);
  }

  int cnt = 0;
  long long answer = 0;
  for(int i = 0;i < n;i++) {
    if(elems[i] == 1){
      answer += 1LL * (cnt + 1) * right[i];
    }
    cnt = (cnt + 1) * (elems[i] < 1);
  }

  printf("%lld\n", answer);

  return 0;
}
