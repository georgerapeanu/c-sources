#include <bits/stdc++.h>
#include "cetatuie.h"

using namespace std;

long long back(int pos, int n, long long k, int v[], long long sum){
  if(pos >= n){
    return sum;
  }

  long long ans = 1e18;
  for(long long increase = 0;increase <= k;increase++){
    v[pos] += increase;
    ans = min(ans, back(pos + 1, n, k - increase, v, sum + (pos > 0 ? abs(v[pos] - v[pos - 1]):0)));
    v[pos] -= increase;
  }

  return ans;
}

long long solve(int n, long long k, int v[]){
  return back(0, n, k, v, 0);
}
