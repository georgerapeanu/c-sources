#include <bits/stdc++.h>
#ifdef LOCAL_DEFINE
#include <dbg.h>
#else
#define dbg(...)
#endif

using namespace std;

int main(){
  ios::sync_with_stdio(true);
  cin.tie(0);
  cout.tie(0);
  
  int n, m;
  cin >> n >> m;
  
  vector<bitset<1000>> subsets(1 << m);
  for(int i = 0;i < m;i++){
    int k;
    cin >> k;

    for(int j = 1;j <= k;j++) {
      int val;
      cin >> val;
      val--;
      subsets[1 << i].set(val);
    }
  }
  
  vector<int> sizes(1 << m, 0);
  vector<int> memorized_popcount(1 << m, 0);
  for(int i = 0;i < (1 << m);i++){
    memorized_popcount[i] = __builtin_popcount(i);
    for(int j = 0;j < m;j++){
      if((i >> j) & 1){
        subsets[i] |= subsets[i ^ (1 << j)];
      }
    }
    sizes[i] = subsets[i].count();
  }


  vector<vector<int> > stuff(n, vector<int>(n + 1, 0));
  
  for(int i = 0;i < n;i++){
    for(int conf = 0;conf < (1 << m);conf++){
      if(subsets[conf].test(i)){
        continue;
      } else {
        stuff[i][n - sizes[conf] - 1] += ((memorized_popcount[conf] & 1) ? -1:1);
      }
    }
    int t = 0;
    for(int j = 0;j <= n;j++){
      stuff[i][j] += t;
      if(stuff[i][j] < 0){
        t = -(-stuff[i][j] + 1) / 2;
        stuff[i][j] -= 2 * t;
      } else if(stuff[i][j] > 1){
        t = stuff[i][j] / 2;
        stuff[i][j] -= 2 * t;
      } else {
        t = 0;
      }
    }
    reverse(stuff[i].begin(), stuff[i].end());
  }

  vector<int> order;

  for(int i = 0;i < n;i++){
    order.push_back(i);
  }
  dbg(stuff);
  sort(order.begin(), order.end(), [&stuff](const int a, const int b) {
      if(stuff[a] != stuff[b]){
        return stuff[a] < stuff[b];
      }
      return a < b;
   });

  for(auto it:order){
    cout << it + 1 << " ";
  }

  return 0;
}
