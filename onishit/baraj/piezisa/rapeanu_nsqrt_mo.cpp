#include <bits/stdc++.h>
#include "piezisa.h"

using namespace std;

const int inf = 1e9;
const int NMAX = 2e5;
const int BUCK = 600;

struct query_t{
  int l;
  int r;
  int id;
  int ans;

  query_t(){
    l = r = id = 0;
    ans = inf;
  }

  bool operator < (const query_t &other)const{
    return this->r > other.r;
  }
};

void solve(int n, int v[], int q, int l[], int r[], int solutions[]){
  vector<int> prefix_sums(n + 1, 0);
  for(int i = 1;i <= n;i++){
    prefix_sums[i] = prefix_sums[i - 1] ^ v[i - 1];
  }

  vector<pair<int,int> > normalizare;

  for(int i = 0; i <= n; i++) {
    normalizare.push_back({prefix_sums[i], i});
  }

  sort(normalizare.begin(), normalizare.end());

  int current_value = 0;

  for(int i = 0;i < (int)normalizare.size();i++){
    if(i > 0 && normalizare[i].first != normalizare[i - 1].first){
      current_value++;
    }
    prefix_sums[normalizare[i].second] = current_value;
  }

  vector<vector<query_t> > queries(n / BUCK + 1, vector<query_t>());

  for(int i = 0;i < q;i++){
    query_t query;
    query.l = l[i] + 1;
    query.r = r[i] + 1;
    query.id = i;
    query.ans = inf;
    queries[query.l / BUCK].push_back(query);
  }
  
  for(int i = 0;i * BUCK <= n;i++){
    sort(queries[i].begin(), queries[i].end());
  }

  vector<int> left(current_value + 1, -1);
  vector<int> right(current_value + 1, -1);
  vector<pair<int, int> > undo_stack;
  for(int bucket = 0;bucket  * BUCK <= n;bucket++){
    int min_value = inf;
    for(auto& it:right){
      it = -1;
    }
    
    int mo_l = bucket * BUCK;
    int mo_r = n + 1;

    for(auto& query:queries[bucket]){
      while(mo_r > query.r){
        mo_r--;
        right[prefix_sums[mo_r]] = mo_r;
        if(right[prefix_sums[mo_r]] != -1 && left[prefix_sums[mo_r]] != -1){
          min_value = min(min_value, right[prefix_sums[mo_r]] - left[prefix_sums[mo_r]]);
        }
      }
      
      int backup_min = min_value;

      while(mo_l < query.l){
        undo_stack.push_back({prefix_sums[mo_l], left[prefix_sums[mo_l]]});
        left[prefix_sums[mo_l]] = mo_l;
        if(right[prefix_sums[mo_l]] != -1 && left[prefix_sums[mo_l]] != -1){
          min_value = min(min_value, right[prefix_sums[mo_l]] - left[prefix_sums[mo_l]]);
        }
        mo_l++;
      }

      query.ans = min_value;
      if(query.ans == inf){
        query.ans = -1;
      }
      solutions[query.id] = query.ans;
      while(undo_stack.empty() == false){
        left[undo_stack.back().first] = undo_stack.back().second;
        undo_stack.pop_back();
        mo_l--;
      }

      min_value = backup_min;
    }

    for(int i = bucket * BUCK;i <= n && i < (bucket + 1) * BUCK;i++){
      left[prefix_sums[i]] = i;
    }
  }
}


