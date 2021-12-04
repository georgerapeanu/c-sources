#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> a;
vector<int> b;

struct operation_t{
  char type;
  int l;
  int r;
};

int main(){

  scanf("%d",&n);

  a = vector<int>(n);
  b = vector<int>(n);

  for(auto &it:a){
    scanf("%d",&it);
  }
  for(auto &it:b){
    scanf("%d",&it);
  }

  vector<int> bpos = {0};

  for(int i = 1;i < n;i++){
    if(b[bpos.back()] != b[i]){
      bpos.push_back(i);
    }
  }
  vector<int> apos;

  for(int i = 0;i < n;i++){
    if(apos.size() < bpos.size() && a[i] == b[bpos[apos.size()]]){
      apos.push_back(i);
    }
  }

  if(apos.size() != bpos.size()){
    printf("-1\n");
    return 0;
  }

  vector<operation_t> ans; 

  int last = -1;
  int currSgn = 0;

  auto solve = [&](int l,int r,int mode){
    if(l > r){
      return ;
    }
    if(mode == -1){
      for(int i = r;i >= l;i--){
        for(int j = apos[i];j < bpos[i];j++){
          ans.push_back({(a[j] < a[j + 1] ? 'm':'M'),j,j + 1});
          a[j + 1] = a[j];
        }
      }
    }else{
      for(int i = l;i <= r;i++){
        for(int j = apos[i];j > bpos[i];j--){
          ans.push_back({(a[j] < a[j - 1] ? 'm':'M'),j - 1,j});
          a[j - 1] = a[j];
        }
      }
    }
  };

  for(int i = 0;i < (int)apos.size();i++){
    if(apos[i] <= bpos[i]){
      if(currSgn <= 0){
        ;
      }else{
        solve(last + 1,i - 1,currSgn); 
        last = i - 1;
      }
      currSgn = -1;
    }else{
      if(currSgn >= 0){
        ;
      }else{
        solve(last + 1,i - 1,currSgn);
        last = i - 1;
      }
      currSgn = 1;
    }
  }

  solve(last + 1,(int)apos.size() - 1,currSgn);

  for(int i = 1;i < n;i++){
    if(a[i] != b[i]){
      ans.push_back({(a[i - 1] < a[i] ? 'm':'M'),i - 1,i});
      a[i] = a[i - 1];
    }
  }

  printf("%d\n",(int)ans.size());

  for(auto it:ans){
    printf("%c %d %d\n",it.type,it.l + 1,it.r + 1);
  }


  return 0;
}
