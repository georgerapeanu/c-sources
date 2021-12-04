#include <bits/stdc++.h>

using namespace std;

int main(){

  freopen("linii.in","r",stdin);
  freopen("linii.out","w",stdout);

  int n;

  scanf("%d", &n);

  vector<pair<int,int> > v(n,make_pair(0,0));

  for(auto &it:v){
    int x,y;
    scanf("%d %d", &x, &y);
    it.first = x + y;
    it.second = y - x;
  }

  sort(v.begin(), v.end());

  vector<int> active;

  for(auto it:v){
    int l = -1;
    int r = active.size();

    while(r - l > 1){
      int mid = (l + r) / 2;
      if(active[mid] <= it.second){
        r = mid;
      }else{
        l = mid;
      }
    }
    if(r == (int)active.size()){
      active.push_back(it.second);
    }else{
      active[r] = it.second;
    }
  }

  printf("%d\n",(int)active.size());

  return 0;
}
