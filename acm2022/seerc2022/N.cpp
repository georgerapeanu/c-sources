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
  vector<int> v(n, 0);

  priority_queue<pair<int, int>> pq;
  for(int i = 0;i < n;i++){
    cin >> v[i];
    pq.push({v[i], i});
  }

  while(!pq.empty()){
    pair<int, int> tmp = pq.top();
    pq.pop();

    if(tmp.first != v[tmp.second]){
      continue;
    }

    if(tmp.second > 0 && v[tmp.second] - v[tmp.second - 1] > m){
      v[tmp.second - 1] = v[tmp.second] - m;
      pq.push({v[tmp.second - 1], tmp.second - 1});
    }
    if(tmp.second + 1 < n && v[tmp.second] - v[tmp.second + 1] > m){
      v[tmp.second + 1] = v[tmp.second] - m;
      pq.push({v[tmp.second + 1], tmp.second + 1});
    }
  }

  for(auto it:v){
    cout << it << " "; 
  }

  return 0;
} 
