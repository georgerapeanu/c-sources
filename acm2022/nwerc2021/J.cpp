#include <bits/stdc++.h>

using namespace std;

long long sqr_dist(const pair<int, int> &a, const pair<int, int> &b){
  return 1LL * (a.first - b.first) * (a.first - b.first) + 1LL * (a.second - b.second) * (a.second - b.second);
}

int main(){
  int n;
  cin >> n;
  vector<pair<int, int> > v(n);
  for(auto &it:v){
    cin >> it.first >> it.second;
  }

  vector<pair<int, int> > intervals;

  for(int i = 0;i < (int)v.size();i++){
    pair<int, int> current = v[i];
    pair<int, int> next = v[(i + 1) % n];
    if(current.second > next.second){
      swap(current, next);
    }

    if(sqr_dist(current, next) < sqr_dist(next, {current.first, current.second + 360})){
      intervals.push_back({current.second, next.second});
      intervals.push_back({current.second + 360, next.second + 360});
    } else {
      intervals.push_back({next.second, current.second + 360});
      intervals.push_back({next.second + 360, current.second + 720});
      intervals.push_back({next.second - 360, current.second});
    }
  }


  vector<pair<int ,int> > events;
  for(auto it:intervals){
    events.push_back({it.first, -1});
    events.push_back({it.second, 1});
    cerr << "debug " <<  it.first << " " << it.second << "\n";
  }
  
  int last_x = 0;
  int active = 0;
  sort(events.begin(), events.end());

  for(auto it:events){
    if(active == 0 && last_x != it.first){
      int lft = max(last_x, 180);
      int rgt = min(it.first, 540);
      if(lft < rgt){
        cout << "no ";
        cout << (lft + rgt) / 2 << ((lft + rgt) % 2 == 0 ? ".0":".5");
        return 0;
      }
    }
    if(it.second == 1){
      active--;
    }else{
      active++;
    }
    last_x = it.first;
  }

  if(last_x < 540){
    int lft = max(last_x, 180);
    int rgt = 540;
    cout << "no ";
    cout << (lft + rgt) / 2 << ((lft + rgt) % 2 == 0 ? ".0":".5");
    return 0;
  }

  cout << "yes";

  return 0;
}
