#include <bits/stdc++.h>

using namespace std;


void update(vector<int> &aib, int pos, int value){
  for(;pos < (int)aib.size(); pos += (-pos) & pos) {
    aib[pos] += value;
  }
}

int query(const vector<int> &aib, int value){
  int ans = 0;
  int ans_sum = 0;
  for(int i = (1 << 30);i; i >>= 1) {
    if((ans | i) < (int)aib.size() && ans_sum + aib[ans | i] < value){
      ans |= i;
      ans_sum += aib[ans];
    }
  }
  return ans + 1;
}

int main(){

  int t;

  cin >> t;

  mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

  while(t--){
    int n, k;
    cin >> n >> k;

    vector<int> fr(n + 1, 0);
    vector<int> aib(n + 1, 0);

    for(int i = 1;i <= n;i++){
      update(aib, i, 1);
    }

    int active_nodes = n;

    for(int i = 0;i <= k;i++){
      int current, cnt;
      cin >> current >> cnt;

      if(fr[current] && active_nodes > 0){
        int nod = query(aib, (rng() % active_nodes));
        if(i < k){
          cout << "T " << nod << endl;
        }
      }else{
        fr[current] = cnt;
        update(aib, current, -1);
        active_nodes--;
        if(i < k){
          cout << "W" << endl;
        }
      }
    }
    long double avg_edges = 0;
    int cnt_nodes = 0;
    long long ans = 0;
    for(auto it:fr){
      avg_edges += it;
      cnt_nodes += (it > 0);
      ans += it;
    }
    avg_edges /= cnt_nodes;
    cout << "E " << (ans + (long long)(avg_edges * (n - cnt_nodes))) / 2 << endl;
  }
  

  return 0;
}
