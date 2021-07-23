#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int n;
int v[NMAX + 5];
int dist[NMAX + 5];

inline int get_left(int i){
  return ((i - 1 + n - 1) % n) + 1;
}

inline int get_right(int i){
  return (i % n) + 1;
}

bool check(int value){
  queue<int> q;
  for(int i = 1;i <= n;i++){
    dist[i] = value;
    q.push(i);
  }
  while(q.empty() == false){
    int i = q.front();
    q.pop();
    if(dist[i] < v[i]){
      continue;
    }
    dist[i] |= v[i];
    if(dist[get_left(i)] < dist[i]){
      dist[get_left(i)] = dist[i];
      q.push(get_left(i));
    }
    if(dist[get_right(i)] < dist[i]){
      dist[get_right(i)] = dist[i];
      q.push(get_right(i));
    }
  }

  for(int i = 1;i <= n;i++){
    if(dist[i] < v[i]){
      return false;
    }
  }
  return true;
}


int main(){

  scanf("%d",&n);

  for(int i = 1;i <= n;i++){
    scanf("%d",&v[i]);
  }

  int ans = 0;

  for(int h = 30;h >= 0;h--){
    if(check((ans | ((1 << h) - 1))) == false){
      ans |= (1 << h);
    }
  }

  printf("%d\n",ans);

  return 0;
}
