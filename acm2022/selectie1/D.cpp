#include <bits/stdc++.h>

using namespace std;

bool cmp(pair<string, long double> &a, pair<string ,long double> &b){
  return a.second < b.second;
}

int main(){

  int n;

  cin >> n;

  vector<pair<string, long double> > _first(n, {"",  0});
  vector<pair<string, long double> > _second(n, {"", 0});

  for(int i = 0;i < n;i++) {
    string name;
    cin >> name;
    _first[i].first = name;
    _second[i].first = name;
    cin >> _first[i].second;
    cin >> _second[i].second;
  }


  sort(_first.begin(), _first.end(), cmp);
  sort(_second.begin(), _second.end(), cmp);

  long double best_answer = 1e18;
  int index = -1;

  for(int i = 0;i < n && i < 5;i++){
    long double local_answer = _first[i].second;
    int cntLeft = 3;
    for(int j = 0;j < n && j < 5 && cntLeft > 0;j++){
      if(_second[j].first == _first[i].first){
        continue;
      }
      cntLeft--;
      local_answer += _second[j].second;
    }
    if(best_answer > local_answer){
      best_answer = local_answer;
      index = i;
    }
  }

  cout << fixed << setprecision(10) << best_answer << "\n";
  cout << _first[index].first << "\n";
  int cntLeft = 3;
  for(int j = 0;j < n && j < 5 && cntLeft > 0;j++){
    if(_second[j].first == _first[index].first){
      continue;
    }
    cout << _second[j].first << "\n";
    cntLeft--;
  }

  return 0;
}
