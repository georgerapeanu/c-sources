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
  
  int n;
  cin >> n;

  vector<long long> x(n, 0);
  vector<int> r(n, 0);

  for(auto &it:x){
    cin >> it;
  }

  int __max_r = 0;

  for(auto &it:r){
    cin >> it;
    __max_r = max(__max_r, it);
  }

  vector<pair<int, long long> > functions(n);
  functions[0] = {1, 0};

  vector<pair<int, long long> > candidates(2, make_pair(1, 0));
  for(int i = 1;i < n;i++){
    functions[i].second = (x[i] - x[i - 1]) - functions[i - 1].second;
    functions[i].first = -functions[i - 1].first;
    if(functions[i].first == 1 && functions[i].second > candidates[0].second){
      candidates[0] = functions[i]; 
    }
    if(functions[i].first == -1 && functions[i].second > candidates[1].second){
      candidates[1] = functions[i]; 
    }
  }

  for(auto it:candidates){
    long long fst = (__max_r - it.second) / it.first;
    vector<long long> answer = {fst};

    for(int i = 1;i < n;i++){
      answer.push_back(functions[i].first * answer[0] + functions[i].second);
      assert(answer[i] + answer[i - 1] == x[i] - x[i - 1]);
    }

    vector<long long> tmp = answer;
    sort(tmp.begin(), tmp.end());
    sort(r.begin(), r.end());

    bool ok = true;

    for(int i = 0;i < n;i++){
      ok &= (tmp[i] == r[i]);
    }

    if(ok){
      for(auto it:answer){
        cout << it << " ";
      } 
      return 0;
    }
  }

  return 0;
}
