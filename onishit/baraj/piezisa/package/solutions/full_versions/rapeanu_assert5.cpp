#include "piezisa.h"
#include <cassert>
#include <bits/stdc++.h>

using namespace std;

const int NMAX = 5e5;
const int BUCK = 1000;
const int inf = 1e9;

class BucketDecomposition{
  
  int n;
  int bucket_size;
  vector<int> values;
  vector<int> bucket_values;
  vector<int> bucket;

  public:

  ///0 indexed
  BucketDecomposition(int n, int bucket_size){
    this->n = n;
    this->bucket_size = bucket_size;
    values = vector<int>(n + 1, inf);
    bucket = vector<int>(n + 1, 0);

    int current_bucket = 0;
    for(int i = 0;i < n;i += bucket_size){
      for(int j = i;j < n && j < i + bucket_size;j++){
        bucket[j] = current_bucket;
      }
      current_bucket++;
    }
    bucket_values = vector<int>(current_bucket, inf);
  }

  void update(int pos, int value){
    values[pos] = value;
    bucket_values[bucket[pos]] = min(bucket_values[bucket[pos]], value);
  }

  int query(int r){
    r--;
    int ans = inf;
    for(int i = bucket[r] - 1;i >= 0;i--){
      ans = min(ans, bucket_values[i]);
    }
    for(int i = r;i >= 0 && bucket[i] == bucket[r];i--){
      ans = min(ans, values[i]);
    }
    return ans;
  }
};

struct query_t{
  int id;
  int l;
  int r;
  int ans;

  query_t(){
    id = l = r = 0;
    ans = inf;
  }

  bool operator < (const query_t &other)const{
    return this->r > other.r;
  }
};

void solve(int n, int v[], int q, int l[], int r[], int solutions[]){
  assert(n <= 500000);
  assert(q <= 500000);

  for(int i = 0;i < n;i++){
    assert(0 <= v[i] && v[i] < (1 << 30));
  }

  for(int i = 0;i < q;i++){
    assert(0 <= l[i] && l[i] <= r[i] && r[i] < n);
  }

  vector<int> prefix_sums(n + 1, 0);
  vector<pair<int,int>> normalizare;

  normalizare.push_back({prefix_sums[0], 0});
  for(int i = 0;i < n;i++){
    prefix_sums[i + 1] = prefix_sums[i] ^ v[i];
    normalizare.push_back({prefix_sums[i + 1], i + 1});
  }
  
  sort(normalizare.begin(), normalizare.end());

  int last = 0;
  for(int i = 0;i < (int)normalizare.size();i++){
    if(i > 0 && normalizare[i].first != normalizare[i - 1].first){
      last++;
    }
    prefix_sums[normalizare[i].second] = last;
  }

  normalizare.clear();
  
  vector<int> fr(last + 1, 0);

  for(int i = 0;i < (int)prefix_sums.size();i++){
    fr[prefix_sums[i]]++;
  }

  vector<query_t> queries(q);

  for(int i = 0;i < q;i++){
    queries[i].l = l[i] + 1;
    queries[i].r = r[i] + 1;
    queries[i].ans = inf;
    queries[i].id = i;
  }

  vector<int> nxt(n + 1, -1);
  vector<int> ant(n + 1, -1);

  for(int value = 0;value <= last;value++){
    if(fr[value] > BUCK){
      for(int i = 0;i <= n;i++){
        ant[i] = (prefix_sums[i] == value ? i:(i > 0 ? ant[i - 1]:-1)); 
      }
      for(int i = n;i >= 0;i--){
        nxt[i] = (prefix_sums[i] == value ? i:(i < n ? nxt[i + 1]:-1)); 
      }

      for(auto &it:queries){
        if(ant[it.l - 1] != -1 && nxt[it.r] != -1){
          it.ans = min(it.ans, nxt[it.r] - ant[it.l - 1]);
        }
      }
    }
  }

  vector<vector<int> > positions(last + 1, vector<int>());
  for(int i = 0;i <= n;i++){
    positions[prefix_sums[i]].push_back(i);
  }
  
  sort(queries.begin(), queries.end());

  BucketDecomposition batog(n + 1, BUCK);
  int idx = n;

  for(auto &query:queries){
    while(idx >= query.r){
      if(fr[prefix_sums[idx]] <= BUCK){
        for(auto it:positions[prefix_sums[idx]]){
          batog.update(it, idx - it);
          if(it >= idx){
            break;
          }
        }
      }
      idx--;
    }
    query.ans = min(query.ans, batog.query(query.l));
  }

  for(auto &query:queries){
    if(query.ans == inf){
      query.ans = -1;
    }
    solutions[query.id] = query.ans;
  }
}

