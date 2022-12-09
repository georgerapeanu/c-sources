#include <bits/stdc++.h>

using namespace std;

pair<vector<int>, vector<int> >  solve(vector<vector<int> > elems, pair<int,int> r1, pair<int, int> r2){

  vector<int> a;
  vector<int> b;
  for(int value = (int)elems.size() - 1;value >= 0;value--){
    int cnt1 = 0;
    int cnt2 = 0;
    for(auto it:elems[value]){
      cnt1 += (r1.first <= it && it < r1.second);
      cnt2 += (r2.first <= it && it < r2.second);
    }
    cnt1 = cnt2 = min(cnt1, cnt2);
    for(auto it:elems[value]){
      if(r1.first <= it && it < r1.second && cnt1 > 0){
        cnt1--;
        r1.first = it + 1;
        a.push_back(it);
      }
      if(r2.first <= it && it < r2.second && cnt2 > 0){
        cnt2--;
        r2.first = it + 1;
        b.push_back(it);
      }
    }
  }
  return {a, b};
}

int main(){

  int n;
  scanf("%d", &n);

  vector<int> v(n, 0);
  for(auto &it:v){
    scanf("%d", &it);
  }

  vector<int> original_v = v;

  vector<pair<int, int> > stuff;

  for(int i = 0;i < n;i++){
    stuff.push_back({v[i], i});
  }

  sort(stuff.begin(), stuff.end());

  int cnt = 0;

  for(int i = 0;i < n;i++){
    if(i > 0 && stuff[i - 1].first != stuff[i].first) {
      cnt++; 
    }
    v[stuff[i].second] = cnt;
  }
  vector<vector<int> > elems(cnt + 1);

  for(auto it:stuff){
    elems[v[it.second]].push_back(it.second);
  }

  while(elems.empty() == false && elems.back().size() < 2){
    elems.pop_back();
  }
  
  vector<int> a, b;
  vector<int> c, d;
 
  if(elems.empty() == false){
    int split = elems.back()[elems.back().size() >> 1];
    tie(a,b) = solve(elems, {0, split}, {split, n});
    tie(c,d) = solve(elems, {0, split + 1}, {split + 1, n});
  }

  if(a.size() < c.size()) {
    swap(a, c);
    swap(b, d);
  }

  for(auto it:a){
    printf("%d ", original_v[it]); 
  }
  
  for(auto it:b){
    printf("%d ", original_v[it]); 
  }

  if(a.empty()){
    printf("-1\n");
  }
  

  return 0;
}
