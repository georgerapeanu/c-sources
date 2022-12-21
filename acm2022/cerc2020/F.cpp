#include <bits/stdc++.h>

using namespace std;

int main(){

  int n;

  scanf("%d", &n);

  vector<int> sum(n + 1);

  for(int i = 1;i <= n;i++){
    scanf("%d", &sum[i]);
    sum[i] += sum[i - 1];
    sum[i] %= 10;
  }

  vector<int> last(10, -1);

  vector<int> answer(n + 1, -1);
  for(int i = n;i;i--){
    last[sum[i]] = i;
    if(last[sum[i - 1]] != -1){
      answer[i] = last[sum[i - 1]] - i + 1;
    }
  }

  for(int i = 1;i <= n;i++){
    printf("%d ", answer[i]);
  }

  return 0;
}
