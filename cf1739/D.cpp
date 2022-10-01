#include <bits/stdc++.h>

using namespace std;

int cut_count(const vector<int> &father, int query_depth){
  int answer = 0;
  vector<int> depth(father.size(), 0);
  
  for(int i = (int)father.size() - 1;i > 1;i--){
    if(depth[i] >= query_depth - (father[i] != 1)){
      answer++; 
    }else{
      depth[father[i]] = max(depth[father[i]], depth[i] + 1);
    }
  }

  return answer;
}

int main(){

  int t;

  scanf("%d", &t);

  while(t--){
    int n, k;
    scanf("%d %d", &n, &k);
    vector<int> father(n + 1, 0);

    for(int i = 2;i <= n;i++){
      scanf("%d", &father[i]);
    }
    
    int low = 0;
    int high = n;

    while(high - low > 1){
      int mid = (low + high) >> 1;

      if(cut_count(father, mid) > k){
        low = mid;
      }else{
        high = mid;
      }
    }

    printf("%d\n", high);
  }

  return 0;
}
