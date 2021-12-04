#include <bits/stdc++.h>

using namespace std;



int main(){

  int n,k;
  vector<pair<int,int> > v;
  vector<pair<int,int> > initial;

  scanf("%d %d",&n,&k);

  initial = vector<pair<int,int> > (n,make_pair(0,0));
  
  for(auto &it:initial){
    scanf("%d %d",&it.first,&it.second);
  }

  v = initial;
  sort(v.begin(),v.end());

  for(int i = 0;i < n;i++){
    if(v[i].second != initial[i].second){
      printf("N");
      return 0;
    }
  }

  printf("Y");
    
  return 0;
}
