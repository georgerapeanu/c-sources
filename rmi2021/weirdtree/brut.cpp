#include "weirdtree.h"
#include <vector>
#include <algorithm>

using namespace std;

vector<int> v;

void initialise(int n, int q, int h[]){
  v = vector<int>(n,0);
  for(int i = 0;i < n;i++){
    v[i] = h[i + 1];
  }
}

bool cmp(int a,int b){
  return v[a] > v[b];
}

void cut(int l, int r, int k){
  vector<int> order;
  for(int i = l - 1;i < r;i++){
    order.push_back(i);
  }
  sort(order.begin(),order.end(), cmp);

  int last_index = 0;
  int last_value = v[order[0]];

  for(int i = 1;i < (int)order.size();i++){
    if(k >= 1LL * (v[order[i - 1]] - v[order[i]]) * i){
      k -= 1LL * (v[order[i - 1]] - v[order[i]]) * i;
      last_index = i;
      last_value = v[order[i]];
    }else{
      break;
    }
  }
  
  
  sort(order.begin(),order.begin() + last_index + 1);
  last_value -= k / (last_index + 1) ;
  k %= (last_index + 1);
  for(int i = 0;i <= (int)last_index;i++){
    v[order[i]] = max(0, last_value - (i < k));
  }
}

void magic(int i, int x){
  v[i - 1] = x;
}

long long inspect(int l, int r){
  long long sum = 0;

  for(int i = l - 1;i < r;i++){
    sum += v[i];
  }
  return sum;
}
