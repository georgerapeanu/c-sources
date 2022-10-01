#include <bits/stdc++.h>

using namespace std;

int main(){
  
  int t;

  scanf("%d", &t);

  while(t--){
    int n;
    vector<int> damages[2];
    scanf("%d", &n);
    
    vector<int> a(n, 0);

    for(auto &it:a){
      scanf("%d", &it);
    }

    for(int i = 0;i < n;i++){
      int value = 0;
      scanf("%d", &value);
      damages[a[i]].push_back(value);
    }

    sort(damages[0].begin(), damages[0].end(), greater<int>());
    sort(damages[1].begin(), damages[1].end(), greater<int>());
    int len = min(damages[0].size(), damages[1].size());

    long long sum[] = {0, 0};

    for(int i = 0;i < len;i++){
      sum[0] += damages[0][i];
      sum[1] += damages[1][i];
    }

    long long single_sum = 0;

    for(int i = len;i < n;i++){
      if(i < (int)damages[0].size()){
        single_sum += damages[0][i];
      }
      if(i < (int)damages[1].size()){
        single_sum += damages[1][i];
      }
    }

    printf("%lld\n", (sum[0] + sum[1]) * 2 - (damages[0].size() != damages[1].size() ? 0:min(damages[0][len - 1], damages[1][len - 1])) + single_sum);

  }

  return 0;
}
