#include <bits/stdc++.h>

using namespace std;

int t;
int a,b;

pair<int,int> solve(int a,int b,int p,int q){
  if(a >= p){
    return {a - p, min(p,q - (a - p)) * 2 + (a - p)};
  }
  return {b - q, min(q,p - (b - q)) * 2 + (b - q)};
}

int main(){

  scanf("%d",&t);

  while(t--){
    scanf("%d %d",&a,&b);
    int p = (a + b) / 2;
    int q = a + b - p;
    
    pair<int,int> fst = solve(a,b,p,q);
    pair<int,int> snd = solve(a,b,q,p);

    vector<int> ans;

    for(int i = 0;i <= a + b;i++){
      if(i >= fst.first && i <= fst.second && (i - fst.first) % 2 == 0){
        ans.push_back(i);
      }else if(i >= snd.first && i <= snd.second && (i - snd.first) % 2 == 0){
        ans.push_back(i);
      }
    }

    printf("%d\n",(int)ans.size());
    for(auto &it:ans){
      printf("%d ",it);
    }
    printf("\n");
    

  }


  return 0;
}
