#include <bits/stdc++.h>

using namespace std;

int main(){
  int n;

  scanf("%d",&n);

  vector<pair<int,int> > v(n,make_pair(0,0));

  for(auto &it:v){
    scanf("%d %d",&it.first,&it.second);
  }

  auto my_filter = [&](const vector<pair<int,int> > &v){
    vector<pair<int,int> > tmp = v;
    sort(tmp.begin(),tmp.end(),[&](const pair<int,int> &a,const pair<int,int> &b){
      if(a.first != b.first){
        return a.first < b.first;
      }
      return a.second > b.second;
    });
    vector<pair<int,int> > ans;

    for(auto it:tmp){
      while(ans.empty() == false && ans.back().second >= it.second){
        ans.pop_back();
      }
      ans.push_back(it);
    }
    return ans;
  };

  v = my_filter(v);

  int last = -1;
  int cnt = 0;

  for(auto it:v){
    if(last < it.first){
      cnt++;
      last = it.second;
    }
  }

  printf("%d\n",cnt);
  return 0;
}
