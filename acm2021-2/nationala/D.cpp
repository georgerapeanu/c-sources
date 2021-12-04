#include <bits/stdc++.h>

using namespace std;


int main(){

  map<int,int> to_norm;
  
  int n;

  scanf("%d",&n);

  vector<int> v(n);

  for(auto &it:v){
    scanf("%d",&it);
    to_norm[it] = 0;
  }

  int lst = 0;

  for(auto &it:to_norm){
    it.second = ++lst;
  }

  for(auto &it:v){
    it = to_norm[it];
  }
  
  vector<pair<int,int> > segments;

  int last = 0;

  for(int i = 1;i < (int)v.size();i++){
    if(v[i - 1] > v[i] || v[i - 1] + 1 < v[i]){
      segments.push_back({v[last],v[i - 1]});
      last = i;
    }
  }
  segments.push_back({v[last],v[(int)v.size() - 1]});

  vector<int> sum(n + 5,0);

  for(auto &it:segments){
    sum[it.first]++;
    sum[it.second]--;
  }

  for(int i = 1;i < (int)sum.size();i++){
    sum[i] += sum[i - 1];
  }

  vector<pair<int,int> > newSegments;

  for(auto &it:segments){
    int last = it.first;
    for(int i = it.first;i + 1 < it.second;i++){
      if(sum[i] != 0){
        if(sum[i] > 0){
          sum[i] = -1;
        }else{
          newSegments.push_back({last,i});
          last = i + 1;
        }
      }
    }
  }

  segments = newSegments;

  
  printf("%d\n",ans);

  return 0;
}
