#include <bits/stdc++.h>
#include "minimize.h"

using namespace std;

struct segment_t{
  int delta; /// the segment is actually [r - delta, r]
  int r;
  long long cost;

  bool operator < (const segment_T &other){
    if(this->cost != other.cost){
      return this->cost < other.cost;
    }
    if(this->r != other.r){
      return this->r < other.r;
    }
  }
};
int n;
int k;
vector<vector<int> > lookupTable;
priority_queue<segment_t> segments;
vector<int> v;

void initialize(int _N, int _K, vector <int> a){
  n = _N;
  k = _K;
  lookupTable = vector<vector<int>>(n + 1, vector<int>(k + 1, -1));
  pref_sum = vector<long long>(n + 1, 0);
  v = a;


  for(int i = 1;i <= n;i++){
    long long cost_sum = 0;
    for(int delta = 0;delta <= i;delta++){
      lookupTable[i][delta] = (v[i] ^ v[i - delta]) - cost_sum;
      if(i - delta > 1){
        cost_sum += a[i - delta] ^ a[i - delta - 1];
      }
    }
  }
}
void modify(int pos, int val);
long long calculate(); 
