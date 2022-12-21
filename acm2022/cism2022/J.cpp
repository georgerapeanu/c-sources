#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

ull ask(ull l, ull r){
  ull answer;
  cout << "q " << l << " " << r - 1 << endl;
  cin >> answer;
  return answer;
}

void solve(ull l, ull r, ull cnt, vector<ull> &positions){
  if(r - l == cnt){
    for(ull i = l;i < r;i++){
      positions.push_back(i);
    }
    return ;
  }
  if(cnt == 0){
    return ;
  }
  if(r - l == 1){
    return ;
  }
  ull mid = (l + r) / 2;
  ull left_cnt = ask(l, mid);
  solve(l, mid, left_cnt, positions);
  solve(mid, r, cnt - left_cnt, positions);
}

void answer(const vector<ull> &positions) {
  cout << "a ";
  cout << positions.size() << " ";
  for(auto it:positions){
    cout << it << " ";
  }
  exit(0);
}

int main(){

  vector<ull> positions;
  ull right = 1ULL << 63;
  solve(0, right, ask(0, right), positions);
  answer(positions);
  

  return 0;
}
