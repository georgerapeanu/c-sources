#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;
const int KMAX = 2e5;

int n,m,d;
int k,q;

vector<int> graph[NMAX + 5];
vector<int> policies[KMAX + 5];
int gr_in[NMAX + 5];
long long value[NMAX + 5];

int main(){

  scanf("%d %d %d",&n,&m,&d);
  scanf("%d %d",&k,&q);

  for(int i = 1;i <= m;i++){
    int x,y;
    scanf("%d %d",&x,&y);
    graph[y].push_back(x);
    gr_in[x]++;
  }

  for(int i = 1;i <= n;i++){
    int key;
    scanf("%d",&key);
    if(key != -1){
      policies[key].push_back(i);
      gr_in[i]++;
    }
  }

  for(int i = 1;i <= d;i++){
    int policy,_value;
    scanf("%d %d",&policy,&_value);
    value[policy] += _value;
  }

  queue<int> topo;
  long long sum = 0;

  for(int i = 1;i <= n;i++){
    if(gr_in[i] == 0){
      topo.push(i);
    }
  }

  for(int i = 1;i <= q;i++){
    int key;
    scanf("%d",&key);
    for(auto it:policies[key]){
      gr_in[it]--;
      if(gr_in[it] == 0){
        topo.push(it);
      }
    }
    while(topo.empty() == false){
      int nod = topo.front();
      topo.pop();
      sum += value[nod];
      for(auto it:graph[nod]){
        gr_in[it]--;
        if(gr_in[it] == 0){
          topo.push(it);
        }
      }
    }
    printf("%lld\n",sum);
  }

  return 0;
}
