#include <bits/stdc++.h>

using namespace std;

int main(){


  vector<int> gr(4,0);
  for(int i = 0;i < 3;i++){
    int u,v;
    scanf("%d %d",&u,&v);
    u--;
    v--;
    gr[u]++;
    gr[v]++;
  }

  bool ok = true;

  for(auto it:gr){
    ok &= (0 < it && it < 3);
  }

  printf(ok ? "YES\n":"NO\n");

  return 0;
}
