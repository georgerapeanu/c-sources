//rapeanu_nsqrtlog_aint_normal.cpp
#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;
const int BUCK = 600;
const int inf = 1e9;

class SegmentTree{
  
  int n;
  vector<int> aint;

  void update(int nod, int st, int dr, int pos, int value){
    if(dr < pos || st > pos){
      return;
    }
    if(st == dr){
      aint[nod] = min(aint[nod], value);
      return ;
    }

    int mid = (st + dr) / 2;

    update(nod * 2, st, mid, pos, value);
    update(nod * 2 + 1, mid + 1, dr, pos , value);

    aint[nod] = min(aint[nod * 2], aint[nod * 2 + 1]);
  }

  int query(int nod, int st, int dr, int l, int r){
    if(r < st || l > dr){
      return inf;
    }

    if(l <= st && dr <= r){
      return aint[nod];
    }

    int mid = (st + dr) / 2;

    return min(query(nod * 2, st, mid, l, r), query(nod * 2 + 1, mid + 1, dr, l, r));
  }


  public:

  ///0 indexed
  SegmentTree(int n){
    this->n = n;
    aint = vector<int>(4 * n + 5, inf);
  }

  void update(int pos, int value){
    update(1, 0, n - 1, pos, value);
  }

  ///query on [l, r)
  int query(int l, int r){
    return query(1, 0, n - 1, l, r - 1);
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

  SegmentTree aint(n + 1);
  int idx = n;

  for(auto &query:queries){
    while(idx >= query.r){
      if(fr[prefix_sums[idx]] <= BUCK){
        for(auto it:positions[prefix_sums[idx]]){
          aint.update(it, idx - it);
          if(it >= idx){
            break;
          }
        }
      }
      idx--;
    }
    query.ans = min(query.ans, aint.query(0, query.l));
  }

  for(auto &query:queries){
    if(query.ans == inf){
      query.ans = -1;
    }
    solutions[query.id] = query.ans;
  }
}

#include <stdio.h>
#include <stdlib.h>

int main(){
  
  int n, q;
  scanf("%d", &n);
  int* v = (int*)malloc(sizeof(int) * n);

  for(int i = 0;i < n;i++){
    scanf("%d", &v[i]);
  }

  scanf("%d", &q);

  int* l = (int*)malloc(sizeof(int) * q);
  int* r = (int*)malloc(sizeof(int) * q);
  for(int i = 0;i < q;i++){
    scanf("%d %d", &l[i], &r[i]);
  }

  int* answers = (int*)malloc(sizeof(int) * q);

  solve(n, v, q, l, r, answers);

  for(int i = 0;i < q;i++){
    printf("%d\n", answers[i]);
  }

  free(answers);
  free(l);
  free(r);
  free(v);

  return 0;
}
