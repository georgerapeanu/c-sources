#include <bits/stdc++.h>

using namespace std;

const int NMAX = 20;

int n;
vector<int> sons[NMAX + 5];


vector<int> dfs(int nod){
  vector<int> ans;
  for(auto it:sons[nod]){
    vector<int> tmp = dfs(it);
    tmp.push_back(it);
    for(int i = (int)tmp.size() - 1;i;i--){
      swap(tmp[i],tmp[i - 1]);
    }
    vector<int> new_ans = ans;
    reverse(ans.begin(),ans.end());
    for(auto it:tmp){
      new_ans.push_back(it);
      for(auto it:ans){
        new_ans.push_back(it);
      }
      reverse(ans.begin(),ans.end());
    }
    ans = new_ans;
  }
  return ans;
}

int main(){

    scanf("%d",&n);
    
    for(int i = 2;i <= n;i++){
      int father;
      scanf("%d",&father);
      sons[father].push_back(i);
    }

    vector<int> ans = dfs(1);
    
    printf("%d\n",(int)ans.size());
    for(auto it:ans){
      printf("%d ",it);
    }

    return 0;
}
